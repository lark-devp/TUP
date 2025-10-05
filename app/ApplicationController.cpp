#include "ApplicationController.h"
#include <QDebug>
#include <QVector>
#include <QDate>

ApplicationController::ApplicationController(std::unique_ptr<IUIFactory> factory,std::unique_ptr<IDatabaseService> dbService, QObject *parent)
    : QObject(parent)
    , m_factory(std::move(factory))
    , m_dbService(std::move(dbService))
{
}

void ApplicationController::start()
{
    // 1. Создаем окно авторизации через фабрику
    m_authorizationView = m_factory->createAuthorizationWindow();

    if (!m_authorizationView) {
        qCritical() << "Критическая ошибка: не удалось создать окно авторизации!";
        return;
    }

    // 2. Подписываемся на главный сигнал от окна авторизации
    connect(m_authorizationView.get(), &IAuthorizationView::loginRequested,
            this, &ApplicationController::onLoginRequested);

    // 3. Показываем окно авторизации
    m_authorizationView->showView();
}

/**
 * @brief Этот слот вызывается, когда пользователь нажимает "Войти".
 * Здесь происходит вся логика аутентификации.
 */
void ApplicationController::onLoginRequested(const QString& username, const QString& password)
{
    qDebug() << "Попытка входа через БД для пользователя:" << username;
    m_authorizationView->showLoading(true);

    // ----- ЗАМЕНЯЕМ СТАРУЮ ЛОГИКУ -----
    QVariantMap userData = m_dbService->authenticateUser(username, password);

    if (!userData.isEmpty()) {
        qDebug() << "Аутентификация в БД успешна!";
        m_currentUserId = userData["user_id"].toInt(); // Сохраняем ID пользователя

        // Получаем задачи для этого пользователя
        QVector<TaskDisplayData> tasks = m_dbService->getTasksForUser(m_currentUserId);

        // Переходим на главный экран и ПЕРЕДАЕМ ему полученные задачи
        m_authorizationView->hideView();
        m_authorizationView.reset();
        showMainWindow(tasks); // Вызываем метод с задачами
    } else {
        qDebug() << "Ошибка аутентификации в БД!";
        m_authorizationView->showLoading(false);
        m_authorizationView->showError("Неверное имя пользователя или пароль");
    }
}
/**
 * @brief Этот метод инкапсулирует всю логику создания и настройки главного окна.
 * Мы вынесли его из start(), чтобы можно было вызвать после успешного логина.
 */
void ApplicationController::showMainWindow(const QVector<TaskDisplayData>& tasks)
{
    // Этот код был раньше в методе start()
    m_taskSelectionView = m_factory->createTaskListWindow();
    if (!m_taskSelectionView) {
        qCritical() << "Критическая ошибка: не удалось создать главное окно!";
        return;
    }

    // Подключаем ВСЕ сигналы от главного окна, как и раньше
    connect(m_taskSelectionView.get(), &ITaskSelectionView::taskSelectedForTimer, this, &ApplicationController::onTaskSelectedForTimer);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::statisticsRequestedForTask, this, &ApplicationController::onStatisticsRequestedForTask);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::allTasksStatisticsRequested, this, &ApplicationController::onAllTasksStatisticsRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::synchronizationRequested, this, &ApplicationController::onSynchronizationRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::addTaskRequested, this, &ApplicationController::onAddTaskRequested);
    connect(m_authorizationView.get(), &IAuthorizationView::loginRequested,
            this, &ApplicationController::onLoginRequested);

    m_taskSelectionView->displayTasks(tasks);
    // Показываем главное окно
    m_taskSelectionView->showView();
}



