#include "ApplicationController.h"
#include <QDebug>
#include <QVector>
#include <QDate>
#include <QMessageBox>

ApplicationController::ApplicationController(std::unique_ptr<IUIFactory> factory,std::unique_ptr<IDatabaseService> dbService,
                                             std::unique_ptr<ITweekApiService> calendar, QObject *parent)
    : QObject(parent)
    , m_factory(std::move(factory))
    , m_dbService(std::move(dbService)), m_tweekApiService(std::move(calendar))
{
    m_currentUserId = 1;
}

void ApplicationController::start()
{
    qDebug() << "Запуск приложения для пользователя по умолчанию ID:" << m_currentUserId;
    QVector<TaskDisplayData> tasks = m_dbService->getTasksForUser(m_currentUserId);
    showMainWindow(tasks);
}

void ApplicationController::showMainWindow(const QVector<TaskDisplayData>& tasks)
{

    m_taskSelectionView = m_factory->createTaskListWindow();
    if (!m_taskSelectionView) {
        qCritical() << "Критическая ошибка: не удалось создать главное окно!";
        return;
    }


    connect(m_taskSelectionView.get(), &ITaskSelectionView::taskSelectedForTimer, this, &ApplicationController::onTaskSelectedForTimer);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::statisticsRequestedForTask, this, &ApplicationController::onStatisticsRequestedForTask);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::allTasksStatisticsRequested, this, &ApplicationController::onAllTasksStatisticsRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::synchronizationRequested, this, &ApplicationController::onSynchronizationRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::addTaskRequested, this, &ApplicationController::onAddTaskRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::editTaskRequested, this, &ApplicationController::onEditTaskRequested);
    connect(m_taskSelectionView.get(), &ITaskSelectionView::syncSingleTaskRequested, this, &ApplicationController::onSyncSingleTaskToTweek);
    m_taskSelectionView->displayTasks(tasks);

    m_taskSelectionView->showView();
}




void ApplicationController::onTaskSelectedForTimer(const QString& taskId)
{
    qDebug() << "Переход к выбору режима таймера для задачи:" << taskId;

    m_currentTimingTaskId = taskId.toInt();
    m_taskSelectionView->hideView();

    m_timerView = m_factory->createTimerWindow();


    QString title = m_dbService->getTaskTitle(m_currentTimingTaskId);
    m_timerView->setTaskTitle(title.isEmpty() ? "Задача " + taskId : title);

    connect(m_timerView.get(), &ITimerView::stopClicked, this, &ApplicationController::onTimerStop);
    connect(m_timerView.get(), &ITimerView::closeRequested, this, &ApplicationController::onTimerClosed);
    connect(m_timerView.get(), &ITimerView::timerModeSelected, this, &ApplicationController::onTimerModeSelected);
    connect(m_timerView.get(), &ITimerView::pomodoroModeSelected, this, &ApplicationController::onPomodoroModeSelected);
    connect(m_timerView.get(), &ITimerView::skipRestRequested, this, &ApplicationController::onSkipRestRequested);


    m_timerView->showModeSelection();
    m_timerView->showView();
}
void ApplicationController::onTimerModeSelected()
{
    qDebug() << "Выбран режим обычного таймера";
    m_currentTimerMode = TimerMode::Stopwatch;
    if (m_timerView) {
        m_timerView->showStopwatchMode();
    }


    m_elapsedSeconds = 0;
    m_sessionStartTime = QDateTime::currentDateTime();

    if (!m_timer) {
        m_timer = std::make_unique<QTimer>(this);
        connect(m_timer.get(), &QTimer::timeout, this, &ApplicationController::onTimerTick);
    }
    m_timer->start(1000);


    m_timerView->updateDisplayedTime("00:00:00");
}

