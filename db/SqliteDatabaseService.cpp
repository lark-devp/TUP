#include "SqliteDatabaseService.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QApplication>

SqliteDatabaseService::SqliteDatabaseService(QObject* parent)
    : IDatabaseService(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "Database service for SQLite initialized.";

    // Определяем безопасное место для хранения файла БД
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    m_dbPath = QApplication::applicationDirPath() + "/timetracker.sqlite";
    qDebug() << "Database path set to:" << m_dbPath;
}

SqliteDatabaseService::~SqliteDatabaseService()
{
    if (m_db.isOpen()) {
        disconnectFromSource();
    }
}

bool SqliteDatabaseService::connectToSource()
{
    m_db.setDatabaseName(m_dbPath);

    if (!m_db.open()) {
        qCritical() << "Failed to connect to database! Error:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Successfully connected to SQLite database:" << m_db.databaseName();
    initializeDatabase(); // Создаем таблицы, если их нет
    return true;
}

void SqliteDatabaseService::initializeDatabase()
{
    QSqlQuery query(m_db);

    // Включаем поддержку внешних ключей
    if (!query.exec("PRAGMA foreign_keys = ON;")) {
        qWarning() << "Could not enable foreign keys:" << query.lastError().text();
    }

    // Создание таблицы User
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS "User" (
            user_id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL,
            tweek_token TEXT,
            tweek_refresh_token TEXT,
            tweek_default_calendar_id TEXT,
            auth_token TEXT UNIQUE
        )
    )")) {
        qCritical() << "Failed to create User table:" << query.lastError().text();
    }

    // Создание таблицы Task
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS "Task" (
            task_id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            title TEXT NOT NULL,
            description TEXT,
            is_active INTEGER NOT NULL DEFAULT 1,
            tweek_task_id TEXT,
            FOREIGN KEY (user_id) REFERENCES "User" (user_id)
        )
    )")) {
        qCritical() << "Failed to create Task table:" << query.lastError().text();
    }

    // Создание таблицы TimeTracking
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS "TimeTracking" (
            tracking_id INTEGER PRIMARY KEY AUTOINCREMENT,
            task_id INTEGER NOT NULL,
            start_time TEXT NOT NULL,
            end_time TEXT NOT NULL,
            FOREIGN KEY (task_id) REFERENCES "Task" (task_id)
        )
    )")) {
        qCritical() << "Failed to create TimeTracking table:" << query.lastError().text();
    }

    qDebug() << "Database schema checked and initialized.";
}

void SqliteDatabaseService::disconnectFromSource()
{
    m_db.close();
    qDebug() << "Database connection closed.";
}

QVariantMap SqliteDatabaseService::authenticateUser(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare(R"(SELECT user_id FROM "User" WHERE username = :username AND password_hash = :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qCritical() << "Authentication error:" << query.lastError().text();
        return QVariantMap();
    }
    if (query.next()) {
        QVariantMap userData;
        userData["user_id"] = query.value("user_id").toInt();
        return userData;
    }
    return QVariantMap();
}

bool SqliteDatabaseService::addUser(const QString& username, const QString& password)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO "User" (username, password_hash)
        VALUES (:username, :password)
    )");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qCritical() << "User registration error:" << query.lastError().text();
        emit errorOccurred("User with this name already exists.");
        return false;
    }
    return true;
}

