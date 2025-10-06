#include "PostgresDatabaseService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

PostgresDatabaseService::PostgresDatabaseService(QObject* parent)
    : IDatabaseService(parent)
{
    // Получаем объект соединения с базой данных по умолчанию
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
    // --- 1. Установка параметров соединения ---
    // ВАЖНО: Для курсовой работы можно временно хранить их в коде,
    // но в реальном приложении их нужно выносить в файл конфигурации (settings.ini, .env).

    m_db.setHostName("localhost");      // Адрес сервера БД. "localhost" - если БД на том же компьютере.
    m_db.setDatabaseName("timetracker"); // <-- ЗАМЕНИТЕ НА ИМЯ ВАШЕЙ БАЗЫ ДАННЫХ
    m_db.setUserName("postgres");  // <-- ЗАМЕНИТЕ НА ВАШЕГО ПОЛЬЗОВАТЕЛЯ POSTGRES (часто "postgres")
    m_db.setPassword("Annapetrovna2005");  // <-- ЗАМЕНИТЕ НА ВАШ ПАРОЛЬ
    m_db.setPort(5432);                 // Стандартный порт для PostgreSQL

    // --- 2. Попытка открыть соединение ---
    bool ok = m_db.open();

    // --- 3. Проверка результата и логирование ---
    if (ok) {
        qDebug() << "Успешное подключение к базе данных:" << m_db.databaseName();
    } else {
        // Если подключиться не удалось, выводим подробную ошибку.
        // Это САМАЯ ВАЖНАЯ часть для отладки!
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


// Он будет автоматически загружать новое поле password_hash благодаря "SELECT *".
QVariantMap PostgresDatabaseService::authenticateUser(const QString& username, const QString& password)
{
    // ВАЖНО: Никогда не храните пароли в открытом виде!
    // Этот пример предполагает, что у вас в таблице User есть поле password_hash
    // Для простоты здесь используется SHA-256, но в реальных системах нужны "соленые" хеши.
    // QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    // Для курсовой работы, если у вас нет хеширования, можете временно использовать прямое сравнение,
    // но ОБЯЗАТЕЛЬНО упомяните в пояснительной записке, что это небезопасно.
    // Давайте для примера предположим, что у вас в таблице есть поле "password".
    query.prepare(R"(SELECT user_id FROM "User" WHERE username = :username AND password_hash = :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // Замените на passwordHash, если используете хеши

    if (!query.exec()) {
        qCritical() << "Ошибка аутентификации:" << query.lastError().text();
        return QVariantMap(); // Возвращаем пустую карту при ошибке
    }

    if (query.next()) {
        // Пользователь найден, возвращаем его ID
        QVariantMap userData;
        userData["user_id"] = query.value("user_id").toInt();
        return userData;
    }

    // Пользователь не найден
    return QVariantMap();
}

QVector<TaskDisplayData> PostgresDatabaseService::getTasksForUser(int userId)
{
    QVector<TaskDisplayData> tasks;
    QSqlQuery query;
    query.prepare(R"(SELECT task_id, title FROM "Task" WHERE user_id = :user_id)");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Ошибка получения задач:" << query.lastError().text();
        return tasks; // Возвращаем пустой вектор
    }

    while (query.next()) {
        TaskDisplayData task;
        task.id = query.value("task_id").toString();
        task.title = query.value("title").toString();
        tasks.append(task);
    }

    qDebug() << "Найдено" << tasks.count() << "задач для пользователя" << userId;
    return tasks;
}
bool PostgresDatabaseService::addTask(const QString& title, const QString& description, int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(INSERT INTO "Task" (user_id, title, description) VALUES (:user_id, :title, :description))");
    query.bindValue(":user_id", userId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qCritical() << "Ошибка добавления задачи:" << query.lastError().text();
        emit errorOccurred("Не удалось сохранить задачу в базу данных.");
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
