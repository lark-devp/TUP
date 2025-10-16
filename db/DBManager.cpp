#include "DBManager.h"
#include <QSqlError>
#include <QDebug>

DBManager::DBManager() {
    // Регистрируем драйвер PostgreSQL
    m_db = QSqlDatabase::addDatabase("QPSQL");
}

DBManager::~DBManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

DBManager& DBManager::instance() {
    static DBManager instance;  // Создаётся один раз за всю программу
    return instance;
}

bool DBManager::connect(const QString& host,
                        const QString& dbName,
                        const QString& user,
                        const QString& password,
                        int port) {
    if (m_db.isOpen()) {
        return true; // Уже подключен
    }

    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open()) {
        qWarning() << "Ошибка подключения к PostgreSQL:"
                   << m_db.lastError().text();
        return false;
    }

    qDebug() << "Подключение к PostgreSQL успешно!";
    return true;
}

QSqlDatabase DBManager::database() const {
    return m_db;
}
