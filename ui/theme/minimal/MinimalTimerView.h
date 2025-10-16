#pragma once

#include "ui/interfaces/ITimerView.h"

// Предварительные объявления
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

    // --- РЕАЛИЗАЯ ИНТЕРФЕЙСОВ ---
    QWidget* getWidget() override;
    void setTaskTitle(const QString& title) override;
    void updateDisplayedTime(const QString& timeString) override;
    void showModeSelection() override;
    void displayPomodoroState(int remainingSessions, bool isWorkSession) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onPomodoroButtonClicked();

private:
    // --- ОБЩИЕ UI ЭЛЕМЕНТЫ ---
    QStackedWidget* m_mainStack;
    QLabel* m_taskTitleLabel;

    // --- UI для выбора режима (Страница 0) ---
    QWidget* createModeSelectionPage();

    // --- UI для обычного таймера (Страница 1) ---
    QLabel* m_stopwatchTimeLabel;
    QWidget* createStopwatchPage();

    // --- UI для Помодоро (Страница 2) ---
    QLabel* m_pomodoroTimeLabel;
    QLabel* m_pomodoroStateLabel;
    QLabel* m_pomodoroSessionLabel; // Для отображения помидорок
    QWidget* createPomodoroPage();

};
