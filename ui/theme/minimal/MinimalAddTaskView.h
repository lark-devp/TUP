#pragma once

#include "ui/interfaces/IAddTaskView.h"


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



    QWidget* getWidget() override;

    void clearForm() override;
    void showValidationError(const QString& message) override;
    void setTaskData(const QString& title, const QString& description) override;

private slots:

    void onSaveClicked();
    void onCancelClicked();

private:

    QLabel* m_titleLabel;
    QLineEdit* m_titleLineEdit;
    QTextEdit* m_descriptionTextEdit;

    // Кнопки
    QPushButton* m_saveButton;
    QPushButton* m_cancelButton;
};
