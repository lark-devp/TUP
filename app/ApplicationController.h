#pragma once

#include <QObject>
#include <memory>
#include <QTimer>
#include <QDateTime>
#include "ui/interfaces/IUIFactory.h"
#include "ui/interfaces/ITaskSelectionView.h"
#include "ui/interfaces/ITimerView.h"
#include "ui/interfaces/ISingleTaskStatisticsView.h"
#include "ui/interfaces/IAddTaskView.h"
#include "ui/interfaces/IAuthorizationView.h"
#include "db/IDatabaseService.h"
#include "calendar/ITweekApiService.h"
#include "ui/interfaces/IEditTaskView.h"


class ApplicationController : public QObject
{
    Q_OBJECT


public:

    explicit ApplicationController(std::unique_ptr<IUIFactory> factory, std::unique_ptr<IDatabaseService> dbService, std::unique_ptr<ITweekApiService> calendar, QObject *parent = nullptr);


    void start();
    void showMainWindow(const QVector<TaskDisplayData>& tasks);
private slots:
    void onLoginRequested(const QString& username, const QString& password);
    void onRegistrationSubmitted(const QString& username, const QString& email, const QString& password);
    void onRecoverySubmitted(const QString& email);
    void onBackToLoginRequested();

    void onTaskSelectedForTimer(const QString& taskId);
    void onStatisticsRequestedForTask(const QString& taskId);
    void onAllTasksStatisticsRequested();
    void onSynchronizationRequested();
    void onAddTaskRequested();


    void onTimerClosed();
    void onStatisticsClosed();
    void onAllTasksStatisticsClosed();
    void onSynchronizationClosed();
    void onAddTaskSaved(const QString& title, const QString& description);
    void onAddTaskCancelled();

    void onTimerStop();
    void onTimerTick();

    void onWeekChangeForStatisticsRequested(const QDate& weekStartDate);

    void onTweekConnectRequested(const QString& email, const QString& password);
    void onTweekAuthSuccess(const QString& idToken, const QString& refreshToken);
    void onTweekAuthFailed(const QString& error);

    void onCalendarsFetchSuccess(const QVector<TweekCalendar>& calendars);
    void onCalendarsFetchFailed(const QString& error);

    void onTasksFetchSuccess(const QVector<TweekTask>& tasks);
    void onTasksFetchFailed(const QString& error);

    void onSyncTasksSelected(const QVector<TweekTask>& selectedTasks);

    void onTimerModeSelected();
    void onPomodoroModeSelected(int workMinutes, int restMinutes);

    void onEditTaskRequested(const QString& taskId);
    void onEditTaskSaved(const QString& title, const QString& description);
    void onEditTaskDeleted();
    void onEditTaskCancelled();

    void onSyncSingleTaskToTweek(const QString& taskId);
    void onTweekTaskCreateSuccess(int localTaskId, const QString& newTweekTaskId);
    void onTweekTaskCreateFailed(int localTaskId, const QString& error);
    void onTweekTaskUpdateSuccess(const QString& tweekTaskId);
    void onTweekTaskUpdateFailed(const QString& tweekTaskId, const QString& error);


private:


    void returnToTaskSelection();
    void refreshTaskList();
    void loadAndDisplayWeeklyStats();
    void startNextPomodoroSession();
    void handlePomodoroSessionFinish();
    int m_currentUserId;
    int m_currentEditingTaskId;
    enum class TimerMode { None, Stopwatch, Pomodoro };
    enum class PomodoroState { Work, Rest };

    TimerMode m_currentTimerMode = TimerMode::None;
    PomodoroState m_currentPomodoroState;


    qint64 m_elapsedSeconds;


    int m_pomodoroWorkDurationSecs;
    int m_pomodoroRestDurationSecs;
    int m_pomodoroTotalSessions = 4;
    int m_pomodoroSessionsCompleted = 0;
    qint64 m_secondsRemainingInSession;


    std::unique_ptr<QTimer> m_timer;
    QDateTime m_sessionStartTime;
    int m_currentTimingTaskId;

    // Поля для хранения контекста окна статистики
    int m_currentStatisticsTaskId;
    QDate m_currentStatisticsWeekStart;

    // Контроллер владеет фабрикой
    std::unique_ptr<IUIFactory> m_factory;
    std::unique_ptr<IDatabaseService> m_dbService;

    // Контроллер хранит указатели на текущие активные окна
    std::unique_ptr<IAuthorizationView> m_authorizationView;
    std::unique_ptr<ITaskSelectionView> m_taskSelectionView;
    std::unique_ptr<ITimerView> m_timerView;
    std::unique_ptr<ISingleTaskStatisticsView> m_statisticsView;
    std::unique_ptr<IAllTasksStatisticsView> m_allTasksStatisticsView;
    std::unique_ptr<ISynchronizationView> m_synchronizationView;
    std::unique_ptr<IAddTaskView> m_addTaskView;
    std::unique_ptr<ITweekApiService> m_tweekApiService;
    std::optional<TweekTokens> m_currentTweekTokens;
    std::unique_ptr<IEditTaskView> m_editTaskView;

};
