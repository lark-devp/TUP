#include "ApplicationController.h"
#include <QDebug>
#include <QVector>
#include <QDate>

ApplicationController::ApplicationController(std::unique_ptr<IUIFactory> factory,std::unique_ptr<IDatabaseService> dbService,
                                             std::unique_ptr<ITweekApiService> calendar, QObject *parent)
    : QObject(parent)
    , m_factory(std::move(factory))
    , m_dbService(std::move(dbService)), m_tweekApiService(std::move(calendar))
{
}

void ApplicationController::start()
{
    m_authorizationView = m_factory->createAuthorizationWindow();
    if (!m_authorizationView) {
        qCritical() << "Критическая ошибка: не удалось создать окно авторизации!";
        return;
    }


    connect(m_authorizationView.get(), &IAuthorizationView::loginRequested, this, &ApplicationController::onLoginRequested);
    connect(m_authorizationView.get(), &IAuthorizationView::registrationSubmitted, this, &ApplicationController::onRegistrationSubmitted);
    connect(m_authorizationView.get(), &IAuthorizationView::recoverySubmitted, this, &ApplicationController::onRecoverySubmitted);
    connect(m_authorizationView.get(), &IAuthorizationView::backToLoginRequested, this, &ApplicationController::onBackToLoginRequested);

    m_authorizationView->showView();
}

void ApplicationController::onLoginRequested(const QString& username, const QString& password)
{
    qDebug() << "Попытка входа через БД для пользователя:" << username;
    m_authorizationView->showLoading(true);

    QVariantMap userData = m_dbService->authenticateUser(username, password);

    m_authorizationView->showLoading(false);
    if (!userData.isEmpty()) {
        qDebug() << "Аутентификация в БД успешна!";
        m_currentUserId = userData["user_id"].toInt();
        QVector<TaskDisplayData> tasks = m_dbService->getTasksForUser(m_currentUserId);

        m_authorizationView->hideView();
        m_authorizationView.reset();
        showMainWindow(tasks);
    } else {
        qDebug() << "Ошибка аутентификации в БД!";
        m_authorizationView->showError("Неверное имя пользователя или пароль");
    }
}

void ApplicationController::onRegistrationSubmitted(const QString& username, const QString& email, const QString& password)
{

    if (username.trimmed().isEmpty() || password.isEmpty() || email.trimmed().isEmpty()) {
        m_authorizationView->showError("Все поля должны быть заполнены.");
        return;
    }

    m_authorizationView->showLoading(true);
    bool success = m_dbService->addUser(username, email, password);
    m_authorizationView->showLoading(false);

    if (success) {
        m_authorizationView->showInfo("Регистрация прошла успешно! Теперь вы можете войти.");
        m_authorizationView->switchState(IAuthorizationView::State::Login);
    } else {
        m_authorizationView->showError("Такой пользователь уже существует.");
    }
}

void ApplicationController::onRecoverySubmitted(const QString& email)
{
    if (email.trimmed().isEmpty() || !email.contains('@')) {
        m_authorizationView->showError("Пожалуйста, введите корректный email.");
        return;
    }

    qDebug() << "Запрос на восстановление пароля для email:" << email;

    m_authorizationView->showInfo("Если пользователь с таким email существует, ссылка для сброса пароля была отправлена на почту.");
    m_authorizationView->switchState(IAuthorizationView::State::Login);
}

