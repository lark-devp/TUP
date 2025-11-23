#include "TweekApiServiceImpl.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QUrlQuery>


TweekApiServiceImpl::TweekApiServiceImpl(QObject *parent)
    : ITweekApiService(parent),
    m_apiKey("AIzaSyC7_JO56peYl_eD9QODZlLwZpMclLUoC9s"),
    m_signInUrl("https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + m_apiKey),
    m_refreshUrl("https://securetoken.googleapis.com/v1/token?key=" + m_apiKey),
    m_calendarsUrl("https://tweek.so/api/v1/calendars"),
    m_tasksUrl("https://tweek.so/api/v1/tasks")
{
    m_networkManager = new QNetworkAccessManager(this);
}

// Вспомогательный метод для создания запросов с авторизацией
QNetworkRequest TweekApiServiceImpl::createAuthorizedRequest(const QUrl& url, const QString& idToken)
{
    QNetworkRequest request(url);
    qDebug() << "Creating authorized request for" << url << "with token:" << (idToken.isEmpty() ? "EMPTY!" : "present");


    request.setRawHeader("Authorization", ("Bearer " + idToken).toUtf8());


    request.setHeader(QNetworkRequest::UserAgentHeader, "TimeTrackerApp/1.0");

    return request;
}

void TweekApiServiceImpl::fetchCalendars(const QString& idToken)
{
    QNetworkRequest request = createAuthorizedRequest(m_calendarsUrl, idToken);
    QNetworkReply* reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onCalendarsReplyFinished);
}

// ----- ОБНОВЛЕННЫЙ СЛОТ ДЛЯ КАЛЕНДАРЕЙ -----
void TweekApiServiceImpl::onCalendarsReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (redirectionTarget.isValid()) {
        QUrl newUrl = reply->url().resolved(redirectionTarget.toUrl());
        qDebug() << "Redirecting calendar request to:" << newUrl;

        QNetworkRequest newRequest(newUrl);
        // ВАЖНО: Копируем заголовок авторизации из старого запроса в новый
        newRequest.setRawHeader("Authorization", reply->request().rawHeader("Authorization"));

        QNetworkReply* newReply = m_networkManager->get(newRequest);
        // Подключаем новый ответ к этому же слоту для рекурсивной обработки
        connect(newReply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onCalendarsReplyFinished);

        reply->deleteLater();
        return; // Завершаем обработку старого ответа
    }


    if (reply->error() != QNetworkReply::NoError) {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qCritical() << "Calendar fetch network error:" << reply->errorString() << "| HTTP Status:" << httpStatusCode;
        emit calendarsFetchFailed("Сетевая ошибка: " + reply->errorString());
        reply->deleteLater();
        return;
    }


    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isArray()) {
        emit calendarsFetchFailed("Некорректный ответ от сервера (ожидался массив).");
        reply->deleteLater();
        return;
    }

    QVector<TweekCalendar> calendars;
    for (const QJsonValue& value : doc.array()) {
        QJsonObject obj = value.toObject();
        TweekCalendar calendar;
        calendar.id = obj["id"].toString();
        calendar.name = obj["name"].toString();
        if (!calendar.id.isEmpty() && !calendar.name.isEmpty()) {
            calendars.append(calendar);
        }
    }
    emit calendarsFetchSuccess(calendars);
    reply->deleteLater();
}

void TweekApiServiceImpl::fetchTodayTasks(const QString& idToken, const QString& calendarId)
{
    QUrl urlWithQuery = m_tasksUrl;
    QUrlQuery query;
    query.addQueryItem("calendarId", calendarId);

    QString today = QDate::currentDate().toString(Qt::ISODate);
    query.addQueryItem("dateFrom", today);
    query.addQueryItem("dateTo", today);

    urlWithQuery.setQuery(query);

    QNetworkRequest request = createAuthorizedRequest(urlWithQuery, idToken);
    QNetworkReply* reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onTasksReplyFinished);
}


