#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QDateTime>
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
    /**
     * @brief Получает название задачи по её ID.
     * @param taskId Уникальный идентификатор задачи.
     * @return Название задачи или пустая строка, если не найдена.
     */
    virtual QString getTaskTitle(int taskId) = 0;

    /**
     * @brief Добавляет запись о сессии трекинга времени в базу данных.
     * @param taskId ID задачи, к которой относится запись.
     * @param startTime Время начала сессии.
     * @param endTime Время окончания сессии.
     * @return true в случае успеха, иначе false.
     */
    virtual bool addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime) = 0;
    /**
     * @brief Получает статистику по задаче за неделю, сгруппированную по дням.
     * @param taskId ID задачи.
     * @param weekStartDate Дата понедельника нужной недели.
     * @return Вектор из 7 элементов (qint64), где каждый элемент - сумма минут для дня недели (Пн-Вс).
     */
    virtual QVector<qint64> getWeeklyTaskStats(int taskId, const QDate& weekStartDate) = 0;

signals:
    void connectionStatusChanged(bool isConnected);
    void errorOccurred(const QString& errorMessage);
};
