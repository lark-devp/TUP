#include "MinimalEditTaskView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

MinimalEditTaskView::MinimalEditTaskView(QWidget *parent)
    : IEditTaskView(parent)
{
    this->setStyleSheet("background-color: #f4f7fa;");

    const QString titleStyle = R"(
        font-size: 22px;
        font-weight: bold;
        color: #333;
        margin-bottom: 10px;
    )";

    const QString lineEditStyle = R"(
        QLineEdit {
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 10px;
            background-color: #ffffff;
            font-size: 14px;
        }
        QLineEdit:focus {
            border-color: #4a90e2; /* Синий при фокусе */
        }
    )";

    const QString textEditStyle = R"(
        QTextEdit {
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 10px;
            background-color: #ffffff;
            font-size: 14px;
        }
        QTextEdit:focus {
            border-color: #4a90e2; /* Синий при фокусе */
        }
    )";

    const QString saveButtonStyle = R"(
        QPushButton {
           background-color: #4CAF50; /* Зеленый */
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px 15px;
           border: none;
        }
        QPushButton:hover { background-color: #5cb85c; }
        QPushButton:pressed { background-color: #45a049; }
    )";

    const QString deleteButtonStyle = R"(
        QPushButton {
           background-color: #f44336; /* Красный */
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px 15px;
           border: none;
        }
        QPushButton:hover { background-color: #e57373; }
        QPushButton:pressed { background-color: #d32f2f; }
    )";

    const QString cancelButtonStyle = R"(
        QPushButton {
           background-color: #6c757d; /* Серый */
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px 15px;
           border: none;
        }
        QPushButton:hover { background-color: #868e96; }
        QPushButton:pressed { background-color: #5a6268; }
    )";


    m_titleLabel = new QLabel("Редактирование задачи", this);
    m_titleLineEdit = new QLineEdit(this);
    m_titleLineEdit->setPlaceholderText("Название задачи...");

    m_descriptionTextEdit = new QTextEdit(this);
    m_descriptionTextEdit->setPlaceholderText("Описание задачи...");
    m_descriptionTextEdit->setMinimumHeight(200);

    m_saveButton = new QPushButton("Сохранить", this);
    m_deleteButton = new QPushButton("Удалить", this);
    m_cancelButton = new QPushButton("Отмена", this);


    m_titleLabel->setStyleSheet(titleStyle);
    m_titleLineEdit->setStyleSheet(lineEditStyle);
    m_descriptionTextEdit->setStyleSheet(textEditStyle);
    m_saveButton->setStyleSheet(saveButtonStyle);
    m_deleteButton->setStyleSheet(deleteButtonStyle);
    m_cancelButton->setStyleSheet(cancelButtonStyle);

    for (auto* button : {m_saveButton, m_deleteButton, m_cancelButton}) {
        button->setCursor(Qt::PointingHandCursor);
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }


    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(new QLabel("Название:", this));
    mainLayout->addWidget(m_titleLineEdit);
    mainLayout->addWidget(new QLabel("Описание:", this));
    mainLayout->addWidget(m_descriptionTextEdit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Редактирование задачи");




    connect(m_saveButton, &QPushButton::clicked, this, &MinimalEditTaskView::onSaveClicked);
    connect(m_deleteButton, &QPushButton::clicked, this, &MinimalEditTaskView::onDeleteClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &MinimalEditTaskView::onCancelClicked);
}


QWidget* MinimalEditTaskView::getWidget()
{
    return this;
}

void MinimalEditTaskView::setTaskData(const QString& title, const QString& description)
{
    m_titleLineEdit->setText(title);
    m_descriptionTextEdit->setText(description);
}

void MinimalEditTaskView::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Ошибка валидации", message);
}



void MinimalEditTaskView::onSaveClicked()
{
    emit saveTaskRequested(m_titleLineEdit->text(), m_descriptionTextEdit->toPlainText());
}

void MinimalEditTaskView::onDeleteClicked()
{
    auto reply = QMessageBox::question(this, "Подтверждение удаления",
                                       "Вы уверены, что хотите удалить эту задачу?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit deleteTaskRequested();
    }
}

void MinimalEditTaskView::onCancelClicked()
{
    emit cancelRequested();
}