// Этот слот вызовется, когда пользователь нажмет "Старт" в окне выбора задач
// Этот слот вызывается, когда пользователь нажимает "Старт" в окне выбора задач
void ApplicationController::onTaskSelectedForTimer(const QString& taskId)
{
    qDebug() << "Переход к таймеру для задачи:" << taskId;

    // 1. Сохраняем ID текущей задачи
    m_currentTimingTaskId = taskId.toInt();

    // 2. Скрываем окно выбора задач
    m_taskSelectionView->hideView();

    // 3. Создаем окно таймера
    m_timerView = m_factory->createTimerWindow();

    // 4. Настраиваем окно
    QString title = m_dbService->getTaskTitle(m_currentTimingTaskId);
    m_timerView->setTaskTitle(title.isEmpty() ? "Задача " + taskId : title);
    m_timerView->updateDisplayedTime("00:00:00"); // Начинаем с нуля

    // 5. Подключаем сигналы от окна таймера к нашим новым слотам
    connect(m_timerView.get(), &ITimerView::stopClicked, this, &ApplicationController::onTimerStop);
    connect(m_timerView.get(), &ITimerView::closeRequested, this, &ApplicationController::onTimerClosed);

    // 6. Показываем окно
    m_timerView->showView();

    // --- 7. ЗАПУСКАЕМ ЛОГИКУ ТАЙМЕРА ---
    m_elapsedSeconds = 0;
    m_sessionStartTime = QDateTime::currentDateTime();
    m_timer = std::make_unique<QTimer>(this);
    connect(m_timer.get(), &QTimer::timeout, this, &ApplicationController::onTimerTick);
    m_timer->start(1000); // Запускаем таймер с интервалом в 1 секунду
}

// Слот, вызываемый каждую секунду по сигналу от QTimer
void ApplicationController::onTimerTick()
{
    m_elapsedSeconds++;
    qint64 hours = m_elapsedSeconds / 3600;
    qint64 minutes = (m_elapsedSeconds % 3600) / 60;
    qint64 seconds = m_elapsedSeconds % 60;

    // Форматируем строку в виде HH:mm:ss
    QString timeString = QString("%1:%2:%3")
                             .arg(hours, 2, 10, QChar('0'))
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0'));

    if (m_timerView) {
        m_timerView->updateDisplayedTime(timeString);
    }
}

// Слот, вызываемый при нажатии кнопки "Стоп"
void ApplicationController::onTimerStop()
{
    qDebug() << "Таймер остановлен. Сохранение сессии...";

    // 1. Останавливаем таймер
    if (m_timer) {
        m_timer->stop();
    }

    // 2. Сохраняем запись в базу данных
    QDateTime endTime = QDateTime::currentDateTime();
    bool success = m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);

    if (success) {
        qDebug() << "Сессия успешно сохранена.";
    } else {
        qCritical() << "Не удалось сохранить сессию!";
        // Здесь можно показать пользователю сообщение об ошибке, если нужно
    }

    // 3. Закрываем окно таймера и возвращаемся к списку задач
    onTimerClosed();
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
    m_taskSelectionView->hideView();

    m_statisticsView = m_factory->createSingleTaskStatisticsWindow();

    m_currentStatisticsTaskId = taskId.toInt();

    m_statisticsView->setTaskTitle("Статистика по задаче " + taskId);

    connect(m_statisticsView.get(), &ISingleTaskStatisticsView::closeRequested,
            this, &ApplicationController::onStatisticsClosed);
    connect(m_statisticsView.get(), &ISingleTaskStatisticsView::weekChanged,
            this, &ApplicationController::onWeekChangeForStatisticsRequested);

    m_statisticsView->showView();

    // --- ИЗМЕНЕНИЕ: ЯВНЫЙ ВЫЗОВ ПЕРВОЙ ЗАГРУЗКИ ---
    // Устанавливаем начальную неделю (понедельник текущей недели) и загружаем данные
    QDate today = QDate::currentDate();
    onWeekChangeForStatisticsRequested(today.addDays(-(today.dayOfWeek() - 1)));
}


// Новый слот для обработки смены недели
void ApplicationController::onWeekChangeForStatisticsRequested(const QDate& weekStartDate)
{
    m_currentStatisticsWeekStart = weekStartDate;
    loadAndDisplayWeeklyStats();
}

