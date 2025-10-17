#pragma once

#include "ui/interfaces/IEditTaskView.h"

class QLineEdit;
class QTextEdit;
class QPushButton;
class QLabel;

/**
 * @brief Минималистичная реализация вида для редактирования/удаления задачи.
 */
class MinimalEditTaskView : public IEditTaskView
{
    Q_OBJECT

public:
    explicit MinimalEditTaskView(QWidget *parent = nullptr);
    ~MinimalEditTaskView() override = default;

    // Реализация методов базового интерфейса IView
    QWidget* getWidget() override;

    // Реализация методов интерфейса IEditTaskView
    void setTaskData(const QString& title, const QString& description) override;
    void showValidationError(const QString& message) override;

private slots:
    // Слоты для обработки нажатий на кнопки
    void onSaveClicked();
    void onDeleteClicked();
    void onCancelClicked();

private:
    // UI элементы
    QLabel* m_titleLabel;
    QLineEdit* m_titleLineEdit;
    QTextEdit* m_descriptionTextEdit;

    // Кнопки
    QPushButton* m_saveButton;
    QPushButton* m_deleteButton;
    QPushButton* m_cancelButton;
};
