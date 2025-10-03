#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>
#include "ui/interfaces/ITaskSelectionView.h"

/**
 * @brief Интерфейс для абстракции взаимодействия с базой данных.
 * Позволяет приложению работать с любой БД (PostgreSQL, Firestore и т.д.),
 * не меняя основной код.
 */
class IDatabaseService : public QObject
{
    Q_OBJECT

public:
    explicit IDatabaseService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IDatabaseService() = default;
    /**
     * @brief Проверяет учетные данные пользователя.
     * @param username Имя пользователя.
     * @param password Пароль.
     * @return QVariantMap с данными пользователя (например, user_id) в случае успеха,
     * или пустой QVariantMap в случае неудачи.
     */
    virtual QVariantMap authenticateUser(const QString& username, const QString& password) = 0;

    /**
     * @brief Получает список задач для конкретного пользователя.
     * @param userId ID пользователя.
     * @return Вектор задач для отображения.
     */
    virtual QVector<TaskDisplayData> getTasksForUser(int userId) = 0;

    /**
     * @brief Подключается к источнику данных.
     * @return true в случае успеха, иначе false.
     */
    virtual bool connectToSource() = 0;

    /**
     * @brief Отключается от источника данных.
     */
    virtual void disconnectFromSource() = 0;
    /**
     * @brief Добавляет новую задачу для указанного пользователя.
     * @param title Название задачи.
     * @param description Описание задачи.
     * @param userId ID пользователя, которому принадлежит задача.
     * @return true в случае успеха, иначе false.
     */
    virtual bool addTask(const QString& title, const QString& description, int userId) = 0;

signals:
    void connectionStatusChanged(bool isConnected);
    void errorOccurred(const QString& errorMessage);
};
