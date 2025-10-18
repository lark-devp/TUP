#pragma once

#include "IView.h"
#include <QObject>
#include <QString>
#include <QVector>
#include "calendar/ITweekApiService.h"



class ISynchronizationView : public IView
{
    Q_OBJECT

public:
    enum class ViewState {
        Login,
        Sync
    };

    explicit ISynchronizationView(QWidget * parent = nullptr) : IView(parent) {}
    ~ISynchronizationView() override = default;

    // Методы для управления видом
    virtual void showState(ViewState state) = 0;
    virtual void updateStatus(const QString& statusMessage) = 0;
    virtual void logMessage(const QString& message) = 0;
    virtual void setProgress(int percentage) = 0;

    // Новые методы для отображения данных
    virtual void displayCalendars(const QVector<TweekCalendar>& calendars) = 0;
    virtual void displayTasks(const QVector<TweekTask>& tasks) = 0;
    virtual void setControlsEnabled(bool enabled) = 0;


signals:
    void closeRequested();
    void connectRequested(const QString& email, const QString& password);


    void calendarsRequested();
    void tasksRequested(const QString& calendarId);
    void tasksSelected(const QVector<TweekTask>& selectedTasks);
    void disconnectRequested();

};
