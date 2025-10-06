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

class ApplicationController : public QObject
{
    Q_OBJECT


public:
    // Контроллер принимает во владение Фабрику
    explicit ApplicationController(std::unique_ptr<IUIFactory> factory, std::unique_ptr<IDatabaseService> dbService, std::unique_ptr<ITweekApiService> calendar, QObject *parent = nullptr);

    // Метод для запуска приложения (показа первого окна)
    void start();
    void showMainWindow(const QVector<TaskDisplayData>& tasks);
private slots:
    void onLoginRequested(const QString& username, const QString& password);

    void onTaskSelectedForTimer(const QString& taskId);
    void onStatisticsRequestedForTask(const QString& taskId);
    void onAllTasksStatisticsRequested();
    void onSynchronizationRequested();
    void onAddTaskRequested();

    //слоты при закрытии окон
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

private:
    /**
     * @brief Создает, настраивает и показывает главное окно приложения (список задач).
     * Вызывается после успешной авторизации.
     */

    void returnToTaskSelection();
    void refreshTaskList();
    void loadAndDisplayWeeklyStats();
    int m_currentUserId;

    // Поля для управления сессией таймера
    std::unique_ptr<QTimer> m_timer;
    QDateTime m_sessionStartTime;
    qint64 m_elapsedSeconds; // Прошедшие секунды с начала сессии
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

};
