#pragma once

#include "IView.h"
#include <QObject>
#include <QString>
#include <QVector>

/**
 * @brief Структура для отображения задачи в списке.
 */
struct TaskDisplayData {
    QString id;
    QString title;
};

/**
 * @brief Интерфейс для окна выбора задач.
 */
class ITaskSelectionView : public IView
{
    Q_OBJECT

public:
    explicit ITaskSelectionView(QWidget * parent = nullptr) : IView(parent) {}

    ~ITaskSelectionView() override = default;


    virtual void displayTasks(const QVector<TaskDisplayData>& tasks) = 0;
    virtual void showLoading(bool isLoading) = 0;
    virtual void showError(const QString& message) = 0;
    virtual void setupConnections() = 0;

signals:

    void taskSelectedForTimer(const QString& taskId);
    void editTaskRequested(const QString& taskId);
    void statisticsRequestedForTask(const QString& taskId);
    void allTasksStatisticsRequested();
    void addTaskRequested();
    void synchronizationRequested();
    void syncSingleTaskRequested(const QString& taskId);
    void refreshRequested();
    void logoutRequested();
};
