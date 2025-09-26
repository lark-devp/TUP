#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

/**
 * @brief Интерфейс для абстракции взаимодействия с базой данных.
 * Позволяет приложению работать с любой БД (PostgreSQL, Firestore и т.д.),
 * не меняя основной код.
 */
class IDatabaseService : public QObject
{
    Q_OBJECT

public:
    virtual ~IDatabaseService() = default;

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
     * @brief Сохраняет данные в указанную коллекцию/таблицу.
     * @param collection Название коллекции или таблицы.
     * @param documentId Уникальный идентификатор записи.
     * @param data Данные для сохранения в формате ключ-значение.
     * @return true в случае успеха, иначе false.
     */
    virtual bool saveData(const QString& collection, const QString& documentId, const QVariantMap& data) = 0;

    /**
     * @brief Загружает данные из указанной коллекции/таблицы.
     * @param collection Название коллекции или таблицы.
     * @param documentId Уникальный идентификатор записи.
     * @return Загруженные данные. Если запись не найдена, возвращает пустой QVariantMap.
     */
    virtual QVariantMap loadData(const QString& collection, const QString& documentId) = 0;

signals:
    void connectionStatusChanged(bool isConnected);
    void errorOccurred(const QString& errorMessage);
};
