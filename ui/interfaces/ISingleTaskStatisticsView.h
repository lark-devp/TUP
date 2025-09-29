#pragma once

#include "IView.h"
#include <QObject>
#include <QString>
#include <QVariantMap> // Для гибкой передачи данных для графиков
#include <QDate>

/**
 * @brief Интерфейс для окна статистики по одной задаче.
 */
class ISingleTaskStatisticsView : public IView
{
    Q_OBJECT

public:
    ~ISingleTaskStatisticsView() override = default;

    // Методы для управления видом
    virtual void setTaskTitle(const QString& title) = 0;
    virtual void displayStatistics(const QVariantMap& statsData) = 0;
    virtual void showLoading(bool isLoading) = 0;

signals:
    // Сигналы о действиях пользователя
    void dateRangeChanged(const QDate& from, const QDate& to);
    void closeRequested();
};
