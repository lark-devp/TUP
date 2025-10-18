#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QDateTime>
#include <optional>
#include "ui/interfaces/ITaskSelectionView.h"
#include "ui/interfaces/IAllTasksStatisticsView.h"


// Структура для хранения токенов
struct TweekTokens {
    QString idToken;
    QString refreshToken;
};


/**
 * @brief Интерфейс для абстракции взаимодействия с базой данных.
 */
class IDatabaseService : public QObject
{
    Q_OBJECT

public:
    explicit IDatabaseService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IDatabaseService() = default;

    virtual bool connectToSource() = 0;
    virtual void disconnectFromSource() = 0;

    //  Пользователи
    virtual QVariantMap authenticateUser(const QString& username, const QString& password) = 0;
    virtual bool addUser(const QString& username, const QString& email, const QString& password) = 0;

    //  Задачи и Время
    virtual QVector<TaskDisplayData> getTasksForUser(int userId) = 0;
    virtual bool addTask(const QString& title, const QString& description, int userId, const QString& tweekId = QString()) = 0;
    virtual QString getTaskTitle(int taskId) = 0;
    virtual bool addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime) = 0;
    virtual QVector<qint64> getWeeklyTaskStats(int taskId, const QDate& weekStartDate) = 0;
    virtual QVector<TaskTimeSummary> getTaskTimeSummaries(int userId) = 0;
    virtual QVariantMap getTaskDetails(int taskId) = 0;
    virtual bool updateTask(int taskId, const QString& title, const QString& description) = 0;
    virtual bool deactivateTask(int taskId) = 0;
    virtual bool saveTweekTaskId(int localTaskId, const QString& tweekTaskId) = 0;
    virtual bool saveTweekDefaultCalendar(int userId, const QString& calendarId) = 0;

    // Tweek API
    virtual bool saveTweekTokens(int userId, const QString& idToken, const QString& refreshToken) = 0;
    virtual std::optional<TweekTokens> getTweekTokens(int userId) = 0;
    virtual QString getTweekDefaultCalendar(int userId) = 0;



    virtual bool hasTweekTokens(int userId) = 0;
    virtual void clearTweekData(int userId) = 0;

signals:
    void errorOccurred(const QString& errorMessage);
};
