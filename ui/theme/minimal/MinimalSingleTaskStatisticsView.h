#pragma once

#include "ui/interfaces/ISingleTaskStatisticsView.h"
#include "BarChartView.h"

class QLabel;
class QTableView;
class QStandardItemModel;
class QVBoxLayout;
class QPushButton;

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:

    void onPrevWeekClicked();
    void onNextWeekClicked();

private:

    QVBoxLayout* m_mainLayout;
    QLabel* m_taskTitleLabel;
    QLabel* m_loadingLabel;



    BarChartView* m_chartView;
    QLabel* m_weekRangeLabel;
    QPushButton* m_prevWeekButton;
    QPushButton* m_nextWeekButton;


    QDate m_currentWeekStart;
};
