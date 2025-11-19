#pragma once

#include "IView.h"
#include <QWidget>
#include <QString>

/**
 * @brief Интерфейс для окна с таймером.
 * @note Наследуется от QWidget, чтобы реализация могла быть виджетом,
 * как в примере MinimalTaskSelectionView.
 */
class ITimerView : public IView
{
    Q_OBJECT

public:
    explicit ITimerView(QWidget* parent = nullptr) : IView(parent) {}

    ~ITimerView() override = default;

    virtual void setTaskTitle(const QString& title) = 0;
    virtual void updateDisplayedTime(const QString& timeString) = 0;
    virtual QWidget* getWidget() = 0;

    /**
     * @brief Показывает начальный экран выбора режима (Таймер или Помодоро).
     */
    virtual void showModeSelection() = 0;
    /**
     * @brief Отображает состояние сессии Помодоро.
     * @param remainingSessions Количество оставшихся "помидорок" (рабочих сессий).
     * @param isWorkSession True, если текущая сессия - работа, false - если отдых.
     */
    virtual void displayPomodoroState(int remainingSessions, bool isWorkSession) = 0;
    virtual void showStopwatchMode() = 0;

signals:
    void stopClicked();
    void closeRequested();
    /**
     * @brief Пользователь выбрал стандартный режим таймера (секундомер).
     */
    void timerModeSelected();

    /**
     * @brief Пользователь выбрал режим Помодоро и задал настройки.
     * @param workMinutes Длительность рабочей сессии в минутах.
     * @param restMinutes Длительность сессии отдыха в минутах.
     */
    void pomodoroModeSelected(int workMinutes, int restMinutes);

};
