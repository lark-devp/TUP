#pragma once

#include "ui/interfaces/IAddTaskView.h" // Убедитесь, что путь к вашему интерфейсу правильный

// Предварительные объявления классов Qt для уменьшения зависимостей в заголовке
class QLineEdit;
class QTextEdit;
class QPushButton;
class QLabel;

/**
 * @brief Минималистичная реализация вида для добавления/редактирования задачи.
 */
class MinimalAddTaskView : public IAddTaskView
{
    Q_OBJECT

public:
    explicit MinimalAddTaskView(QWidget *parent = nullptr);
    ~MinimalAddTaskView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---
    // Из IView
    QWidget* getWidget() override;

    // Из IAddTaskView
    void clearForm() override;
    void showValidationError(const QString& message) override;
    void setTaskData(const QString& title, const QString& description) override;

private slots:
    // Внутренние слоты для обработки действий пользователя
    void onSaveClicked();
    void onCancelClicked();

private:
    // Указатели на UI-элементы
    QLabel* m_titleLabel;
    QLineEdit* m_titleLineEdit;
    QTextEdit* m_descriptionTextEdit;

    // Кнопки
    QPushButton* m_saveButton;
    QPushButton* m_cancelButton;
};
