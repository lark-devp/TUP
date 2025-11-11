#pragma once

#include <memory>

#include "ITaskSelectionView.h"
#include "ITimerView.h"
#include "IAddTaskView.h"
#include "ISingleTaskStatisticsView.h"
#include "IAllTasksStatisticsView.h"
#include "ISynchronizationView.h"
#include "IAuthorizationView.h"
#include "IEditTaskView.h"

/**
 * @brief Интерфейс Абстрактной фабрики для создания UI-компонентов.
 * Конкретные реализации этой фабрики (MinimalistUIFactory, CyberpunkUIFactory)
 * будут создавать окна в своем уникальном стиле.
 */
class IUIFactory
{
public:
    virtual ~IUIFactory() = default;
    virtual std::unique_ptr<IAuthorizationView> createAuthorizationWindow() = 0;
    virtual std::unique_ptr<ITaskSelectionView> createTaskListWindow() = 0;
    virtual std::unique_ptr<ITimerView> createTimerWindow() = 0;
    virtual std::unique_ptr<IAddTaskView> createAddTaskWindow() = 0;
    virtual std::unique_ptr<ISingleTaskStatisticsView> createSingleTaskStatisticsWindow() = 0;
    virtual std::unique_ptr<IAllTasksStatisticsView> createAllTasksStatisticsWindow() = 0;
    virtual std::unique_ptr<ISynchronizationView> createSynchronizationWindow() = 0;
    virtual std::unique_ptr<IEditTaskView> createEditTaskWindow() = 0;
};