QVector<TaskDisplayData> SqliteDatabaseService::getTasksForUser(int userId)
{
    QVector<TaskDisplayData> tasks;
    QSqlQuery query;
    query.prepare(R"(
        SELECT task_id, title FROM "Task"
        WHERE user_id = :user_id AND is_active = 1
        ORDER BY title
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error getting tasks:" << query.lastError().text();
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

QVariantMap SqliteDatabaseService::getTaskDetails(int taskId)
{
    QSqlQuery query;
    query.prepare(R"(SELECT title, description, tweek_task_id FROM "Task" WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Error getting task details:" << query.lastError().text();
        return QVariantMap();
    }
    if (query.next()) {
        QVariantMap taskData;
        taskData["title"] = query.value("title").toString();
        taskData["description"] = query.value("description").toString();
        taskData["tweek_task_id"] = query.value("tweek_task_id").toString();
        return taskData;
    }
    return QVariantMap();
}

bool SqliteDatabaseService::updateTask(int taskId, const QString& title, const QString& description)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE "Task" SET title = :title, description = :description
        WHERE task_id = :task_id
    )");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Error updating task:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqliteDatabaseService::deactivateTask(int taskId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "Task" SET is_active = 0 WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Error deactivating task:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqliteDatabaseService::addTask(const QString& title, const QString& description, int userId, const QString& tweekId)
{
    QSqlQuery query(m_db);
    if (tweekId.isEmpty()) {
        query.prepare(R"(
            INSERT INTO "Task" (user_id, title, description)
            VALUES (:user_id, :title, :description)
        )");
    } else {
        query.prepare(R"(
            INSERT INTO "Task" (user_id, title, description, tweek_task_id)
            VALUES (:user_id, :title, :description, :tweek_id)
        )");
        query.bindValue(":tweek_id", tweekId);
    }
    query.bindValue(":user_id", userId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qCritical() << "Error adding task:" << query.lastError().text();
        return false;
    }
    return true;
}

QString SqliteDatabaseService::getTaskTitle(int taskId)
{
    QSqlQuery query;
    query.prepare(R"(SELECT title FROM "Task" WHERE task_id = :task_id)");
    query.bindValue(":task_id", taskId);

    if (!query.exec()) {
        qCritical() << "Error getting task title:" << query.lastError().text();
        return QString();
    }
    if (query.next()) {
        return query.value("title").toString();
    }
    return QString();
}

bool SqliteDatabaseService::addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO "TimeTracking" (task_id, start_time, end_time)
        VALUES (:task_id, :start_time, :end_time)
    )");
    query.bindValue(":task_id", taskId);
    query.bindValue(":start_time", startTime.toString(Qt::ISODate));
    query.bindValue(":end_time", endTime.toString(Qt::ISODate));

    if (!query.exec()) {
        qCritical() << "Error saving time session:" << query.lastError().text();
        return false;
    }
    return true;
}

QVector<qint64> SqliteDatabaseService::getWeeklyTaskStats(int taskId, const QDate& weekStartDate)
{
    QVector<qint64> weeklyMinutes(7, 0);
    QSqlQuery query(m_db);

    query.prepare(R"(
        SELECT
            strftime('%w', start_time) as day_of_week,
            CAST(SUM(strftime('%s', end_time) - strftime('%s', start_time)) / 60.0 AS INTEGER) as total_minutes
        FROM "TimeTracking"
        WHERE
            task_id = :task_id AND
            start_time >= :start_date AND
            start_time < :end_date
        GROUP BY day_of_week
    )");

    query.bindValue(":task_id", taskId);
    // --- ИСПРАВЛЕНИЕ ЗДЕСЬ ---
    query.bindValue(":start_date", weekStartDate.startOfDay().toString(Qt::ISODate));
    query.bindValue(":end_date", weekStartDate.addDays(7).startOfDay().toString(Qt::ISODate));
    // --- КОНЕЦ ИСПРАВЛЕНИЯ ---

    if (!query.exec()) {
        qCritical() << "Error getting weekly stats:" << query.lastError().text();
        return weeklyMinutes;
    }

    while (query.next()) {
        int dayOfWeek = query.value("day_of_week").toInt(); // 0=Вс, 1=Пн, ...
        if (dayOfWeek == 0) { dayOfWeek = 7; } // Воскресенье делаем 7-м днем

        qint64 minutes = query.value("total_minutes").toLongLong();
        if (dayOfWeek >= 1 && dayOfWeek <= 7) {
            weeklyMinutes[dayOfWeek - 1] = minutes;
        }
    }
    return weeklyMinutes;
}

