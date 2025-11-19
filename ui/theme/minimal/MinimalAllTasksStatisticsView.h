#pragma once

#include "ui/interfaces/IAllTasksStatisticsView.h"

class QLabel;
class QPushButton;
class QTableView;
class QStandardItemModel;
class QStackedWidget;

class MinimalAllTasksStatisticsView : public IAllTasksStatisticsView
{
    Q_OBJECT

public:
    explicit MinimalAllTasksStatisticsView(QWidget *parent = nullptr);
    ~MinimalAllTasksStatisticsView() override = default;

    QWidget* getWidget() override;
    void displayTaskSummaries(const QVector<TaskTimeSummary>& summaries) override;
    void showLoading(bool isLoading) override;

private:
    QString formatMinutes(qint64 minutes);

    QLabel* m_titleLabel;
    QPushButton* m_closeButton;
    QStackedWidget* m_stackedWidget;
    QTableView* m_statsTableView;
    QStandardItemModel* m_model;
};
