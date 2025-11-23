#pragma once
#include "db/IDatabaseService.h"
#include <QSqlDatabase>

class SqliteDatabaseService : public IDatabaseService
{
    Q_OBJECT

public:
    SqliteDatabaseService(QObject* parent = nullptr);
    ~SqliteDatabaseService() override;

    bool connectToSource() override;
    void disconnectFromSource() override;

    QVector<TaskDisplayData> getTasksForUser(int userId) override;
    bool addTask(const QString& title, const QString& description, int userId, const QString& tweekId = QString()) override;
    QString getTaskTitle(int taskId) override;
    bool addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime) override;
    QVector<qint64> getWeeklyTaskStats(int taskId, const QDate& weekStartDate) override;
    QVector<TaskTimeSummary> getTaskTimeSummaries(int userId) override;
    QVariantMap getTaskDetails(int taskId) override;
    bool clearTweekTaskId(int localTaskId) override;
    bool updateTask(int taskId, const QString& title, const QString& description) override;
    bool deactivateTask(int taskId) override;
    bool saveTweekTaskId(int localTaskId, const QString& tweekTaskId) override;
    bool saveTweekDefaultCalendar(int userId, const QString& calendarId) override;

    bool saveTweekTokens(int userId, const QString& idToken, const QString& refreshToken) override;
    std::optional<TweekTokens> getTweekTokens(int userId) override;
    QString getTweekDefaultCalendar(int userId) override;
    void clearTweekData(int userId) override;

private:
    void initializeDatabase();
    QSqlDatabase m_db;
    QString m_dbPath;
};
