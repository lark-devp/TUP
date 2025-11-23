#pragma once

#include "ui/interfaces/ISingleTaskStatisticsView.h"
#include "BarChartView.h"

class QLabel;
class QVBoxLayout;
class QPushButton;
class QStackedWidget;

class MinimalSingleTaskStatisticsView : public ISingleTaskStatisticsView
{
    Q_OBJECT

public:
    explicit MinimalSingleTaskStatisticsView(QWidget *parent = nullptr);
    ~MinimalSingleTaskStatisticsView() override = default;

    QWidget* getWidget() override;

    void setTaskTitle(const QString& title) override;
    void displayWeeklyChart(const QVector<qint64>& weeklyData, const QString& weekRangeLabel) override;
    void showLoading(bool isLoading) override;

private slots:
    void onPrevWeekClicked();
    void onNextWeekClicked();

private:
    QLabel* m_taskTitleLabel;
    QLabel* m_loadingLabel;
    QStackedWidget* m_stackedWidget;
    BarChartView* m_chartView;
    QLabel* m_weekRangeLabel;
    QPushButton* m_prevWeekButton;
    QPushButton* m_nextWeekButton;
    QPushButton* m_closeButton;
    QDate m_currentWeekStart;
};
