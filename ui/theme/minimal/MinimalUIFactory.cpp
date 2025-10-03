#include "MinimalUIFactory.h"

// Подключаем заголовочные файлы конкретных реализаций окон
#include "ui/theme/minimal/MinimalTaskSelectionView.h"
#include "ui/theme/minimal/MinimalTimerView.h"
#include "ui/theme/minimal/MinimalSingleTaskStatisticsView.h"
#include "ui/theme/minimal/MinimalAllTasksStatisticsView.h"
#include "ui/theme/minimal/MinimalSynchronizationView.h"
#include "ui/theme/minimal/MinimalAddTaskView.h"

std::unique_ptr<ITaskSelectionView> MinimalUIFactory::createTaskListWindow()
{
    // Фабрика создает конкретный объект и возвращает указатель на его интерфейс
    return std::make_unique<MinimalTaskSelectionView>();
}

// Даже если у вас еще нет этих окон, вы ОБЯЗАНЫ предоставить
// реализацию-заглушку для каждого метода, требуемого интерфейсом.

std::unique_ptr<ITimerView> MinimalUIFactory::createTimerWindow()
{
    // Пока возвращаем nullptr, т.к. класс MinimalistTimerView еще не создан
    return std::make_unique<MinimalTimerView>();
}

std::unique_ptr<IAddTaskView> MinimalUIFactory::createAddTaskWindow()
{
    return std::make_unique<MinimalAddTaskView>();
}

std::unique_ptr<ISingleTaskStatisticsView> MinimalUIFactory::createSingleTaskStatisticsWindow()
{
    return std::make_unique<MinimalSingleTaskStatisticsView>();
}

std::unique_ptr<IAllTasksStatisticsView> MinimalUIFactory::createAllTasksStatisticsWindow()
{
    return std::make_unique<MinimalAllTasksStatisticsView>();
}

std::unique_ptr<ISynchronizationView> MinimalUIFactory::createSynchronizationWindow()
{
    return std::make_unique<MinimalSynchronizationView>();
}

