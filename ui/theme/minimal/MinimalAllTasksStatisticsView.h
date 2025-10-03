#pragma once

#include "ui/interfaces/IAllTasksStatisticsView.h" // Путь к вашему интерфейсу

// Предварительные объявления классов Qt для облегчения заголовка
class QLabel;
class QDateEdit;
class QPushButton;
class QTableView;
class QStandardItemModel;
class QStackedWidget;

/**
 * @brief Минималистичная реализация окна общей статистики.
 *
 * Отображает статистику в виде таблицы и предоставляет элементы
 * управления для выбора диапазона дат.
 */
class MinimalAllTasksStatisticsView : public IAllTasksStatisticsView
{
    Q_OBJECT

public:
    explicit MinimalAllTasksStatisticsView(QWidget *parent = nullptr);
    ~MinimalAllTasksStatisticsView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---
    // Из IView
    QWidget* getWidget() override;

    // Из IAllTasksStatisticsView
    void displayOverallStatistics(const QVariantMap& statsData) override;
    void showLoading(bool isLoading) override;

private slots:
    // Внутренний слот для реакции на нажатие кнопки "Применить"
    void onApplyDateRangeClicked();

private:
    // Указатели на UI-элементы
    QLabel* m_titleLabel;
    QDateEdit* m_fromDateEdit;
    QDateEdit* m_toDateEdit;
    QPushButton* m_applyButton;
    QPushButton* m_closeButton;
    QStackedWidget* m_stackedWidget; // Для переключения между таблицей и загрузкой

    // Элементы для отображения статистики
    QTableView* m_statsTableView;
    QStandardItemModel* m_model; // Модель данных для таблицы
};
