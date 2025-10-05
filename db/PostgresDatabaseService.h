#pragma once
#include "db/IDatabaseService.h"
#include <QSqlDatabase> // <-- 1. Подключаем основной класс для работы с БД

class PostgresDatabaseService : public IDatabaseService
{
    Q_OBJECT
    // ... (объявления ваших публичных методов) ...
public:
    PostgresDatabaseService(QObject* parent = nullptr);
    ~PostgresDatabaseService() override;

    // --- Реализация методов интерфейса ---
    bool connectToSource() override;
    void disconnectFromSource() override;
    QVariantMap authenticateUser(const QString& username, const QString& password) override;
    QVector<TaskDisplayData> getTasksForUser(int userId) override;

    bool addTask(const QString& title, const QString& description, int userId) override;

    QString getTaskTitle(int taskId) override;
    bool addTimeTrackingEntry(int taskId, const QDateTime& startTime, const QDateTime& endTime) override;
    QVector<qint64> getWeeklyTaskStats(int taskId, const QDate& weekStartDate) override;

private:
    QSqlDatabase m_db; // <-- 2. Добавляем объект для хранения соединения
};
