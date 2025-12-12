#pragma once

#include <QObject>
#include <QString>


struct TweekCalendar {
    QString id;
    QString name;
};

struct TweekTask {
    QString id;
    QString title;
    QString description;
    bool done;
};


class ITweekApiService : public QObject
{
    Q_OBJECT

public:
    explicit ITweekApiService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ITweekApiService() = default;

    virtual void authenticate(const QString& email, const QString& password) = 0;
    virtual void refreshToken(const QString& token) = 0;

    virtual void fetchCalendars(const QString& idToken) = 0;


    virtual void fetchTodayTasks(const QString& idToken, const QString& calendarId) = 0;
    virtual void createTaskInTweek(const QString& idToken, const QString& calendarId, const QString& title, const QString& description, int localTaskId) = 0;
    virtual void updateTaskInTweek(const QString& idToken, const QString& tweekTaskId, const QString& title, const QString& description, int localTaskId) = 0;

signals:

    void authenticationSuccess(const QString& idToken, const QString& refreshToken);

    void authenticationFailed(const QString& errorMessage);

    void calendarsFetchSuccess(const QVector<TweekCalendar>& calendars);
    void calendarsFetchFailed(const QString& errorMessage);

    void tasksFetchSuccess(const QVector<TweekTask>& tasks);
    void tasksFetchFailed(const QString& errorMessage);
    void taskCreateSuccess(int localTaskId, const QString& newTweekTaskId);
    void taskCreateFailed(int localTaskId, const QString& errorMessage);
    void taskUpdateSuccess(const QString& tweekTaskId);
    void taskUpdateFailed(const QString& tweekTaskId, const QString& errorMessage);
    void taskUpdateSuccess(int localTaskId);
    void taskUpdateFailed(int localTaskId, const QString& errorMessage, int httpStatusCode);
};
