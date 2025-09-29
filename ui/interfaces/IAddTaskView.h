#pragma once

#include "IView.h"
#include <QObject>
#include <QString>

/**
 * @brief Интерфейс для окна добавления/редактирования задачи.
 */
class IAddTaskView : public IView
{
    Q_OBJECT

public:
    // Этот конструктор будет принимать 'parent' и передавать его дальше в IView.
    explicit IAddTaskView(QWidget * parent = nullptr) : IView(parent) {}

    ~IAddTaskView() override = default;

    // Методы для управления видом
    virtual void clearForm() = 0;
    virtual void showValidationError(const QString& message) = 0;
    virtual void setTaskData(const QString& title, const QString& description) = 0;

signals:
    // Сигналы о действиях пользователя
    void saveTaskRequested(const QString& title, const QString& description);
    void cancelRequested();
};
