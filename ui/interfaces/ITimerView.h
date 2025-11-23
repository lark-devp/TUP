#pragma once

#include "IView.h"
#include <QWidget>
#include <QString>

class ITimerView : public IView
{
    Q_OBJECT

public:
    explicit ITimerView(QWidget* parent = nullptr) : IView(parent) {}

    ~ITimerView() override = default;

    virtual void setTaskTitle(const QString& title) = 0;
    virtual void updateDisplayedTime(const QString& timeString) = 0;
    virtual QWidget* getWidget() = 0;

    virtual void showModeSelection() = 0;
    virtual void displayPomodoroState(int totalSessions, int completedSessions, bool isWorkSession) = 0;
    virtual void showStopwatchMode() = 0;

signals:
    void stopClicked();
    void closeRequested();
    void timerModeSelected();
    void pomodoroModeSelected(int workMinutes, int restMinutes, int sessionCount);
    void skipRestRequested();

};


