#pragma once

#include <QObject>
#include <QDateTime>
#include <QVector>
#include <QString>

/**
 * @brief Структура для представления учебного события при обмене с календарями.
 */
struct StudyEvent {
    QString id;
    QString title;
    QString description;
    QDateTime startTime;
    QDateTime endTime;
};

/**
 * @brief Интерфейс для абстракции взаимодействия с внешними календарями.
 * Скрывает детали реализации работы с Tweek, Google Calendar и т.д.
 */
class ICalendarService : public QObject
{
    Q_OBJECT

public:
    virtual ~ICalendarService() = default;

    /**
     * @brief Получает список событий из календаря за указанный период.
     * @param from Начало периода.
     * @param to Конец периода.
     * @return Вектор событий.
     */
    virtual QVector<StudyEvent> getEvents(const QDateTime& from, const QDateTime& to) = 0;

    /**
     * @brief Добавляет новое событие в календарь.
     * @param event Событие для добавления.
     * @return true в случае успеха, иначе false.
     */
    virtual bool addEvent(const StudyEvent& event) = 0;

    /**
     * @brief Обновляет существующее событие в календаре.
     * @param event Событие с обновленными данными.
     * @return true в случае успеха, иначе false.
     */
    virtual bool updateEvent(const StudyEvent& event) = 0;

    /**
     * @brief Удаляет событие из календаря по его ID.
     * @param eventId Уникальный идентификатор события.
     * @return true в случае успеха, иначе false.
     */
    virtual bool deleteEvent(const QString& eventId) = 0;

signals:
    void eventsChanged();
    void errorOccurred(const QString& errorMessage);
};
