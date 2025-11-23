#pragma once

#include "calendar/ITweekApiService.h"
#include <QNetworkAccessManager>
#include <QUrl>

class TweekApiServiceImpl : public ITweekApiService
{
    Q_OBJECT

public:
    explicit TweekApiServiceImpl(QObject *parent = nullptr);

    void authenticate(const QString& email, const QString& password) override;
    void refreshToken(const QString& token) override;
    void fetchCalendars(const QString& idToken) override;
    void fetchTodayTasks(const QString& idToken, const QString& calendarId) override;
    void createTaskInTweek(const QString& idToken, const QString& calendarId, const QString& title, const QString& description, int localTaskId) override;
    void updateTaskInTweek(const QString& idToken, const QString& tweekTaskId, const QString& title, const QString& description, int localTaskId) override;
private slots:
    void onAuthenticationReplyFinished();
    void onRefreshTokenReplyFinished();
    void onCalendarsReplyFinished();
    void onTasksReplyFinished();

private:
    QNetworkRequest createAuthorizedRequest(const QUrl& url, const QString& idToken);
    QNetworkAccessManager* m_networkManager;
    const QString m_apiKey = "AIzaSyD8L3xf8ELS_YeKMA04u7nLyxhkneOspcs";
    const QUrl m_signInUrl;
    const QUrl m_refreshUrl;
    const QUrl m_calendarsUrl;
    const QUrl m_tasksUrl;
};
