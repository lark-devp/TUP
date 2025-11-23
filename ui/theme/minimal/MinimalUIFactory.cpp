#include "MinimalUIFactory.h"

#include "ui/theme/minimal/MinimalTaskSelectionView.h"
#include "ui/theme/minimal/MinimalTimerView.h"
#include "ui/theme/minimal/MinimalSingleTaskStatisticsView.h"
#include "ui/theme/minimal/MinimalAllTasksStatisticsView.h"
#include "ui/theme/minimal/MinimalSynchronizationView.h"
#include "ui/theme/minimal/MinimalAddTaskView.h"
#include "ui/theme/minimal/MinimalEditTaskView.h"

std::unique_ptr<ITaskSelectionView> MinimalUIFactory::createTaskListWindow()
{
    return std::make_unique<MinimalTaskSelectionView>();
}



std::unique_ptr<ITimerView> MinimalUIFactory::createTimerWindow()
{

    return std::make_unique<MinimalTimerView>();
}

std::unique_ptr<IAddTaskView> MinimalUIFactory::createAddTaskWindow()
{
    return std::make_unique<MinimalAddTaskView>();
}

std::unique_ptr<IEditTaskView> MinimalUIFactory::createEditTaskWindow()
{
    return std::make_unique<MinimalEditTaskView>();
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
