#pragma once

#include "IView.h"
#include <QObject>
#include <QString>

/**
 * @brief Интерфейс для окна редактирования/удаления задачи.
 */
class IEditTaskView : public IView
{
    Q_OBJECT

public:
    // Конструктор, передающий 'parent' в базовый класс IView.
    explicit IEditTaskView(QWidget * parent = nullptr) : IView(parent) {}
    ~IEditTaskView() override = default;

    // Методы для управления данными и состоянием вида
    virtual void setTaskData(const QString& title, const QString& description) = 0;
    virtual void showValidationError(const QString& message) = 0;

signals:
    // Сигналы о действиях пользователя
    void saveTaskRequested(const QString& title, const QString& description);
    void deleteTaskRequested();
    void cancelRequested();
};
