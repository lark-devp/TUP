#pragma once

#include "ui/interfaces/IUIFactory.h" // Подключаем абстрактный интерфейс фабрики

/**
 * @brief Конкретная реализация фабрики, создающая окна в минималистичном стиле.
 */
class MinimalUIFactory : public IUIFactory
{
public:
    MinimalUIFactory() = default;
    ~MinimalUIFactory() override = default;

    // Реализуем методы создания окон из интерфейса IUIFactory
    std::unique_ptr<IAuthorizationView> createAuthorizationWindow() override;
    std::unique_ptr<ITaskSelectionView> createTaskListWindow() override;
    std::unique_ptr<ITimerView> createTimerWindow() override;
    std::unique_ptr<IAddTaskView> createAddTaskWindow() override;
    std::unique_ptr<ISingleTaskStatisticsView> createSingleTaskStatisticsWindow() override;
    std::unique_ptr<IAllTasksStatisticsView> createAllTasksStatisticsWindow() override;
    std::unique_ptr<ISynchronizationView> createSynchronizationWindow() override;
};
