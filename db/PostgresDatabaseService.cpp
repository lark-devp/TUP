#include "PostgresDatabaseService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

PostgresDatabaseService::PostgresDatabaseService(QObject* parent)
    : IDatabaseService(parent)
{

    // "QPSQL" - это внутреннее имя драйвера Qt для PostgreSQL
    m_db = QSqlDatabase::addDatabase("QPSQL");
    qDebug() << "Database service initialized.";
}

PostgresDatabaseService::~PostgresDatabaseService()
{
    // При уничтожении объекта сервиса, корректно закрываем соединение
    if (m_db.isOpen()) {
        disconnectFromSource();
    }
}

/**
 * @brief Устанавливает соединение с базой данных PostgreSQL.
 * Все параметры соединения задаются здесь.
 */
bool PostgresDatabaseService::connectToSource()
{


    m_db.setHostName("localhost");
    m_db.setDatabaseName("timetracker");
    m_db.setUserName("postgres");  //
    m_db.setPassword("Annapetrovna2005");
    m_db.setPort(5432);                 // Стандартный порт для PostgreSQL


    bool ok = m_db.open();


    if (ok) {
        qDebug() << "Успешное подключение к базе данных:" << m_db.databaseName();
    } else {

        qCritical() << "Не удалось подключиться к базе данных! Ошибка:";
        qCritical() << m_db.lastError().text();
    }

    return ok;
}

/**
 * @brief Закрывает соединение с базой данных.
 */
void PostgresDatabaseService::disconnectFromSource()
{
    m_db.close();
    qDebug() << "Соединение с базой данных закрыто.";
}


QVariantMap PostgresDatabaseService::authenticateUser(const QString& username, const QString& password)
{

    QSqlQuery query;
    query.prepare(R"(SELECT user_id FROM "User" WHERE username = :username AND password_hash = :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qCritical() << "Ошибка аутентификации:" << query.lastError().text();
        return QVariantMap();
    }
    if (query.next()) {
        QVariantMap userData;
        userData["user_id"] = query.value("user_id").toInt();
        return userData;
    }
    return QVariantMap();
}

bool PostgresDatabaseService::addUser(const QString& username, const QString& email, const QString& password)
{

    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO "User" (username, password_hash, email)
        VALUES (:username, :password, :email)
    )");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qCritical() << "Ошибка регистрации пользователя:" << query.lastError().text();

        if (query.lastError().nativeErrorCode() == "23505") { // Код ошибки уникальности в Postgres
            emit errorOccurred("Пользователь с таким именем или email уже существует.");
        } else {
            emit errorOccurred("Не удалось зарегистрировать пользователя.");
        }
        return false;
    }

    qDebug() << "Пользователь" << username << "успешно зарегистрирован.";
    return true;
}


QVector<TaskDisplayData> PostgresDatabaseService::getTasksForUser(int userId)
{
    QVector<TaskDisplayData> tasks;
    QSqlQuery query;
    // ОБНОВЛЕННЫЙ ЗАПРОС: Добавляем проверку на is_active = TRUE
    query.prepare(R"(
        SELECT task_id, title FROM "Task"
        WHERE user_id = :user_id AND is_active = TRUE
        ORDER BY title
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения задач:" << query.lastError().text();
        return tasks;
    }

    while (query.next()) {
        TaskDisplayData task;
        task.id = query.value("task_id").toString();
        task.title = query.value("title").toString();
        tasks.append(task);
    }
    return tasks;
}
QVariantMap PostgresDatabaseService::getTaskDetails(int taskId)
{
    QSqlQuery query;
    // ИСПРАВЛЕНИЕ: Мы явно добавляем tweek_task_id в список полей для выборки
    query.prepare(R"(SELECT title, description, tweek_task_id FROM "Task" WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения деталей задачи:" << query.lastError().text();
        return QVariantMap();
    }
    if (query.next()) {
        QVariantMap taskData;
        taskData["title"] = query.value("title").toString();
        taskData["description"] = query.value("description").toString();
        // Теперь эта строка будет работать, потому что поле есть в результате запроса
        taskData["tweek_task_id"] = query.value("tweek_task_id").toString();
        return taskData;
    }
    return QVariantMap();
}

