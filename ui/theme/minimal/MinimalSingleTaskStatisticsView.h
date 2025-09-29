#pragma once

#include "ui/interfaces/ISingleTaskStatisticsView.h" // Убедитесь, что путь к вашему интерфейсу корректен

// Предварительные объявления классов Qt
class QLabel;
class QDateEdit;
class QTableView;
class QStandardItemModel;
class QVBoxLayout;
class QCloseEvent;
class QWidget;

/**
 * @brief Класс минималистичной реализации окна статистики по одной задаче.
 */
class MinimalSingleTaskStatisticsView : public ISingleTaskStatisticsView
{
    Q_OBJECT

public:
    explicit MinimalSingleTaskStatisticsView(QWidget *parent = nullptr);
    ~MinimalSingleTaskStatisticsView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---

    // Из IView
    QWidget* getWidget() override;

    // Из ISingleTaskStatisticsView
    void setTaskTitle(const QString& title) override;
    void displayStatistics(const QVariantMap& statsData) override;
    void showLoading(bool isLoading) override;

protected:
    // Переопределяем событие закрытия окна для отправки сигнала
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Внутренний слот для реакции на изменение дат в UI
    void onDateWidgetsChanged();

private:
    // --- UI-элементы ---
    QLabel* m_taskTitleLabel;
    QDateEdit* m_fromDateEdit;
    QDateEdit* m_toDateEdit;
    QTableView* m_statisticsView;
    QStandardItemModel* m_statisticsModel;
    QLabel* m_loadingLabel; // Простой виджет для индикации загрузки

    // --- Компоновка ---
    QVBoxLayout* m_mainLayout;
};
