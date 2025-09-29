#pragma once

#include "IView.h"
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QDate>

/**
 * @brief Интерфейс для окна статистики по одной задаче.
 */
class ISingleTaskStatisticsView :  public IView
{
    Q_OBJECT

public:
    // Этот конструктор будет принимать 'parent' и передавать его дальше в IView.
    explicit ISingleTaskStatisticsView(QWidget * parent = nullptr) : IView(parent) {}

    ~ISingleTaskStatisticsView() override = default;

    // Методы для управления видом
    virtual void setTaskTitle(const QString& title) = 0;
    virtual void displayStatistics(const QVariantMap& statsData) = 0;
    virtual void showLoading(bool isLoading) = 0;

signals:
    // Сигналы о действиях пользователя
    void dateRangeChanged(const QDate& from, const QDate& to);
    void closeRequested();
    void taskSelectedForStatistics(const QString& taskId);
};
