#include "MinimalAddTaskView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

MinimalAddTaskView::MinimalAddTaskView(QWidget *parent)
    : IAddTaskView(parent)
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
            border-color: #4a90e2;
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
            border-color: #4a90e2;
        }
    )";

    const QString saveButtonStyle = R"(
        QPushButton {
           background-color: #4CAF50; /* Зеленый */
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px;
           border: none;
        }
        QPushButton:hover { background-color: #5cb85c; }
        QPushButton:pressed { background-color: #45a049; }
    )";

    const QString cancelButtonStyle = R"(
        QPushButton {
           background-color: #f44336; /* Красный */
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px;
           border: none;
        }
        QPushButton:hover { background-color: #e57373; }
        QPushButton:pressed { background-color: #d32f2f; }
    )";


    m_titleLabel = new QLabel("Новая задача", this);
    m_titleLineEdit = new QLineEdit(this);
    m_titleLineEdit->setPlaceholderText("Введите название задачи...");

    m_descriptionTextEdit = new QTextEdit(this);
    m_descriptionTextEdit->setPlaceholderText("Введите описание...");
    m_descriptionTextEdit->setMinimumHeight(200);
    m_saveButton = new QPushButton("Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);


    m_titleLabel->setStyleSheet(titleStyle);
    m_titleLineEdit->setStyleSheet(lineEditStyle);
    m_descriptionTextEdit->setStyleSheet(textEditStyle);
    m_saveButton->setStyleSheet(saveButtonStyle);
    m_cancelButton->setStyleSheet(cancelButtonStyle);

    for (auto* button : {m_saveButton, m_cancelButton}) {
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
    setWindowTitle("Добавление задачи");



    connect(m_saveButton, &QPushButton::clicked, this, &MinimalAddTaskView::onSaveClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &MinimalAddTaskView::onCancelClicked);
}


QWidget* MinimalAddTaskView::getWidget()
{
    return this;
}

void MinimalAddTaskView::clearForm()
{
    m_titleLineEdit->clear();
    m_descriptionTextEdit->clear();
}

void MinimalAddTaskView::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Ошибка валидации", message);
}

void MinimalAddTaskView::setTaskData(const QString& title, const QString& description)
{
    m_titleLineEdit->setText(title);
    m_descriptionTextEdit->setText(description);
    m_titleLabel->setText("Редактирование задачи");
    setWindowTitle("Редактирование задачи");
}



void MinimalAddTaskView::onSaveClicked()
{
    QString title = m_titleLineEdit->text();
    QString description = m_descriptionTextEdit->toPlainText();

    emit saveTaskRequested(title, description);
}

void MinimalAddTaskView::onCancelClicked()
{
    emit cancelRequested();
}
