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

    // Этот метод вам не понадобится, так как мы будем использовать
    // именованное соединение, но для полноты картины можно его оставить.
    bool saveData(const QString&, const QString&, const QVariantMap&) override { return false; }
    QVariantMap loadData(const QString&, const QString&) override { return QVariantMap(); }

private:
    QSqlDatabase m_db; // <-- 2. Добавляем объект для хранения соединения
};