// НОВЫЙ МЕТОД
bool PostgresDatabaseService::updateTask(int taskId, const QString& title, const QString& description)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE "Task"
        SET title = :title, description = :description
        WHERE task_id = :task_id
    )");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Ошибка обновления задачи:" << query.lastError().text();
        return false;
    }
    return true;
}

// НОВЫЙ МЕТОД
bool PostgresDatabaseService::deactivateTask(int taskId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "Task" SET is_active = FALSE WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Ошибка деактивации (удаления) задачи:" << query.lastError().text();
        return false;
    }
    return true;
}
bool PostgresDatabaseService::addTask(const QString& title, const QString& description, int userId, const QString& tweekId)
{
    qDebug() << "[DEBUG 3: DATABASE]"
             << "Title:" << title
             << "Description:" << description
             << "TweekID:" << tweekId;

    QSqlQuery query(m_db);

    if (tweekId.isEmpty()) {
        // --- Сценарий 1: Задача создается локально, tweek_task_id будет NULL ---
        query.prepare(R"(
            INSERT INTO "Task" (user_id, title, description)
            VALUES (:user_id, :title, :description)
        )");
    } else {
        // --- Сценарий 2: Задача импортируется из Tweek ---
        query.prepare(R"(
            INSERT INTO "Task" (user_id, title, description, tweek_task_id)
            VALUES (:user_id, :title, :description, :tweek_id)
        )");
        query.bindValue(":tweek_id", tweekId);
    }

    // Эти параметры общие для обоих запросов
    query.bindValue(":user_id", userId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qCritical() << "Ошибка добавления задачи:" << query.lastError().text();
        emit errorOccurred("Не удалось сохранить задачу в базу данных."); // Можно добавить это для обратной связи
        return false;
    }

    qDebug() << "Задача '" << title << "' успешно добавлена для пользователя" << userId;
    return true;
}

QString PostgresDatabaseService::getTaskTitle(int taskId)
{
    QSqlQuery query;
    query.prepare(R"(SELECT title FROM "Task" WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения названия задачи:" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        return query.value("title").toString();
    }

    return QString(); // Возвращаем пустую строку, если задача не найдена
}


bool PostgresDatabaseService::addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO "TimeTracking" (task_id, start_time, end_time)
        VALUES (:task_id, :start_time, :end_time)
    )");
    query.bindValue(":task_id", taskId);
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);

    if (!query.exec()) {
        qCritical() << "Ошибка сохранения сессии времени:" << query.lastError().text();
        emit errorOccurred("Не удалось сохранить сессию времени в базу данных.");
        return false;
    }

    qDebug() << "Сессия для задачи" << taskId << "успешно сохранена.";
    return true;
}

QVector<qint64> PostgresDatabaseService::getWeeklyTaskStats(int taskId, const QDate& weekStartDate)
{
    // Инициализируем вектор семью нулями (для Пн, Вт, ..., Вс)
    QVector<qint64> weeklyMinutes(7, 0);

    QSqlQuery query(m_db);
    // EXTRACT(ISODOW FROM start_time) в PostgreSQL возвращает день недели (1=Пн, 7=Вс)
    query.prepare(R"(
        SELECT
            EXTRACT(ISODOW FROM start_time) as day_of_week,
            SUM(EXTRACT(EPOCH FROM (end_time - start_time))/60)::INT as total_minutes
        FROM "TimeTracking"
        WHERE
            task_id = :task_id AND
            start_time >= :start_date AND
            start_time < :end_date
        GROUP BY day_of_week
    )");

    query.bindValue(":task_id", taskId);
    query.bindValue(":start_date", QDate(weekStartDate));
    query.bindValue(":end_date", QDate(weekStartDate.addDays(7))); // Конец недели (следующий понедельник)

    if (!query.exec()) {
        qCritical() << "Ошибка получения недельной статистики:" << query.lastError().text();
        return weeklyMinutes; // Возвращаем пустой вектор в случае ошибки
    }

    while (query.next()) {
        int dayOfWeek = query.value("day_of_week").toInt(); // 1-7
        qint64 minutes = query.value("total_minutes").toLongLong();
        if (dayOfWeek >= 1 && dayOfWeek <= 7) {
            weeklyMinutes[dayOfWeek - 1] = minutes; // Записываем в нужный индекс (0-6)
        }
    }

    return weeklyMinutes;
}
QVector<TaskTimeSummary> PostgresDatabaseService::getTaskTimeSummaries(int userId)
{
    QVector<TaskTimeSummary> summaries;
    QSqlQuery query(m_db);

    // Этот запрос соединяет задачи с записями времени,
    // фильтрует по пользователю, группирует по каждой задаче
    // и суммирует сгенерированное поле duration_minutes.
    query.prepare(R"(
        SELECT
            T.title,
            SUM(TT.duration_minutes) as total_minutes
        FROM "Task" T
        LEFT JOIN "TimeTracking" TT ON T.task_id = TT.task_id
        WHERE T.user_id = :user_id
        GROUP BY T.task_id, T.title
        HAVING SUM(TT.duration_minutes) IS NOT NULL -- Показываем только задачи, где есть записи времени
        ORDER BY total_minutes DESC
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения сводной статистики по задачам:" << query.lastError().text();
        return summaries;
    }

    while (query.next()) {
        TaskTimeSummary summary;
        summary.title = query.value("title").toString();
        summary.totalMinutes = query.value("total_minutes").toLongLong();
        summaries.append(summary);
    }

    qDebug() << "Найдено" << summaries.count() << "задач с записью времени для пользователя" << userId;
    return summaries;
}

