#pragma once

#include "IView.h"
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QDate>
#include <QVector> // Добавили

class ISingleTaskStatisticsView : public IView
{
    Q_OBJECT

public:
    explicit ISingleTaskStatisticsView(QWidget * parent = nullptr) : IView(parent) {}
    ~ISingleTaskStatisticsView() override = default;

    virtual void setTaskTitle(const QString& title) = 0;
    virtual void displayWeeklyChart(const QVector<qint64>& weeklyData, const QString& weekRangeLabel) = 0;
    virtual void showLoading(bool isLoading) = 0;

signals:
    void weekChanged(const QDate& weekStartDate);
    void closeRequested();
};
