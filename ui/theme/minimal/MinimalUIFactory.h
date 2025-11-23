#pragma once

#include "ui/interfaces/IUIFactory.h"


class MinimalUIFactory : public IUIFactory
{
public:
    MinimalUIFactory()  = default;
    ~MinimalUIFactory() override = default;

    std::unique_ptr<ITaskSelectionView> createTaskListWindow() override;
    std::unique_ptr<ITimerView> createTimerWindow() override;
    std::unique_ptr<IAddTaskView> createAddTaskWindow() override;
    std::unique_ptr<ISingleTaskStatisticsView> createSingleTaskStatisticsWindow() override;
    std::unique_ptr<IAllTasksStatisticsView> createAllTasksStatisticsWindow() override;
    std::unique_ptr<ISynchronizationView> createSynchronizationWindow() override;
    std::unique_ptr<IEditTaskView> createEditTaskWindow() override;
};