bool PostgresDatabaseService::saveTweekTokens(int userId, const QString& idToken, const QString& refreshToken)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE "User"
        SET tweek_token = :id_token, tweek_refresh_token = :refresh_token
        WHERE user_id = :user_id
    )");
    query.bindValue(":id_token", idToken);
    query.bindValue(":refresh_token", refreshToken);
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка сохранения токенов Tweek:" << query.lastError().text();
        return false;
    }
    return true;
}

bool PostgresDatabaseService::hasTweekTokens(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT tweek_token, tweek_refresh_token FROM "User"
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка проверки токенов Tweek:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        // Проверяем, что токены не просто существуют, но и не пустые
        return !query.value("tweek_token").toString().isEmpty() &&
               !query.value("tweek_refresh_token").toString().isEmpty();
    }
    return false;
}

std::optional<TweekTokens> PostgresDatabaseService::getTweekTokens(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT tweek_token, tweek_refresh_token FROM "User"
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения токенов Tweek:" << query.lastError().text();
        return std::nullopt;
    }

    if (query.next()) {
        TweekTokens tokens;
        tokens.idToken = query.value("tweek_token").toString();
        tokens.refreshToken = query.value("tweek_refresh_token").toString();
        if (!tokens.idToken.isEmpty()) {
            return tokens;
        }
    }
    return std::nullopt;
}

// НОВЫЙ МЕТОД
bool PostgresDatabaseService::saveTweekTaskId(int localTaskId, const QString& tweekTaskId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "Task" SET tweek_task_id = :tweek_id WHERE task_id = :local_id)");
    query.bindValue(":tweek_id", tweekTaskId);
    query.bindValue(":local_id", localTaskId);

    if (!query.exec()) {
        qCritical() << "Ошибка сохранения Tweek Task ID:" << query.lastError().text();
        return false;
    }
    return true;
}

// НОВЫЙ МЕТОД
bool PostgresDatabaseService::saveTweekDefaultCalendar(int userId, const QString& calendarId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "User" SET tweek_default_calendar_id = :calendar_id WHERE user_id = :user_id)");
    query.bindValue(":calendar_id", calendarId);
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка сохранения календаря по умолчанию:" << query.lastError().text();
        return false;
    }
    return true;
}

// НОВЫЙ МЕТОД
QString PostgresDatabaseService::getTweekDefaultCalendar(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(SELECT tweek_default_calendar_id FROM "User" WHERE user_id = :user_id)");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения календаря по умолчанию:" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        return query.value(0).toString();
    }
    return QString();
}
void PostgresDatabaseService::clearTweekData(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE "User"
        SET
            tweek_token = NULL,
            tweek_refresh_token = NULL,
            tweek_default_calendar_id = NULL
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка очистки данных Tweek для пользователя" << userId << ":" << query.lastError().text();
    } else {
        qDebug() << "Данные Tweek для пользователя" << userId << "успешно очищены.";
    }
}

