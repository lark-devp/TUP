#pragma once

#include "IView.h"
#include <QObject>
#include <QVariantMap>
#include <QDate>

/**
 * @brief Интерфейс для окна общей статистики по всем задачам.
 */
class IAllTasksStatisticsView : public IView
{
    Q_OBJECT

public:
    ~IAllTasksStatisticsView() override = default;

    // Методы для управления видом
    virtual void displayOverallStatistics(const QVariantMap& statsData) = 0;
    virtual void showLoading(bool isLoading) = 0;

signals:
    // Сигналы о действиях пользователя
    void dateRangeChanged(const QDate& from, const QDate& to);
    void closeRequested();
};
