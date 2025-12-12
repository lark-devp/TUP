#pragma once

#include "IView.h"
#include <QObject>
#include <QString>


class IAddTaskView : public IView
{
    Q_OBJECT

public:

    explicit IAddTaskView(QWidget * parent = nullptr) : IView(parent) {}

    ~IAddTaskView() override = default;


    virtual void clearForm() = 0;
    virtual void showValidationError(const QString& message) = 0;
    virtual void setTaskData(const QString& title, const QString& description) = 0;

signals:

    void saveTaskRequested(const QString& title, const QString& description);
    void cancelRequested();
};
