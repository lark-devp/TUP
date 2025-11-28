#pragma once

#include "ui/interfaces/ITaskSelectionView.h"


class QListWidget;
class QPushButton;
class QLabel;
class QStackedWidget;
class QListWidgetItem;

class MinimalTaskSelectionView : public ITaskSelectionView
{
    Q_OBJECT

public:
    explicit MinimalTaskSelectionView(QWidget *parent = nullptr);
    ~MinimalTaskSelectionView() override = default;

    QWidget* getWidget() override;


    void displayTasks(const QVector<TaskDisplayData>& tasks) override;
    void showLoading(bool isLoading) override;
    void showError(const QString& message) override;

private slots:

    void onTaskSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void onItemDoubleClicked(QListWidgetItem* item);

    void onStartTimerClicked();
    void onShowStatsClicked();
    void onRefreshClicked();

private:

    QLabel* m_titleLabel;
    QListWidget* m_listWidget;
    QStackedWidget* m_stackedWidget;


    QPushButton* m_startTimerButton;
    QPushButton* m_statsButton;


    QPushButton* m_allStatsButton;
    QPushButton* m_addTaskButton;
    QPushButton* m_syncButton;
    QPushButton* m_refreshButton;
};
