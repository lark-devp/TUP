#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DBManager {
public:
    // Доступ к единственному экземпляру
    static DBManager& instance();

    // Подключение к БД
    bool connect(const QString& host,
                 const QString& dbName,
                 const QString& user,
                 const QString& password,
                 int port = 5432);

    // Получить объект БД
    QSqlDatabase database() const;

private:
    // Приватный конструктор (синглтон)
    DBManager();
    ~DBManager();

    // Запрещаем копирование и присваивание
    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