void TweekApiServiceImpl::onTasksReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (redirectionTarget.isValid()) {
        QUrl newUrl = reply->url().resolved(redirectionTarget.toUrl());
        qDebug() << "Redirecting task request to:" << newUrl;

        QNetworkRequest newRequest(newUrl);
        newRequest.setRawHeader("Authorization", reply->request().rawHeader("Authorization"));

        QNetworkReply* newReply = m_networkManager->get(newRequest);
        connect(newReply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onTasksReplyFinished);

        reply->deleteLater();
        return;
    }


    if (reply->error() != QNetworkReply::NoError) {
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qCritical() << "Task fetch network error:" << reply->errorString() << "| HTTP Status:" << httpStatusCode;
        emit tasksFetchFailed("Сетевая ошибка: " + reply->errorString());
        reply->deleteLater();
        return;
    }



    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isObject()) {
        emit tasksFetchFailed("Некорректный ответ от сервера (ожидался объект).");
        reply->deleteLater();
        return;
    }

    QVector<TweekTask> tasks;
    QJsonObject rootObj = doc.object();
    if (rootObj.contains("data") && rootObj["data"].isArray()) {
        for (const QJsonValue& value : rootObj["data"].toArray()) {
            QJsonObject obj = value.toObject();
            TweekTask task;
            task.id = obj["id"].toString();
            task.title = obj["text"].toString();
            task.description = obj["note"].toString();
            task.done = obj["done"].toBool(); // <-- ДОБАВИТЬ ЭТУ СТРОКУ

            // Можно добавить отладочный вывод, чтобы убедиться, что статус считывается
            qDebug() << "[DEBUG 1: PARSER]"
                     << "ID:" << task.id
                     << "Title:" << task.title
                     << "Description:" << task.description
                     << "Done:" << task.done; // <-- И эту для отладки

            if(!task.id.isEmpty() && !task.title.isEmpty()){
                tasks.append(task);
            }
        }
    }
    emit tasksFetchSuccess(tasks);
    reply->deleteLater();
}




void TweekApiServiceImpl::authenticate(const QString &email, const QString &password)
{
    QJsonObject requestBody;
    requestBody["email"] = email;
    requestBody["password"] = password;
    requestBody["returnSecureToken"] = true;
    QJsonDocument doc(requestBody);
    QByteArray jsonData = doc.toJson();

    QNetworkRequest request(m_signInUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, jsonData);
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onAuthenticationReplyFinished);
}

void TweekApiServiceImpl::onAuthenticationReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error() != QNetworkReply::NoError) {
        emit authenticationFailed("Сетевая ошибка: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("error")) {
        QString message = jsonObj["error"].toObject()["message"].toString();
        emit authenticationFailed("Ошибка: " + message);
    } else if (jsonObj.contains("idToken") && jsonObj.contains("refreshToken")) {
        QString idToken = jsonObj["idToken"].toString();
        QString refreshToken = jsonObj["refreshToken"].toString();
        emit authenticationSuccess(idToken, refreshToken);
    } else {
        emit authenticationFailed("Получен некорректный ответ от сервера.");
    }

    reply->deleteLater();
}

