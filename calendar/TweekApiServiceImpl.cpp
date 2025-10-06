#include "TweekApiServiceImpl.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUrlQuery>

TweekApiServiceImpl::TweekApiServiceImpl(QObject *parent)
    : ITweekApiService(parent),
    m_signInUrl("https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + m_apiKey)
{
    m_networkManager = new QNetworkAccessManager(this);
}

void TweekApiServiceImpl::authenticate(const QString &email, const QString &password)
{
    // 1. Создаем JSON-тело запроса
    QJsonObject requestBody;
    requestBody["email"] = email;
    requestBody["password"] = password;
    requestBody["returnSecureToken"] = true;
    QJsonDocument doc(requestBody);
    QByteArray jsonData = doc.toJson();

    // 2. Создаем и настраиваем запрос
    QNetworkRequest request(m_signInUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 3. Отправляем POST-запрос
    QNetworkReply* reply = m_networkManager->post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onAuthenticationReplyFinished);
}

void TweekApiServiceImpl::onAuthenticationReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    // Проверяем на наличие сетевых ошибок
    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "Сетевая ошибка:" << reply->errorString();
        emit authenticationFailed("Сетевая ошибка: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    // Читаем и парсим ответ
    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    // Google API может вернуть 200 OK, но с объектом ошибки внутри JSON
    if (jsonObj.contains("error")) {
        QString message = jsonObj["error"].toObject()["message"].toString();
        qWarning() << "Ошибка API аутентификации:" << message;
        emit authenticationFailed("Ошибка: " + message);
    } else if (jsonObj.contains("idToken") && jsonObj.contains("refreshToken")) {
        QString idToken = jsonObj["idToken"].toString();
        QString refreshToken = jsonObj["refreshToken"].toString();
        qInfo() << "Аутентификация Tweek успешна!";
        emit authenticationSuccess(idToken, refreshToken);
    } else {
        qCritical() << "Неожиданный ответ от API:" << responseData;
        emit authenticationFailed("Получен некорректный ответ от сервера.");
    }

    reply->deleteLater();
}
void TweekApiServiceImpl::refreshToken(const QString &token)
{
    // 1. Создаем тело запроса в формате x-www-form-urlencoded
    // QUrlQuery идеально подходит для этого, так как он сам заботится о кодировании.
    QUrlQuery query;
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("refresh_token", token);
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();

    // 2. Создаем и настраиваем запрос
    QNetworkRequest request(m_refreshUrl);
    // ВАЖНО: Устанавливаем правильный Content-Type, как в документации
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // 3. Отправляем POST-запрос
    QNetworkReply* reply = m_networkManager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onRefreshTokenReplyFinished);
}
void TweekApiServiceImpl::onRefreshTokenReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "Сетевая ошибка при обновлении токена:" << reply->errorString();
        emit authenticationFailed("Сетевая ошибка: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    // Обработка ошибок, как и в первом методе
    if (jsonObj.contains("error")) {
        QString message = jsonObj["error"].toObject()["message"].toString();
        qWarning() << "Ошибка API обновления токена:" << message;
        emit authenticationFailed("Ошибка обновления токена: " + message);
    }
    // ВАЖНО: Проверяем ключи из документации для этого ответа (`id_token` и `refresh_token`)
    else if (jsonObj.contains("id_token") && jsonObj.contains("refresh_token")) {
        QString idToken = jsonObj["id_token"].toString();
        QString refreshToken = jsonObj["refresh_token"].toString();
        qInfo() << "Токен Tweek успешно обновлен!";
        // Отправляем тот же сигнал, что и при обычной аутентификации.
        // Контроллеру не важно, как мы получили токены, ему важно их получить.
        emit authenticationSuccess(idToken, refreshToken);
    } else {
        qCritical() << "Неожиданный ответ от API при обновлении токена:" << responseData;
        emit authenticationFailed("Получен некорректный ответ от сервера.");
    }

    reply->deleteLater();
}
