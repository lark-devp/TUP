#pragma once
#include "db/IDatabaseService.h"
#include <QSqlDatabase>

class PostgresDatabaseService : public IDatabaseService
{
    Q_OBJECT

public:
    PostgresDatabaseService(QObject* parent = nullptr);
    ~PostgresDatabaseService() override;

    bool connectToSource() override;
    void disconnectFromSource() override;
    QVariantMap authenticateUser(const QString& username, const QString& password) override;
    bool addUser(const QString& username, const QString& email, const QString& password) override;
    QVector<TaskDisplayData> getTasksForUser(int userId) override;
    bool addTask(const QString& title, const QString& description, int userId, const QString& tweekId = QString()) override;
    QString getTaskTitle(int taskId) override;
    bool addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime) override;
    QVector<qint64> getWeeklyTaskStats(int taskId, const QDate& weekStartDate) override;
    QVector<TaskTimeSummary> getTaskTimeSummaries(int userId) override;
    bool saveTweekTokens(int userId, const QString& idToken, const QString& refreshToken) override;
    bool hasTweekTokens(int userId) override;
    std::optional<TweekTokens> getTweekTokens(int userId) override;
    QVariantMap getTaskDetails(int taskId) override;
    bool updateTask(int taskId, const QString& title, const QString& description) override;
    bool deactivateTask(int taskId) override;
    bool saveTweekTaskId(int localTaskId, const QString& tweekTaskId) override;
    bool saveTweekDefaultCalendar(int userId, const QString& calendarId) override;
    QString getTweekDefaultCalendar(int userId) override;
    void clearTweekData(int userId) override;


private:
    QSqlDatabase m_db;
};
