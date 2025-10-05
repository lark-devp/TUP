#pragma once

#include "IView.h"
#include <QObject>
#include <QVector>
#include <QString>

// Структура для хранения сводных данных по одной задаче
struct TaskTimeSummary {
    QString title;
    qint64 totalMinutes;
};

/**
 * @brief Интерфейс для окна общей статистики по всем задачам.
 */
class IAllTasksStatisticsView : public IView
{
    Q_OBJECT

public:
    explicit IAllTasksStatisticsView(QWidget * parent = nullptr) : IView(parent) {}
    ~IAllTasksStatisticsView() override = default;

    // Методы для управления видом
    virtual void displayTaskSummaries(const QVector<TaskTimeSummary>& summaries) = 0;
    virtual void showLoading(bool isLoading) = 0;

signals:
    // Сигналы о действиях пользователя
    void closeRequested();

};
