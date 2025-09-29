#include "MinimalUIFactory.h"

// Подключаем заголовочные файлы конкретных реализаций окон
#include "ui/theme/minimal/MinimalTaskSelectionView.h"
#include "ui/theme/minimal/MinimalTimerView.h"
#include "ui/theme/minimal/MinimalSingleTaskStatisticsView.h"
// #include "MinimalistTimerView.h" // Подключите, когда создадите
// ... и так далее

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
    return nullptr;
}

std::unique_ptr<ISingleTaskStatisticsView> MinimalUIFactory::createSingleTaskStatisticsWindow()
{
    return std::make_unique<MinimalSingleTaskStatisticsView>();
}

std::unique_ptr<IAllTasksStatisticsView> MinimalUIFactory::createAllTasksStatisticsWindow()
{
    return nullptr;
}

std::unique_ptr<ISynchronizationView> MinimalUIFactory::createSynchronizationWindow()
{
    return nullptr;
}

