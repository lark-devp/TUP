#pragma once

#include "IView.h" // Ваш базовый интерфейс IView
#include <QWidget>
#include <QString>

/**
 * @brief Интерфейс для окна с таймером.
 * @note Наследуется от QWidget, чтобы реализация могла быть виджетом,
 * как в примере MinimalTaskSelectionView.
 */
class ITimerView : public QWidget, public IView
{
    Q_OBJECT

public:
    // Используем конструктор QWidget
    explicit ITimerView(QWidget* parent = nullptr) : QWidget(parent) {}
    ~ITimerView() override = default;

    // Методы для управления видом
    virtual void setTaskTitle(const QString& title) = 0;
    virtual void updateDisplayedTime(const QString& timeString) = 0;
    virtual void setTimerControlsEnabled(bool canStart, bool canPause, bool canStop) = 0;

signals:
    // Сигналы о действиях пользователя
    void startClicked();
    void pauseClicked();
    void stopClicked();
    void closeRequested();
};
