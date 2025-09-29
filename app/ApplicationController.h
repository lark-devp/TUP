#pragma once

#include <QObject>
#include <memory>
#include "ui/interfaces/IUIFactory.h"
#include "ui/interfaces/ITaskSelectionView.h"
#include "ui/interfaces/ITimerView.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    // Контроллер принимает во владение Фабрику
    explicit ApplicationController(std::unique_ptr<IUIFactory> factory, QObject *parent = nullptr);

    // Метод для запуска приложения (показа первого окна)
    void start();

private slots:
    // Сюда мы будем подключать сигнал taskSelectedForTimer из окна выбора задач
    void onTaskSelectedForTimer(const QString& taskId);

    // Сюда мы будем подключать сигнал closeRequested из окна таймера
    void onTimerClosed();

private:
    // Контроллер владеет фабрикой
    std::unique_ptr<IUIFactory> m_factory;

    // Контроллер хранит указатели на текущие активные окна
    std::unique_ptr<ITaskSelectionView> m_taskSelectionView;
    std::unique_ptr<ITimerView> m_timerView;
};
