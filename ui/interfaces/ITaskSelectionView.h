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
    // Этот конструктор будет принимать 'parent' и передавать его дальше в IView.
    explicit ITaskSelectionView(QWidget * parent = nullptr) : IView(parent) {}

    ~ITaskSelectionView() override = default;


    // Методы для управления видом извне (например, из Presenter'а)
    virtual void displayTasks(const QVector<TaskDisplayData>& tasks) = 0;
    virtual void showLoading(bool isLoading) = 0;
    virtual void showError(const QString& message) = 0;

signals:
    // Сигналы о действиях пользователя
    void taskSelectedForTimer(const QString& taskId);
    void statisticsRequestedForTask(const QString& taskId);
    void allTasksStatisticsRequested();
    void addTaskRequested();
    void synchronizationRequested();
    void refreshRequested();
};
