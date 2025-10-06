#pragma once

#include <QObject>
#include <QString>


// Структура для календаря
struct TweekCalendar {
    QString id;
    QString name;
};

// Структура для задачи из Tweek
struct TweekTask {
    QString id;
    QString title;
    QString description;
};


class ITweekApiService : public QObject
{
    Q_OBJECT

public:
    explicit ITweekApiService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ITweekApiService() = default;

    // Метод для запроса токенов по email и паролю
    virtual void authenticate(const QString& email, const QString& password) = 0;
    virtual void refreshToken(const QString& token) = 0;

    /**
     * @brief Запрашивает список календарей пользователя.
     * @param idToken Токен аутентификации.
     */
    virtual void fetchCalendars(const QString& idToken) = 0;

    /**
     * @brief Запрашивает список задач для календаря на сегодня.
     * @param idToken Токен аутентификации.
     * @param calendarId ID календаря.
     */
    virtual void fetchTodayTasks(const QString& idToken, const QString& calendarId) = 0;

signals:
    // Сигнал в случае успешного получения токенов
    void authenticationSuccess(const QString& idToken, const QString& refreshToken);
    // Сигнал в случае ошибки
    void authenticationFailed(const QString& errorMessage);

    void calendarsFetchSuccess(const QVector<TweekCalendar>& calendars);
    void calendarsFetchFailed(const QString& errorMessage);

    void tasksFetchSuccess(const QVector<TweekTask>& tasks);
    void tasksFetchFailed(const QString& errorMessage);
};
