#pragma once

#include "ui/interfaces/ITimerView.h" // Подключаем скорректированный интерфейс

// Предварительные объявления классов Qt
class QLabel;
class QPushButton;
class QCloseEvent;

class MinimalTimerView : public ITimerView
{
    Q_OBJECT

public:
    explicit MinimalTimerView(QWidget *parent = nullptr);
    ~MinimalTimerView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---
    // Из IView
    QWidget* getWidget() override;

    // Из ITimerView
    void setTaskTitle(const QString& title) override;
    void updateDisplayedTime(const QString& timeString) override;
    void setTimerControlsEnabled(bool canPause, bool canStop) override;

protected:
    // Переопределяем событие закрытия окна для отправки сигнала
    void closeEvent(QCloseEvent *event) override;

private:
    // Указатели на UI-элементы
    QLabel* m_taskTitleLabel;
    QLabel* m_timeDisplayLabel;
    QPushButton* m_pauseButton;
    QPushButton* m_stopButton;
};
