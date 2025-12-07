#pragma once

#include "IView.h"
#include <QObject>
#include <QString>


class IEditTaskView : public IView
{
    Q_OBJECT

public:
    explicit IEditTaskView(QWidget * parent = nullptr) : IView(parent) {}
    ~IEditTaskView() override = default;

    virtual void setTaskData(const QString& title, const QString& description) = 0;
    virtual void showValidationError(const QString& message) = 0;

signals:
    void saveTaskRequested(const QString& title, const QString& description);
    void deleteTaskRequested();
    void cancelRequested();
};