// Новый вспомогательный метод, чтобы не дублировать код
void ApplicationController::loadAndDisplayWeeklyStats()
{
    if (!m_statisticsView || m_currentStatisticsTaskId <= 0) {
        return;
    }

    qDebug() << "Загрузка статистики для задачи" << m_currentStatisticsTaskId
             << "на неделю, начиная с" << m_currentStatisticsWeekStart.toString("yyyy-MM-dd");

    m_statisticsView->showLoading(true);

    // 1. Получаем данные из БД
    QVector<qint64> weeklyData = m_dbService->getWeeklyTaskStats(m_currentStatisticsTaskId, m_currentStatisticsWeekStart);

    // 2. Формируем красивую строку с диапазоном дат для заголовка
    QDate weekEndDate = m_currentStatisticsWeekStart.addDays(6);
    QString weekRangeLabel = QString("%1 - %2")
                                 .arg(m_currentStatisticsWeekStart.toString("dd MMM"))
                                 .arg(weekEndDate.toString("dd MMM yyyy"));

    // 3. Передаем данные в окно
    m_statisticsView->displayWeeklyChart(weeklyData, weekRangeLabel);

    m_statisticsView->showLoading(false);
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
// Этот слот вызовется, когда пользователь нажмет "Добавить"
void ApplicationController::onAddTaskRequested()
{
    qDebug() << "Переход к окну добавления задачи";

    // 1. Скрываем главное окно
    m_taskSelectionView->hideView();

    // 2. Создаем окно добавления задачи через фабрику
    m_addTaskView = m_factory->createAddTaskWindow();
    m_addTaskView->clearForm(); // Очищаем форму на случай, если она использовалась ранее

    // 3. Подключаем ОБА сигнала о завершении работы
    connect(m_addTaskView.get(), &IAddTaskView::saveTaskRequested, this, &ApplicationController::onAddTaskSaved);
    connect(m_addTaskView.get(), &IAddTaskView::cancelRequested, this, &ApplicationController::onAddTaskCancelled);

    // 4. Показываем новое окно
    m_addTaskView->showView();
}

// Слот для реакции на УСПЕШНОЕ добавление
void ApplicationController::onAddTaskSaved(const QString& title, const QString& description)
{
    qDebug() << "Попытка сохранения задачи: " << title;

    // 1. Простая валидация: проверяем, что заголовок не пустой
    if (title.trimmed().isEmpty()) {
        if (m_addTaskView) {
            m_addTaskView->showValidationError("Название задачи не может быть пустым.");
        }
        return; // Прерываем выполнение, не закрывая окно
    }

    // 2. Вызов сервиса базы данных для сохранения задачи
    bool success = m_dbService->addTask(title, description, m_currentUserId);

    // 3. Обработка результата
    if (success) {
        qDebug() << "Задача успешно сохранена в БД.";
        // Обновляем список задач в главном окне
        refreshTaskList();
        // Возвращаемся к главному окну
        returnToTaskSelection();
    } else {
        qCritical() << "Не удалось сохранить задачу в БД.";
        // Показываем ошибку в том же окне добавления задачи
        if (m_addTaskView) {
            m_addTaskView->showValidationError("Произошла ошибка при сохранении задачи. Попробуйте снова или проверьте логи.");
        }
    }
}


// Слот для реакции на ОТМЕНУ
void ApplicationController::onAddTaskCancelled()
{
    qDebug() << "Добавление задачи отменено";
    returnToTaskSelection();
}

// Вспомогательный метод, чтобы не дублировать код возврата
void ApplicationController::returnToTaskSelection()
{
    // 1. Скрываем и уничтожаем окно добавления
    if (m_addTaskView) {
        m_addTaskView->hideView();
        m_addTaskView.reset();
    }

    // 2. Снова показываем главное окно
    if (m_taskSelectionView) {
        m_taskSelectionView->showView();
    }
}
void ApplicationController::refreshTaskList()
{
    if (m_taskSelectionView) {
        qDebug() << "Обновление списка задач для пользователя" << m_currentUserId;
        // 1. Запрашиваем обновленный список задач из БД
        QVector<TaskDisplayData> tasks = m_dbService->getTasksForUser(m_currentUserId);
        // 2. Отображаем его в окне выбора задач
        m_taskSelectionView->displayTasks(tasks);
    }
}
