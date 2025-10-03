#pragma once

#include <QObject>
#include <memory>
#include "ui/interfaces/IUIFactory.h"
#include "ui/interfaces/ITaskSelectionView.h"
#include "ui/interfaces/ITimerView.h"
#include "ui/interfaces/ISingleTaskStatisticsView.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    // Контроллер принимает во владение Фабрику
    explicit ApplicationController(std::unique_ptr<IUIFactory> factory, QObject *parent = nullptr);

    // Метод для запуска приложения (показа первого окна)
    void start();

private slots:

    void onTaskSelectedForTimer(const QString& taskId);
    void onStatisticsRequestedForTask(const QString& taskId);
    void onAllTasksStatisticsRequested();
    void onSynchronizationRequested();

    //слоты при закрытии окон
    void onTimerClosed();
    void onStatisticsClosed();
    void onAllTasksStatisticsClosed();
    void onSynchronizationClosed();

private:
    // Контроллер владеет фабрикой
    std::unique_ptr<IUIFactory> m_factory;

    // Контроллер хранит указатели на текущие активные окна
    std::unique_ptr<ITaskSelectionView> m_taskSelectionView;
    std::unique_ptr<ITimerView> m_timerView;
    std::unique_ptr<ISingleTaskStatisticsView> m_statisticsView;
    std::unique_ptr<IAllTasksStatisticsView> m_allTasksStatisticsView;
    std::unique_ptr<ISynchronizationView> m_synchronizationView;
};
