#pragma once

#include "ui/interfaces/ISingleTaskStatisticsView.h"
#include "BarChartView.h" // Подключаем наш новый виджет

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

    // --- Реализация методов интерфейса IView ---
    QWidget* getWidget() override;

    // --- Реализация методов интерфейса ISingleTaskStatisticsView ---
    void setTaskTitle(const QString& title) override;
    void displayWeeklyChart(const QVector<qint64>& weeklyData, const QString& weekRangeLabel) override;
    void showLoading(bool isLoading) override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Слоты для кнопок навигации
    void onPrevWeekClicked();
    void onNextWeekClicked();

private:
    // UI Элементы
    QVBoxLayout* m_mainLayout;
    QLabel* m_taskTitleLabel;
    QLabel* m_loadingLabel;


    // Новые элементы для диаграммы и навигации
    BarChartView* m_chartView;
    QLabel* m_weekRangeLabel;
    QPushButton* m_prevWeekButton;
    QPushButton* m_nextWeekButton;

    // Храним дату начала текущей недели
    QDate m_currentWeekStart;
};