void ApplicationController::onBackToLoginRequested()
{
    m_authorizationView->switchState(IAuthorizationView::State::Login);
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

// Пользователь выбрал Помодоро
void ApplicationController::onPomodoroModeSelected(int workMinutes, int restMinutes)
{
    qDebug() << "Выбран режим Помодоро: " << workMinutes << "мин работа," << restMinutes << "мин отдых.";
    m_currentTimerMode = TimerMode::Pomodoro;
    m_pomodoroWorkDurationSecs = workMinutes * 60;
    m_pomodoroRestDurationSecs = restMinutes * 60;
    m_pomodoroSessionsCompleted = 0;

    if (!m_timer) {
        m_timer = std::make_unique<QTimer>(this);
        connect(m_timer.get(), &QTimer::timeout, this, &ApplicationController::onTimerTick);
    }

    startNextPomodoroSession();
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

// Логика завершения сессии Помодоро
void ApplicationController::handlePomodoroSessionFinish()
{
    if (m_timer) m_timer->stop();

    // Если закончилась рабочая сессия, сохраняем ее
    if (m_currentPomodoroState == PomodoroState::Work) {
        QDateTime endTime = m_sessionStartTime.addSecs(m_pomodoroWorkDurationSecs);
        m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
        qDebug() << "Рабочая сессия Помодоро сохранена.";
        m_pomodoroSessionsCompleted++;
    }

    // Проверяем, не закончили ли мы все циклы
    if (m_pomodoroSessionsCompleted >= m_pomodoroTotalSessions) {
        qDebug() << "Все сессии Помодоро завершены.";
        onTimerStop(); // Завершаем работу
        return;
    }

    // Если не все, запускаем следующую сессию
    startNextPomodoroSession();
}


void ApplicationController::startNextPomodoroSession()
{
    // Определяем, какая сессия будет следующей: работа или отдых
    // Если предыдущая была отдых ИЛИ это самый первый запуск, то начинаем РАБОТУ
    if (m_currentPomodoroState == PomodoroState::Rest || m_pomodoroSessionsCompleted == 0) {
        m_currentPomodoroState = PomodoroState::Work;
        m_secondsRemainingInSession = m_pomodoroWorkDurationSecs;
    } else { // Иначе - начинаем отдых
        m_currentPomodoroState = PomodoroState::Rest;
        m_secondsRemainingInSession = m_pomodoroRestDurationSecs;
    }

    m_sessionStartTime = QDateTime::currentDateTime();

    if (m_timerView) {
        bool isWork = (m_currentPomodoroState == PomodoroState::Work);
        m_timerView->displayPomodoroState(m_pomodoroTotalSessions - m_pomodoroSessionsCompleted, isWork);
    }

    if (m_timer) m_timer->start(1000);
}




void ApplicationController::onTimerStop()
{
    qDebug() << "Таймер остановлен. Сохранение сессии...";
    if (m_timer) m_timer->stop();

    // Сохраняем прогресс, только если таймер был запущен
    if (m_currentTimerMode == TimerMode::Stopwatch && m_elapsedSeconds > 0) {
        QDateTime endTime = QDateTime::currentDateTime();
        m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
    } else if (m_currentTimerMode == TimerMode::Pomodoro && m_currentPomodoroState == PomodoroState::Work) {
        // Если остановили во время работы, сохраняем фактически затраченное время
        qint64 elapsed = m_pomodoroWorkDurationSecs - m_secondsRemainingInSession;
        if (elapsed > 0) {
            QDateTime endTime = m_sessionStartTime.addSecs(elapsed);
            m_dbService->addTimeTrackingEntry(m_currentTimingTaskId, m_sessionStartTime, endTime);
        }
    }


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

    QDate weekEndDate = m_currentStatisticsWeekStart.addDays(6);
    QString weekRangeLabel = QString("%1 - %2")
                                 .arg(m_currentStatisticsWeekStart.toString("dd MMM"))
                                 .arg(weekEndDate.toString("dd MMM yyyy"));

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
                if (m_currentTweekTokens) {
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


    auto savedTokens = m_dbService->getTweekTokens(m_currentUserId);
    if (savedTokens && !savedTokens->refreshToken.isEmpty()) {
        qDebug() << "Найдены сохраненные токены Tweek. Обновление...";
        m_synchronizationView->showView();
        m_synchronizationView->showState(ISynchronizationView::ViewState::Sync);
        m_synchronizationView->updateStatus("Обновление сессии...");
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





// Этот слот вызовется, когда пользователь закроет окно синхронизации
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

    // 1. Получаем текущие данные задачи из БД
    QVariantMap taskData = m_dbService->getTaskDetails(m_currentEditingTaskId);
    if (taskData.isEmpty()) {
        qWarning() << "Не удалось получить данные для задачи" << taskId;
        // Можно показать ошибку пользователю
        return;
    }

    // 2. Скрываем список задач и создаем окно редактирования
    m_taskSelectionView->hideView();
    m_editTaskView = m_factory->createEditTaskWindow();

    // 3. Заполняем форму данными из БД
    m_editTaskView->setTaskData(taskData["title"].toString(), taskData["description"].toString());

    // 4. Подключаем сигналы от окна редактирования
    connect(m_editTaskView.get(), &IEditTaskView::saveTaskRequested, this, &ApplicationController::onEditTaskSaved);
    connect(m_editTaskView.get(), &IEditTaskView::deleteTaskRequested, this, &ApplicationController::onEditTaskDeleted);
    connect(m_editTaskView.get(), &IEditTaskView::cancelRequested, this, &ApplicationController::onEditTaskCancelled);

    // 5. Показываем окно
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

    // Обновляем данные в БД
    bool success = m_dbService->updateTask(m_currentEditingTaskId, title, description);

    if (success) {
        refreshTaskList();       // Обновляем список задач в главном окне
        returnToTaskSelection(); // Возвращаемся к списку задач
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

    // 1. Сохраняем свежие токены в БД и в текущую сессию
    m_dbService->saveTweekTokens(m_currentUserId, idToken, refreshToken);
    m_currentTweekTokens = TweekTokens{idToken, refreshToken};

    // Проверяем, что окно синхронизации все еще открыто
    if (!m_synchronizationView) return;

    // 2. Переключаем UI в режим синхронизации (если он еще не там)
    m_synchronizationView->showState(ISynchronizationView::ViewState::Sync);
    m_synchronizationView->logMessage("Аутентификация успешна. Загрузка календарей...");
    m_synchronizationView->updateStatus("Загрузка календарей...");
    m_synchronizationView->setControlsEnabled(false); // Держим UI заблокированным

    // 3. ИНИЦИИРУЕМ ЗАГРУЗКУ КАЛЕНДАРЕЙ, ИСПОЛЬЗУЯ СВЕЖИЙ ТОКЕН
    m_tweekApiService->fetchCalendars(m_currentTweekTokens->idToken);
}

// Слот ошибки теперь должен просто разблокировать контролы
void ApplicationController::onTweekAuthFailed(const QString& error)
{
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка: " + error);
    m_synchronizationView->updateStatus("Не удалось подключиться.");
    m_synchronizationView->setProgress(0);
    m_synchronizationView->setControlsEnabled(true);
}


void ApplicationController::onCalendarsFetchSuccess(const QVector<TweekCalendar>& calendars) {
    if (!m_synchronizationView) return;
    m_synchronizationView->displayCalendars(calendars);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->updateStatus("Календари загружены. Выберите задачи.");
}

void ApplicationController::onCalendarsFetchFailed(const QString& error) {
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка загрузки календарей: " + error);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->updateStatus("Ошибка загрузки календарей.");
}

void ApplicationController::onTasksFetchSuccess(const QVector<TweekTask>& tasks) {
    if (!m_synchronizationView) return;
    m_synchronizationView->displayTasks(tasks);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->updateStatus("Задачи загружены. Выберите нужные и подтвердите.");
}

void ApplicationController::onTasksFetchFailed(const QString& error) {
    if (!m_synchronizationView) return;
    m_synchronizationView->logMessage("Ошибка загрузки задач: " + error);
    m_synchronizationView->setControlsEnabled(true);
    m_synchronizationView->updateStatus("Ошибка загрузки задач.");
}

// Слот для сохранения выбранных задач в БД
void ApplicationController::onSyncTasksSelected(const QVector<TweekTask>& selectedTasks) {
    if (!m_synchronizationView) return;

    int successCount = 0;
    for (const auto& task : selectedTasks) {
        if (m_dbService->addTask(task.title, task.description, m_currentUserId)) {
            successCount++;
        }
    }

    m_synchronizationView->logMessage(QString("Успешно добавлено %1 из %2 задач.").arg(successCount).arg(selectedTasks.size()));
    m_synchronizationView->updateStatus("Задачи добавлены.");
    m_synchronizationView->setControlsEnabled(true);


    refreshTaskList();
}