void TweekApiServiceImpl::refreshToken(const QString &token)
{
    QUrlQuery query;
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("refresh_token", token);
    QByteArray postData = query.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkRequest request(m_refreshUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Создаем ответ и сразу же подключаем к нему слот onRefreshTokenReplyFinished
    QNetworkReply* reply = m_networkManager->post(request, postData);

    // Используем this в качестве контекста, чтобы соединение автоматически разорвалось,
    // если TweekApiServiceImpl будет уничтожен до получения ответа.
    connect(reply, &QNetworkReply::finished, this, &TweekApiServiceImpl::onRefreshTokenReplyFinished);
}

void TweekApiServiceImpl::onRefreshTokenReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error() != QNetworkReply::NoError) {

        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray responseData = reply->readAll(); // Читаем тело ответа при ошибке

        // Выводим расширенную информацию в лог
        qCritical() << "Refresh token network error:" << reply->errorString()
                    << "| HTTP Status:" << httpStatusCode
                    << "| Server Response:" << responseData;
        QString errorMessage;
        if (reply->error() == QNetworkReply::ConnectionRefusedError || reply->error() == QNetworkReply::TimeoutError || httpStatusCode == 0) {
            errorMessage = "Не удалось подключиться к серверу. Проверьте ваше интернет-соединение.";
        } else {
            errorMessage = "Ошибка обновления токена: " + responseData;
        }

        emit authenticationFailed("Ошибка обновления токена: " + responseData); // Отправляем тело ответа


        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("error")) {
        QString message = jsonObj["error"].toObject()["message"].toString();
        emit authenticationFailed("Ошибка обновления токена: " + message);
    }
    else if (jsonObj.contains("id_token") && jsonObj.contains("refresh_token")) {
        QString idToken = jsonObj["id_token"].toString();
        QString refreshToken = jsonObj["refresh_token"].toString();
        emit authenticationSuccess(idToken, refreshToken);
    } else {
        emit authenticationFailed("Получен некорректный ответ от сервера.");
    }

    reply->deleteLater();
}
void TweekApiServiceImpl::createTaskInTweek(const QString& idToken, const QString& calendarId, const QString& title, const QString& description, int localTaskId)
{
    QJsonObject taskObject;
    taskObject["text"] = title;
    taskObject["note"] = description;
    taskObject["date"] = QDate::currentDate().toString(Qt::ISODate); // Создаем на сегодня
    taskObject["calendarId"] = calendarId;
    taskObject["done"] = false;
    taskObject["gcal"] = false;

    QJsonDocument doc(taskObject);
    QByteArray jsonData = doc.toJson();

    QNetworkRequest request = createAuthorizedRequest(m_tasksUrl, idToken);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, jsonData);

    // Используем лямбду, чтобы передать localTaskId в обработчик
    connect(reply, &QNetworkReply::finished, this, [this, reply, localTaskId](){
        if (!reply) return;


        if (reply->error() != QNetworkReply::NoError) {
            // Читаем тело ответа, в котором содержится детальная ошибка от Tweek
            QByteArray errorBody = reply->readAll();
            int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

            // Формируем подробное сообщение об ошибке
            QString detailedError = QString("Сетевая ошибка: %1 (Код: %2). Ответ сервера: %3")
                                        .arg(reply->errorString())
                                        .arg(httpStatusCode)
                                        .arg(QString::fromUtf8(errorBody));

            qWarning() << "Ошибка создания задачи в Tweek (local ID:" << localTaskId << "):" << detailedError;
            emit taskCreateFailed(localTaskId, detailedError);
        } else {
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            if (doc.isObject() && doc.object().contains("id")) {
                QString newId = doc.object()["id"].toString();
                emit taskCreateSuccess(localTaskId, newId);
            } else {
                emit taskCreateFailed(localTaskId, "Не удалось получить ID новой задачи из ответа.");
            }
        }
        reply->deleteLater();
    });
}

void TweekApiServiceImpl::updateTaskInTweek(const QString& idToken, const QString& tweekTaskId, const QString& title, const QString& description, int localTaskId)
{
    QJsonObject taskObject;
    taskObject["text"] = title;
    taskObject["note"] = description;

    QJsonDocument doc(taskObject);
    QByteArray jsonData = doc.toJson();

    QUrl updateUrl(m_tasksUrl.toString() + "/" + tweekTaskId);

    QNetworkRequest request = createAuthorizedRequest(updateUrl, idToken);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->sendCustomRequest(request, "PATCH", jsonData);

    // --- ИЗМЕНЕНИЯ В ЛЯМБДЕ ---
    connect(reply, &QNetworkReply::finished, this, [this, reply, localTaskId](){
        if (!reply) return;

        if (reply->error() != QNetworkReply::NoError) {
            int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QString errorString = "Ошибка обновления: " + reply->errorString() + " " + reply->readAll();
            emit taskUpdateFailed(localTaskId, errorString, httpStatusCode);
        } else {
            emit taskUpdateSuccess(localTaskId);
        }
        reply->deleteLater();
    });
}
