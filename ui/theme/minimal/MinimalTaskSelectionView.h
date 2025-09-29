#pragma once

#include "ui/interfaces/ITaskSelectionView.h" // Подключаем ваш интерфейс

// Предварительные объявления классов Qt, чтобы не утяжелять заголовок
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

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---
    // Из IView
    QWidget* getWidget() override;

    // Из ITaskSelectionView
    void displayTasks(const QVector<TaskDisplayData>& tasks) override;
    void showLoading(bool isLoading) override;
    void showError(const QString& message) override;

private slots:
    // Внутренний слот для реакции на выбор элемента в списке
    void onTaskSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous);

    // Слоты для обработки нажатий кнопок, требующих ID задачи
    void onStartTimerClicked();
    void onShowStatsClicked();

private:
    // Указатели на UI-элементы
    QLabel* m_titleLabel;
    QListWidget* m_listWidget;
    QStackedWidget* m_stackedWidget; // Для переключения между списком и загрузкой

    // Кнопки для действий с выбранной задачей
    QPushButton* m_startTimerButton;
    QPushButton* m_statsButton;

    // Кнопки для общих действий
    QPushButton* m_allStatsButton;
    QPushButton* m_addTaskButton;
    QPushButton* m_syncButton;
    QPushButton* m_refreshButton;
};
