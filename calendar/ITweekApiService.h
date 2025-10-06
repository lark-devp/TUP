#pragma once

#include <QObject>
#include <QString>

class ITweekApiService : public QObject
{
    Q_OBJECT

public:
    explicit ITweekApiService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ITweekApiService() = default;

    // Метод для запроса токенов по email и паролю
    virtual void authenticate(const QString& email, const QString& password) = 0;
    virtual void refreshToken(const QString& token) = 0;

signals:
    // Сигнал в случае успешного получения токенов
    void authenticationSuccess(const QString& idToken, const QString& refreshToken);
    // Сигнал в случае ошибки
    void authenticationFailed(const QString& errorMessage);
};
