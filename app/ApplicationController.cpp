#include "ApplicationController.h"
#include <QDebug>
#include <QVector>

ApplicationController::ApplicationController(std::unique_ptr<IUIFactory> factory, QObject *parent)
    : QObject(parent)
    , m_factory(std::move(factory)) // Забираем владение фабрикой
{
}

void ApplicationController::start()
{
    // 1. Используем фабрику для создания ПЕРВОГО окна
    m_taskSelectionView = m_factory->createTaskListWindow();

    if (!m_taskSelectionView) {
        qCritical() << "Не удалось создать главное окно!";
        return;
    }

    // 2. ПОДКЛЮЧАЕМ СИГНАЛЫ от этого окна к слотам Контроллера
    // Это САМЫЙ ВАЖНЫЙ момент. Контроллер подписывается на события.
    connect(m_taskSelectionView.get(), &ITaskSelectionView::taskSelectedForTimer,
            this, &ApplicationController::onTaskSelectedForTimer);

    connect(m_taskSelectionView.get(), &ITaskSelectionView::statisticsRequestedForTask,
            this, &ApplicationController::onStatisticsRequestedForTask);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::allTasksStatisticsRequested,
            this, &ApplicationController::onAllTasksStatisticsRequested);
     connect(m_taskSelectionView.get(), &ITaskSelectionView::synchronizationRequested,
            this, &ApplicationController::onSynchronizationRequested);
    // 3. Показываем окно
    m_taskSelectionView->showView();

    // Для теста можно загрузить данные
    QVector<TaskDisplayData> mockTasks;
    mockTasks.push_back({"id_1", "Задача 1"});
    mockTasks.push_back({"id_2", "Задача 2"});
    m_taskSelectionView->displayTasks(mockTasks);
}

// Этот слот вызовется, когда пользователь нажмет "Старт" в окне выбора задач
void ApplicationController::onTaskSelectedForTimer(const QString& taskId)
{
    qDebug() << "Переход к таймеру для задачи:" << taskId;

    // 1. Скрываем текущее окно
    m_taskSelectionView->hideView();

    // 2. Создаем НОВОЕ окно (окно таймера) через фабрику
    m_timerView = m_factory->createTimerWindow();

    // 3. Настраиваем новое окно
    // Здесь вам пригодится taskId, чтобы, например, получить название задачи из базы
    m_timerView->setTaskTitle("Название для задачи " + taskId);
    m_timerView->updateDisplayedTime("00:00:00");

    // 4. Подключаем сигналы от НОВОГО окна
    // Например, чтобы вернуться назад при закрытии
    connect(m_timerView.get(), &ITimerView::closeRequested,
            this, &ApplicationController::onTimerClosed);

    // 5. Показываем новое окно
    m_timerView->showView();
}

// Этот слот вызовется, когда пользователь закроет окно таймера
void ApplicationController::onTimerClosed()
{
    qDebug() << "Возврат к списку задач";
    // 1. Скрываем и уничтожаем окно таймера (оно нам пока больше не нужно)
    m_timerView->hideView();
    m_timerView.reset(); // Освобождаем память

    // 2. Снова показываем окно списка задач
    m_taskSelectionView->showView();
}

void ApplicationController::onStatisticsRequestedForTask(const QString& taskId)
{
    qDebug() << "Переход к статистике для задачи:" << taskId;

    // 1. Скрываем главное окно
    m_taskSelectionView->hideView();

    // 2. Создаем окно статистики через фабрику
    m_statisticsView = m_factory->createSingleTaskStatisticsWindow();

    // 3. Настраиваем новое окно (например, устанавливаем заголовок)
    m_statisticsView->setTaskTitle("Статистика по задаче " + taskId);
    // Здесь в будущем будет загрузка и отображение данных
    // m_statisticsView->displayStatistics(...);

    // 4. Подключаем сигнал о закрытии, чтобы вернуться назад
    connect(m_statisticsView.get(), &ISingleTaskStatisticsView::closeRequested,
            this, &ApplicationController::onStatisticsClosed);

    // 5. Показываем окно статистики
    m_statisticsView->showView();
}

// Этот слот вызовется, когда пользователь закроет окно статистики
void ApplicationController::onStatisticsClosed()
{
    qDebug() << "Возврат к списку задач из статистики";
    // 1. Скрываем и уничтожаем окно статистики
    if (m_statisticsView) {
        m_statisticsView->hideView();
        m_statisticsView.reset();
    }

    // 2. Снова показываем главное окно
    m_taskSelectionView->showView();
}

void ApplicationController::onAllTasksStatisticsRequested()
{
    qDebug() << "Переход к общей статистике по всем задачам";

    // 1. Скрываем главное окно
    m_taskSelectionView->hideView();

    // 2. Создаем окно общей статистики через фабрику
    m_allTasksStatisticsView = m_factory->createAllTasksStatisticsWindow();

    // 3. Настраиваем новое окно (если нужно)
    // В будущем здесь будет загрузка и отображение данных
    // m_allTasksStatisticsView->displayOverallStatistics(...);

    // 4. Подключаем сигнал о закрытии, чтобы вернуться назад
    connect(m_allTasksStatisticsView.get(), &IAllTasksStatisticsView::closeRequested,
            this, &ApplicationController::onAllTasksStatisticsClosed);

    // 5. Показываем новое окно
    m_allTasksStatisticsView->showView();
}

// Этот слот вызовется, когда пользователь закроет окно общей статистики
void ApplicationController::onAllTasksStatisticsClosed()
{
    qDebug() << "Возврат к списку задач из общей статистики";

    // 1. Скрываем и уничтожаем окно статистики
    if (m_allTasksStatisticsView) {
        m_allTasksStatisticsView->hideView();
        m_allTasksStatisticsView.reset();
    }

    // 2. Снова показываем главное окно
    m_taskSelectionView->showView();
}
// Этот слот вызовется, когда пользователь нажмет "Синхронизация"
void ApplicationController::onSynchronizationRequested()
{
    qDebug() << "Переход к окну синхронизации";

    // 1. Скрываем главное окно
    m_taskSelectionView->hideView();

    // 2. Создаем окно синхронизации через фабрику
    m_synchronizationView = m_factory->createSynchronizationWindow();

    // 3. Подключаем сигнал о закрытии, чтобы вернуться назад
    connect(m_synchronizationView.get(), &ISynchronizationView::closeRequested,
            this, &ApplicationController::onSynchronizationClosed);

    // 4. Показываем новое окно
    m_synchronizationView->showView();

    // 5. ЗАПУСКАЕМ ПРОЦЕСС СИНХРОНИЗАЦИИ
    // Это ключевой момент. Контроллер управляет процессом
    // и передает обновления в "глупое" окно.
    // В будущем здесь будет вызов ICalendarService.
    // А пока давайте сымитируем процесс:
    m_synchronizationView->logMessage("Начинаем синхронизацию...");
    m_synchronizationView->setProgress(10);
    // ... здесь будет реальная работа ...
    m_synchronizationView->logMessage("Синхронизация успешно завершена.");
    m_synchronizationView->setProgress(100);
    m_synchronizationView->setCloseButtonEnabled(true); // Разрешаем закрыть окно
}

// Этот слот вызовется, когда пользователь закроет окно синхронизации
void ApplicationController::onSynchronizationClosed()
{
    qDebug() << "Возврат к списку задач из окна синхронизации";

    // 1. Скрываем и уничтожаем окно
    if (m_synchronizationView) {
        m_synchronizationView->hideView();
        m_synchronizationView.reset();
    }

    // 2. Снова показываем главное окно
    m_taskSelectionView->showView();
}