void ApplicationController::onPomodoroModeSelected(int workMinutes, int restMinutes, int sessionCount)
{
    qDebug() << "Выбран режим Помодоро: " << workMinutes << "мин работа," << restMinutes << "мин отдых, циклов:" << sessionCount;
    m_currentTimerMode = TimerMode::Pomodoro;
    m_pomodoroWorkDurationSecs = workMinutes * 60;
    m_pomodoroRestDurationSecs = restMinutes * 60;
    m_pomodoroTotalSessions = sessionCount;
    m_pomodoroSessionsCompleted = 0;
    m_currentPomodoroState = PomodoroState::Rest;

    if (!m_timer) {
        m_timer = std::make_unique<QTimer>(this);
        connect(m_timer.get(), &QTimer::timeout, this, &ApplicationController::onTimerTick);
    }

    startNextPomodoroSession();
}

void ApplicationController::onSkipRestRequested()
{
    if (m_currentTimerMode == TimerMode::Pomodoro && m_currentPomodoroState == PomodoroState::Rest) {
        qDebug() << "Отдых пропущен, запуск следующей сессии работы.";
        handlePomodoroSessionFinish();
    }
}

void ApplicationController::onTimerTick()
{
    if (m_currentTimerMode == TimerMode::Stopwatch) {
        m_elapsedSeconds++;
        qint64 hours = m_elapsedSeconds / 3600;
        qint64 minutes = (m_elapsedSeconds % 3600) / 60;
        qint64 seconds = m_elapsedSeconds % 60;
        QString timeString = QString("%1:%2:%3").arg(hours, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        if (m_timerView) m_timerView->updateDisplayedTime(timeString);

    } else if (m_currentTimerMode == TimerMode::Pomodoro) {
        m_secondsRemainingInSession--;

        qint64 minutes = m_secondsRemainingInSession / 60;
        qint64 seconds = m_secondsRemainingInSession % 60;
        QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        if (m_timerView) m_timerView->updateDisplayedTime(timeString);

        if (m_secondsRemainingInSession <= 0) {
            handlePomodoroSessionFinish();
        }
    }
}

void ApplicationController::handlePomodoroSessionFinish()
{
    if (m_timer) m_timer->stop();

    if (m_currentPomodoroState == PomodoroState::Work) {
        QDateTime endTime = m_sessionStartTime.addSecs(m_pomodoroWorkDurationSecs);
        m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
        qDebug() << "Рабочая сессия Помодоро сохранена.";
        m_pomodoroSessionsCompleted++;
    }

    if (m_pomodoroSessionsCompleted >= m_pomodoroTotalSessions) {
        qDebug() << "Все сессии Помодоро завершены.";
        onTimerStop();
        return;
    }

    startNextPomodoroSession();
}


void ApplicationController::startNextPomodoroSession()
{
    QString taskTitle = m_dbService->getTaskTitle(m_currentTimingTaskId);
    if (taskTitle.isEmpty()) {
        taskTitle = "текущей задачей";
    }

    if (m_currentPomodoroState == PomodoroState::Rest) {
        m_currentPomodoroState = PomodoroState::Work;
        m_secondsRemainingInSession = m_pomodoroWorkDurationSecs;

        QMessageBox workNotification(m_timerView ? m_timerView->getWidget() : nullptr);
        workNotification.setWindowTitle("Время работать!");
        workNotification.setText(QString("Начинается сессия работы над задачей:\n'%1'").arg(taskTitle));
        workNotification.setIcon(QMessageBox::Information);
        workNotification.setStandardButtons(QMessageBox::Ok);

        workNotification.setWindowFlags(workNotification.windowFlags() | Qt::WindowStaysOnTopHint);

        workNotification.exec();

    } else {
        m_currentPomodoroState = PomodoroState::Rest;
        m_secondsRemainingInSession = m_pomodoroRestDurationSecs;

        QMessageBox restNotification(m_timerView ? m_timerView->getWidget() : nullptr);
        int restMinutes = m_pomodoroRestDurationSecs / 60;
        restNotification.setWindowTitle("Время отдохнуть!");
        restNotification.setText(QString("Сделайте перерыв на %1 минут.").arg(restMinutes));
        restNotification.setIcon(QMessageBox::Information);
        restNotification.setStandardButtons(QMessageBox::Ok);

        restNotification.setWindowFlags(restNotification.windowFlags() | Qt::WindowStaysOnTopHint);

        restNotification.exec();
    }

    m_sessionStartTime = QDateTime::currentDateTime();

    if (m_timerView) {
        bool isWork = (m_currentPomodoroState == PomodoroState::Work);
        m_timerView->displayPomodoroState(m_pomodoroTotalSessions, m_pomodoroSessionsCompleted, isWork);
    }

    if (m_timer) m_timer->start(1000);
}




void ApplicationController::onTimerStop()
{
    qDebug() << "Таймер остановлен. Сохранение сессии...";
    if (m_timer) {
        m_timer->stop();
    }
        saveCurrentSession();

    m_currentTimerMode = TimerMode::None;
    onTimerClosed();
}
void ApplicationController::onTimerClosed()
{
    qDebug() << "Возврат к списку задач";

    if (m_timer) {
        m_timer->stop();
    }
    m_currentTimerMode = TimerMode::None;

    if (m_timerView) {
        m_timerView->hideView();
        m_timerView.reset();
    }

    m_taskSelectionView->showView();
}

void ApplicationController::onStatisticsRequestedForTask(const QString& taskId)
{
    qDebug() << "Переход к статистике для задачи:" << taskId ;
    m_taskSelectionView->hideView();

    m_statisticsView = m_factory->createSingleTaskStatisticsWindow();

    m_currentStatisticsTaskId = taskId.toInt();


    QString title = m_dbService->getTaskTitle(m_currentStatisticsTaskId);

    m_statisticsView->setTaskTitle("Статистика по задаче «" + (title.isEmpty() ? taskId : title) + "»");

    connect(m_statisticsView.get(), &ISingleTaskStatisticsView::closeRequested,
            this, &ApplicationController::onStatisticsClosed);
    connect(m_statisticsView.get(), &ISingleTaskStatisticsView::weekChanged,
            this, &ApplicationController::onWeekChangeForStatisticsRequested);

    m_statisticsView->showView();

    QDate today = QDate::currentDate();
    onWeekChangeForStatisticsRequested(today.addDays(-(today.dayOfWeek() - 1)));
}



void ApplicationController::onWeekChangeForStatisticsRequested(const QDate& weekStartDate)
{
    m_currentStatisticsWeekStart = weekStartDate;
    loadAndDisplayWeeklyStats();
}


void ApplicationController::loadAndDisplayWeeklyStats()
{
    if (!m_statisticsView || m_currentStatisticsTaskId <= 0) {
        return;
    }

    qDebug() << "Загрузка статистики для задачи" << m_currentStatisticsTaskId
             << "на неделю, начиная с" << m_currentStatisticsWeekStart.toString("yyyy-MM-dd");

    m_statisticsView->showLoading(true);


    QVector<qint64> weeklyData = m_dbService->getWeeklyTaskStats(m_currentStatisticsTaskId, m_currentStatisticsWeekStart);

    QLocale russianLocale(QLocale::Russian, QLocale::Russia);
    QDate weekEndDate = m_currentStatisticsWeekStart.addDays(6);


    QString startStr = russianLocale.toString(m_currentStatisticsWeekStart, "dd MMM");
    QString endStr = russianLocale.toString(weekEndDate, "dd MMM yyyy");

    QString weekRangeLabel = QString("%1 - %2").arg(startStr).arg(endStr);

    m_statisticsView->displayWeeklyChart(weeklyData, weekRangeLabel);

    m_statisticsView->showLoading(false);
}



void ApplicationController::onStatisticsClosed()
{
    qDebug() << "Возврат к списку задач из статистики";

    if (m_statisticsView) {
        m_statisticsView->hideView();
        m_statisticsView.reset();
    }


    m_taskSelectionView->showView();
}

void ApplicationController::onAllTasksStatisticsRequested()
{
    qDebug() << "Переход к общей статистике по всем задачам";
    m_taskSelectionView->hideView();

    m_allTasksStatisticsView = m_factory->createAllTasksStatisticsWindow();

    connect(m_allTasksStatisticsView.get(), &IAllTasksStatisticsView::closeRequested,
            this, &ApplicationController::onAllTasksStatisticsClosed);

    m_allTasksStatisticsView->showView();


    m_allTasksStatisticsView->showLoading(true);


    QVector<TaskTimeSummary> summaries = m_dbService->getTaskTimeSummaries(m_currentUserId);


    m_allTasksStatisticsView->displayTaskSummaries(summaries);

    m_allTasksStatisticsView->showLoading(false);
}



void ApplicationController::onAllTasksStatisticsClosed()
{
    qDebug() << "Возврат к списку задач из общей статистики";


    if (m_allTasksStatisticsView) {
        m_allTasksStatisticsView->hideView();
        m_allTasksStatisticsView.reset();
    }


    m_taskSelectionView->showView();
}
void ApplicationController::onSynchronizationRequested()
{
    qDebug() << "Переход к окну синхронизации";
    m_taskSelectionView->hideView();
    m_synchronizationView = m_factory->createSynchronizationWindow();


    connect(m_synchronizationView.get(), &ISynchronizationView::closeRequested,
            this, &ApplicationController::onSynchronizationClosed);
    connect(m_synchronizationView.get(), &ISynchronizationView::connectRequested,
            this, &ApplicationController::onTweekConnectRequested);


    connect(m_synchronizationView.get(), &ISynchronizationView::tasksRequested,
            [this](const QString& calendarId){
                m_dbService->saveTweekDefaultCalendar(m_currentUserId, calendarId);
                if (m_currentTweekTokens) {
                    m_synchronizationView->updateStatus("Загрузка задач...");
                    m_synchronizationView->setProgress(75);
                    m_tweekApiService->fetchTodayTasks(m_currentTweekTokens->idToken, calendarId);
                }
            });
    connect(m_synchronizationView.get(), &ISynchronizationView::tasksSelected,
            this, &ApplicationController::onSyncTasksSelected);


    connect(m_tweekApiService.get(), &ITweekApiService::authenticationSuccess, this, &ApplicationController::onTweekAuthSuccess, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::authenticationFailed, this, &ApplicationController::onTweekAuthFailed, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::calendarsFetchSuccess, this, &ApplicationController::onCalendarsFetchSuccess, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::calendarsFetchFailed, this, &ApplicationController::onCalendarsFetchFailed, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::tasksFetchSuccess, this, &ApplicationController::onTasksFetchSuccess, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::tasksFetchFailed, this, &ApplicationController::onTasksFetchFailed, Qt::UniqueConnection);
    connect(m_synchronizationView.get(), &ISynchronizationView::disconnectRequested,
            this, &ApplicationController::onTweekDisconnectRequested);

    auto savedTokens = m_dbService->getTweekTokens(m_currentUserId);
    if (savedTokens && !savedTokens->refreshToken.isEmpty()) {
        qDebug() << "Найдены сохраненные токены Tweek. Обновление...";
        m_synchronizationView->showView();
        m_synchronizationView->showState(ISynchronizationView::ViewState::Sync);
        m_synchronizationView->updateStatus("Обновление сессии...");
        m_synchronizationView->setProgress(25);
        m_synchronizationView->setControlsEnabled(false);
        m_tweekApiService->refreshToken(savedTokens->refreshToken);
    } else {
        qDebug() << "Токены Tweek не найдены, требуется вход.";
        m_synchronizationView->showView();
        m_synchronizationView->showState(ISynchronizationView::ViewState::Login);
    }
}
void ApplicationController::onTweekConnectRequested(const QString& email, const QString& password)
{
    if (!m_synchronizationView) return;


    m_synchronizationView->updateStatus("Аутентификация...");
    m_synchronizationView->logMessage("Отправка учетных данных...");
    m_synchronizationView->setProgress(25);


    connect(m_tweekApiService.get(), &ITweekApiService::authenticationSuccess,
            this, &ApplicationController::onTweekAuthSuccess, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::authenticationFailed,
            this, &ApplicationController::onTweekAuthFailed, Qt::UniqueConnection);

    m_tweekApiService->authenticate(email, password);
}





void ApplicationController::onSynchronizationClosed()
{
    qDebug() << "Возврат к списку задач из окна синхронизации";


    if (m_synchronizationView) {
        m_synchronizationView->hideView();
        m_synchronizationView.reset();
    }


    m_taskSelectionView->showView();
}

void ApplicationController::onAddTaskRequested()
{
    qDebug() << "Переход к окну добавления задачи";


    m_taskSelectionView->hideView();


    m_addTaskView = m_factory->createAddTaskWindow();
    m_addTaskView->clearForm();

    connect(m_addTaskView.get(), &IAddTaskView::saveTaskRequested, this, &ApplicationController::onAddTaskSaved);
    connect(m_addTaskView.get(), &IAddTaskView::cancelRequested, this, &ApplicationController::onAddTaskCancelled);


    m_addTaskView->showView();
}


void ApplicationController::onAddTaskSaved(const QString& title, const QString& description)
{
    qDebug() << "Попытка сохранения задачи: " << title;


    if (title.trimmed().isEmpty()) {
        if (m_addTaskView) {
            m_addTaskView->showValidationError("Название задачи не может быть пустым.");
        }
        return;
    }


    bool success = m_dbService->addTask(title, description, m_currentUserId);


    if (success) {
        qDebug() << "Задача успешно сохранена в БД.";

        refreshTaskList();

        returnToTaskSelection();
    } else {
        qCritical() << "Не удалось сохранить задачу в БД.";

        if (m_addTaskView) {
            m_addTaskView->showValidationError("Произошла ошибка при сохранении задачи. Попробуйте снова или проверьте логи.");
        }
    }
}



void ApplicationController::onAddTaskCancelled()
{
    qDebug() << "Добавление задачи отменено";
    returnToTaskSelection();
}

void ApplicationController::onEditTaskRequested(const QString& taskId)
{
    qDebug() << "Запрос на редактирование задачи:" << taskId;
    m_currentEditingTaskId = taskId.toInt();

    QVariantMap taskData = m_dbService->getTaskDetails(m_currentEditingTaskId);
    if (taskData.isEmpty()) {
        qWarning() << "Не удалось получить данные для задачи" << taskId;
        return;
    }

    m_taskSelectionView->hideView();
    m_editTaskView = m_factory->createEditTaskWindow();

    m_editTaskView->setTaskData(taskData["title"].toString(), taskData["description"].toString());

    connect(m_editTaskView.get(), &IEditTaskView::saveTaskRequested, this, &ApplicationController::onEditTaskSaved);
    connect(m_editTaskView.get(), &IEditTaskView::deleteTaskRequested, this, &ApplicationController::onEditTaskDeleted);
    connect(m_editTaskView.get(), &IEditTaskView::cancelRequested, this, &ApplicationController::onEditTaskCancelled);

    m_editTaskView->showView();
}

void ApplicationController::onEditTaskSaved(const QString& title, const QString& description)
{
    qDebug() << "Сохранение изменений для задачи:" << m_currentEditingTaskId;

    if (title.trimmed().isEmpty()) {
        if (m_editTaskView) {
            m_editTaskView->showValidationError("Название задачи не может быть пустым.");
        }
        return;
    }

    bool success = m_dbService->updateTask(m_currentEditingTaskId, title, description);

    if (success) {
        refreshTaskList();
        returnToTaskSelection();
    } else {
        if (m_editTaskView) {
            m_editTaskView->showValidationError("Не удалось сохранить изменения.");
        }
    }
}

void ApplicationController::onEditTaskDeleted()
{
    qDebug() << "Удаление (деактивация) задачи:" << m_currentEditingTaskId;

    m_dbService->deactivateTask(m_currentEditingTaskId);

    refreshTaskList();
    returnToTaskSelection();
}

void ApplicationController::onEditTaskCancelled()
{
    qDebug() << "Редактирование задачи отменено.";
    returnToTaskSelection();
}
void ApplicationController::returnToTaskSelection()
{

    if (m_addTaskView) {
        m_addTaskView->hideView();
        m_addTaskView.reset();
    }
    if (m_editTaskView) {
        m_editTaskView->hideView();
        m_editTaskView.reset();
    }

    if (m_taskSelectionView) {
        m_taskSelectionView->showView();
    }
}
void ApplicationController::refreshTaskList()
{
    if (m_taskSelectionView) {
        qDebug() << "Обновление списка задач для пользователя" << m_currentUserId;

        QVector<TaskDisplayData> tasks = m_dbService->getTasksForUser(m_currentUserId);

        m_taskSelectionView->displayTasks(tasks);
    }
}

void ApplicationController::onTweekAuthSuccess(const QString& idToken, const QString& refreshToken)
{
    qDebug() << "Аутентификация/обновление токена Tweek успешно.";

    m_dbService->saveTweekTokens(m_currentUserId, idToken, refreshToken);
    m_currentTweekTokens = TweekTokens{idToken, refreshToken};

    if (!m_synchronizationView) return;

    m_synchronizationView->showState(ISynchronizationView::ViewState::Sync);
    m_synchronizationView->logMessage("Аутентификация успешна. Загрузка календарей...");
    m_synchronizationView->updateStatus("Загрузка календарей...");
    m_synchronizationView->setProgress(50);
    m_synchronizationView->setControlsEnabled(false);

    m_tweekApiService->fetchCalendars(m_currentTweekTokens->idToken);
}

void ApplicationController::onTweekAuthFailed()
{
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка: неверный логин или пароль.");
    m_synchronizationView->updateStatus("Не удалось подключиться.");
    m_synchronizationView->setProgress(0);
    m_synchronizationView->setControlsEnabled(true);
}


void ApplicationController::onCalendarsFetchSuccess(const QVector<TweekCalendar>& calendars) {
    if (!m_synchronizationView) return;

    m_synchronizationView->displayCalendars(calendars);
    m_synchronizationView->setControlsEnabled(true);

    QString defaultCalendarId = m_dbService->getTweekDefaultCalendar(m_currentUserId);
    if (!defaultCalendarId.isEmpty()) {
        m_synchronizationView->selectCalendar(defaultCalendarId);
        m_synchronizationView->updateStatus("Календарь по умолчанию выбран. Нажмите 'Получить задачи'.");
    } else {
        m_synchronizationView->updateStatus("Календари загружены. Выберите календарь и получите задачи.");
    }
}

void ApplicationController::onCalendarsFetchFailed() {
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка: Tweek API не активирован (список календарей пуст).");
    m_synchronizationView->updateStatus("Не найдено ни одного календаря.");
    m_synchronizationView->setControlsEnabled(true);
}

void ApplicationController::onTasksFetchSuccess(const QVector<TweekTask>& allTasks) {
    if (!m_synchronizationView) return;

    QVector<TweekTask> uncompletedTasks;

    for (const auto& task : allTasks) {
        if (!task.done) {
            uncompletedTasks.append(task);
        }
    }

    m_synchronizationView->displayTasks(uncompletedTasks);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->setProgress(90);

    if (uncompletedTasks.isEmpty()) {
        if (allTasks.isEmpty()) {
            m_synchronizationView->updateStatus("На сегодня нет запланированных задач.");
            m_synchronizationView->logMessage("Нет невыполненных задач на сегодня (список пуст).");
        } else {
            m_synchronizationView->updateStatus("Все задачи на сегодня уже выполнены!");
            m_synchronizationView->logMessage("Нет невыполненных задач на сегодня (все выполнены).");
        }
    } else {
        m_synchronizationView->updateStatus("Задачи загружены. Выберите нужные и подтвердите.");
        m_synchronizationView->logMessage(QString("Найдено %1 невыполненных задач для импорта.").arg(uncompletedTasks.size()));
    }
}

void ApplicationController::onTasksFetchFailed(const QString& error) {
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка загрузки задач: " + error);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->updateStatus("Ошибка загрузки задач.");
}

void ApplicationController::onSyncTasksSelected(const QVector<TweekTask>& selectedTasks) {
    if (!m_synchronizationView) return;

    m_synchronizationView->updateStatus("Сохранение задач...");
    m_synchronizationView->setProgress(95);

    int successCount = 0;
    for (const auto& task : selectedTasks) {
        qDebug() << "[DEBUG 2: CONTROLLER]"
                 << "ID:" << task.id
                 << "Title:" << task.title
                 << "Description:" << task.description;
        if (m_dbService->addTask(task.title, task.description, m_currentUserId, task.id)) {
            successCount++;
        }
    }

    m_synchronizationView->logMessage(QString("Успешно добавлено %1 из %2 задач.").arg(successCount).arg(selectedTasks.size()));
    m_synchronizationView->updateStatus("Импорт завершен.");
    m_synchronizationView->setProgress(100);
    m_synchronizationView->setControlsEnabled(true);


    refreshTaskList();
}
void ApplicationController::onSyncSingleTaskToTweek(const QString& taskId)
{
    qDebug() << "Запрос на синхронизацию задачи" << taskId << "с Tweek.";

    if (!m_currentTweekTokens || m_currentTweekTokens->idToken.isEmpty()) {
        auto savedTokens = m_dbService->getTweekTokens(m_currentUserId);
        if (!savedTokens) {
            m_taskSelectionView->showError("Пожалуйста, сначала выполните полную синхронизацию (кнопка 'Синхронизация'), чтобы войти в Tweek.");
            return;
        }
        m_currentTweekTokens = savedTokens;
    }

    QString calendarId = m_dbService->getTweekDefaultCalendar(m_currentUserId);
    if (calendarId.isEmpty()) {
        m_taskSelectionView->showError("Не выбран календарь для синхронизации. Пожалуйста, выполните полную синхронизацию и выберите календарь.");
        return;
    }

    QVariantMap taskData = m_dbService->getTaskDetails(taskId.toInt());
    if (taskData.isEmpty()) {
        m_taskSelectionView->showError("Не удалось найти информацию о задаче.");
        return;
    }

    QString tweekId = taskData["tweek_task_id"].toString();
    QString title = taskData["title"].toString();
    QString description = taskData["description"].toString();

    connect(m_tweekApiService.get(), &ITweekApiService::taskCreateSuccess, this, &ApplicationController::onTweekTaskCreateSuccess, Qt::UniqueConnection);
    connect(m_tweekApiService.get(), &ITweekApiService::taskCreateFailed, this, &ApplicationController::onTweekTaskCreateFailed, Qt::UniqueConnection);
    connect(m_tweekApiService.get(),
            static_cast<void(ITweekApiService::*)(int)>(&ITweekApiService::taskUpdateSuccess),
            this,
            &ApplicationController::onTweekTaskUpdateSuccess,
            Qt::UniqueConnection);

    connect(m_tweekApiService.get(),
            static_cast<void(ITweekApiService::*)(int, const QString&, int)>(&ITweekApiService::taskUpdateFailed),
            this,
            &ApplicationController::onTweekTaskUpdateFailed,
            Qt::UniqueConnection);
    m_taskSelectionView->showLoading(true);

    if (tweekId.isEmpty()) {
        qDebug() << "Создание новой задачи в Tweek...";
        m_tweekApiService->createTaskInTweek(m_currentTweekTokens->idToken, calendarId, title, description, taskId.toInt());
    } else {
        qDebug() << "Обновление существующей задачи в Tweek:" << tweekId;
        m_tweekApiService->updateTaskInTweek(m_currentTweekTokens->idToken, tweekId, title, description, taskId.toInt());
    }
}

void ApplicationController::onTweekTaskCreateSuccess(int localTaskId, const QString& newTweekTaskId)
{
    m_taskSelectionView->showLoading(false);
    qDebug() << "Задача" << localTaskId << "успешно создана в Tweek с ID:" << newTweekTaskId;

    m_dbService->saveTweekTaskId(localTaskId, newTweekTaskId);

    QMessageBox::information(m_taskSelectionView->getWidget(), "Успех", "Задача успешно добавлена в календарь Tweek.");
}

void ApplicationController::onTweekTaskCreateFailed(int localTaskId, const QString& error)
{
    m_taskSelectionView->showLoading(false);
    qWarning() << "Ошибка создания задачи" << localTaskId << "в Tweek:" << error;
    m_taskSelectionView->showError("Не удалось создать задачу в Tweek: " + error);
}

void ApplicationController::onTweekTaskUpdateSuccess(int localTaskId)
{
    m_taskSelectionView->showLoading(false);
    qDebug() << "Задача" << localTaskId << "успешно обновлена в Tweek.";
    QMessageBox::information(m_taskSelectionView->getWidget(), "Успех", "Задача успешно обновлена в календаре Tweek.");
}

void ApplicationController::onTweekTaskUpdateFailed(int localTaskId, const QString& error, int httpStatusCode)
{
    m_taskSelectionView->showLoading(false);


    if (httpStatusCode == 404) {
        qWarning() << "Задача " << localTaskId << " не найдена в Tweek (404). Разрываем связь.";
        m_dbService->clearTweekTaskId(localTaskId);
        QMessageBox::warning(m_taskSelectionView->getWidget(),
                             "Задача не найдена",
                             "Похоже, эта задача была удалена в Tweek. Связь с календарем была разорвана. Нажмите обновить ещё раз");
        refreshTaskList();
    } else {
        qWarning() << "Ошибка обновления задачи" << localTaskId << "в Tweek:" << error << "(Код: " << httpStatusCode << ")";
        m_taskSelectionView->showError("Не удалось обновить задачу в Tweek: " + error);
    }
}
void ApplicationController::onTweekDisconnectRequested()
{
    if (!m_synchronizationView) return;

    qDebug() << "Выход из аккаунта Tweek для пользователя" << m_currentUserId;

    m_dbService->clearTweekData(m_currentUserId);

    m_currentTweekTokens.reset();

    m_synchronizationView->logMessage("Вы успешно вышли из аккауунта.");
    m_synchronizationView->showState(ISynchronizationView::ViewState::Login);
    m_synchronizationView->setControlsEnabled(true);
}
void ApplicationController::saveCurrentSession()
{
    switch (m_currentTimerMode) {
    case TimerMode::Stopwatch:
        if (m_elapsedSeconds > 0) {
            QDateTime endTime = QDateTime::currentDateTime();
            m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
        }
        break;

    case TimerMode::Pomodoro:
        if (m_currentPomodoroState == PomodoroState::Work) {
            qint64 elapsedInSession = m_pomodoroWorkDurationSecs - m_secondsRemainingInSession;
            if (elapsedInSession > 0) {
                QDateTime endTime = m_sessionStartTime.addSecs(elapsedInSession);
                m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
            }
        }
        break;

    case TimerMode::None:
    default:
        break;
    }
}
