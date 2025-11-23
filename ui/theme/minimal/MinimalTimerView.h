#pragma once

#include "ui/interfaces/ITimerView.h"


class QLabel;
class QPushButton;
class QCloseEvent;
class QStackedWidget;
class QWidget;

class MinimalTimerView : public ITimerView
{
    Q_OBJECT

public:
    explicit MinimalTimerView(QWidget *parent = nullptr);
    ~MinimalTimerView() override = default;

    QWidget* getWidget() override;
    void setTaskTitle(const QString& title) override;
    void updateDisplayedTime(const QString& timeString) override;
    void showModeSelection() override;
    void displayPomodoroState(int totalSessions, int completedSessions, bool isWorkSession) override;
    void showStopwatchMode() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onPomodoroButtonClicked();

private:

    QStackedWidget* m_mainStack;
    QLabel* m_taskTitleLabel;


    QWidget* createModeSelectionPage();


    QLabel* m_stopwatchTimeLabel;
    QWidget* createStopwatchPage();


    QLabel* m_pomodoroTimeLabel;
    QLabel* m_pomodoroStateLabel;
    QLabel* m_pomodoroSessionLabel;
    QPushButton* m_skipRestButton;
    QWidget* createPomodoroPage();

};