QVector<TaskTimeSummary> SqliteDatabaseService::getTaskTimeSummaries(int userId)
{
    QVector<TaskTimeSummary> summaries;
    QSqlQuery query(m_db);

    query.prepare(R"(
        SELECT
            T.title,
            SUM(CAST((strftime('%s', TT.end_time) - strftime('%s', TT.start_time)) / 60.0 AS INTEGER)) as total_minutes
        FROM "Task" T
        LEFT JOIN "TimeTracking" TT ON T.task_id = TT.task_id
        WHERE T.user_id = :user_id AND TT.tracking_id IS NOT NULL
        GROUP BY T.task_id, T.title
        ORDER BY total_minutes DESC
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error getting task time summaries:" << query.lastError().text();
        return summaries;
    }

    while (query.next()) {
        TaskTimeSummary summary;
        summary.title = query.value("title").toString();
        summary.totalMinutes = query.value("total_minutes").toLongLong();
        summaries.append(summary);
    }
    return summaries;
}

bool SqliteDatabaseService::saveTweekTokens(int userId, const QString& idToken, const QString& refreshToken)
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
        qCritical() << "Error saving Tweek tokens:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqliteDatabaseService::hasTweekTokens(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT tweek_token, tweek_refresh_token FROM "User"
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error checking Tweek tokens:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return !query.value("tweek_token").toString().isEmpty() &&
               !query.value("tweek_refresh_token").toString().isEmpty();
    }
    return false;
}

std::optional<TweekTokens> SqliteDatabaseService::getTweekTokens(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT tweek_token, tweek_refresh_token FROM "User"
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error getting Tweek tokens:" << query.lastError().text();
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

bool SqliteDatabaseService::saveTweekTaskId(int localTaskId, const QString& tweekTaskId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "Task" SET tweek_task_id = :tweek_id WHERE task_id = :local_id)");
    query.bindValue(":tweek_id", tweekTaskId);
    query.bindValue(":local_id", localTaskId);

    if (!query.exec()) {
        qCritical() << "Error saving Tweek Task ID:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqliteDatabaseService::saveTweekDefaultCalendar(int userId, const QString& calendarId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "User" SET tweek_default_calendar_id = :calendar_id WHERE user_id = :user_id)");
    query.bindValue(":calendar_id", calendarId);
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error saving default calendar:" << query.lastError().text();
        return false;
    }
    return true;
}

QString SqliteDatabaseService::getTweekDefaultCalendar(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(SELECT tweek_default_calendar_id FROM "User" WHERE user_id = :user_id)");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error getting default calendar:" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        return query.value(0).toString();
    }
    return QString();
}
void SqliteDatabaseService::clearTweekData(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE "User"
        SET tweek_token = NULL, tweek_refresh_token = NULL, tweek_default_calendar_id = NULL
        WHERE user_id = :user_id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qCritical() << "Error clearing Tweek data for user" << userId << ":" << query.lastError().text();
    } else {
        qDebug() << "Tweek data for user" << userId << "cleared successfully.";
    }
}

bool SqliteDatabaseService::saveAuthToken(int userId, const QString& token)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "User" SET auth_token = :token WHERE user_id = :user_id)");
    query.bindValue(":token", token);
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        qCritical() << "Error saving auth token:" << query.lastError().text();
        return false;
    }
    return true;
}

void SqliteDatabaseService::clearAuthToken(int userId)
{
    QSqlQuery query(m_db);
    query.prepare(R"(UPDATE "User" SET auth_token = NULL WHERE user_id = :user_id)");
    query.bindValue(":user_id", userId);
    if (!query.exec()) {
        qCritical() << "Error clearing auth token:" << query.lastError().text();
    }
}

QVariantMap SqliteDatabaseService::findUserByToken(const QString& token)
{
    if (token.isEmpty()) return QVariantMap();
    QSqlQuery query;
    query.prepare(R"(SELECT user_id FROM "User" WHERE auth_token = :token)");
    query.bindValue(":token", token);
    if (!query.exec()) {
        qCritical() << "Error finding user by token:" << query.lastError().text();
        return QVariantMap();
    }
    if (query.next()) {
        QVariantMap userData;
        userData["user_id"] = query.value("user_id").toInt();
        return userData;
    }
    return QVariantMap();
}
