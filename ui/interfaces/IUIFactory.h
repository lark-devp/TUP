#pragma once

#include <memory>

#include "ITaskSelectionView.h"
#include "ITimerView.h"
#include "IAddTaskView.h"
#include "ISingleTaskStatisticsView.h"
#include "IAllTasksStatisticsView.h"
#include "ISynchronizationView.h"
#include "IEditTaskView.h"

class IUIFactory
{
public:
    virtual ~IUIFactory() = default;
    virtual std::unique_ptr<ITaskSelectionView> createTaskListWindow() = 0;
    virtual std::unique_ptr<ITimerView> createTimerWindow() = 0;
    virtual std::unique_ptr<IAddTaskView> createAddTaskWindow() = 0;
    virtual std::unique_ptr<ISingleTaskStatisticsView> createSingleTaskStatisticsWindow() = 0;
    virtual std::unique_ptr<IAllTasksStatisticsView> createAllTasksStatisticsWindow() = 0;
    virtual std::unique_ptr<ISynchronizationView> createSynchronizationWindow() = 0;
    virtual std::unique_ptr<IEditTaskView> createEditTaskWindow() = 0;
};
