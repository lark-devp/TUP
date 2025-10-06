#include "MinimalSynchronizationView.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLabel>

MinimalSynchronizationView::MinimalSynchronizationView(QWidget *parent)
    : ISynchronizationView(parent)
{
    // --- 1. Определение стилей ---

    this->setStyleSheet("background-color: #f4f7fa;"); // Общий фон

    const QString titleStyle = R"(
        font-size: 20px;
        font-weight: bold;
        color: #333;
        margin-bottom: 5px;
    )";

    const QString statusStyle = R"(
        font-size: 14px;
        color: #555;
        margin-bottom: 15px;
    )";

    const QString logStyle = R"(
        QTextEdit {
            background-color: #ffffff;
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            font-family: 'Courier New', Courier, monospace;
            font-size: 12px;
            color: #333;
        }
    )";

    const QString progressBarStyle = R"(
        QProgressBar {
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            text-align: center;
            background-color: #ffffff;
            color: #333;
        }
        QProgressBar::chunk {
            background-color: #4a90e2;
            border-radius: 7px;
        }
    )";

    const QString buttonStyle = R"(
        QPushButton {
           background-color: #4a90e2;
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px;
           border: none;
           margin-top: 10px;
        }
        QPushButton:hover { background-color: #5aa1f2; }
        QPushButton:pressed { background-color: #3a80d2; }
        QPushButton:disabled {
           background-color: #dcdcdc;
           color: #a0a0a0;
        }
    )";


    // --- 2. Создание и стилизация виджетов ---
    auto titleLabel = new QLabel("Введите данные от Tweek", this);
    titleLabel->setStyleSheet(titleStyle); // <--- Применение стиля

    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setPlaceholderText("your@example.com");

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    m_connectButton = new QPushButton("Подключить", this);
    m_connectButton->setStyleSheet(buttonStyle); // <--- Применение стиля

    m_closeButton = new QPushButton("Закрыть", this);
    m_closeButton->setStyleSheet(buttonStyle); // <--- Применение стиля

    m_statusLabel = new QLabel("Готово к подключению.", this);
    m_statusLabel->setStyleSheet(statusStyle); // <--- Применение стиля

    m_progressBar = new QProgressBar(this);
    m_progressBar->setStyleSheet(progressBarStyle); // <--- Применение стиля

    m_logView = new QTextEdit(this);
    m_logView->setReadOnly(true);
    m_logView->setStyleSheet(logStyle); // <--- Применение стиля

    // --- 3. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    auto formLayout = new QFormLayout();
    formLayout->addRow("Email:", m_emailEdit);
    formLayout->addRow("Пароль:", m_passwordEdit);

    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(m_connectButton);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->addWidget(m_progressBar);
    mainLayout->addWidget(m_logView);
    mainLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

    setLayout(mainLayout);
    setMinimumSize(450, 500);

    // Изначально кнопка закрытия заблокирована во время "процесса"
    setCloseButtonEnabled(true);

    // --- 4. Соединение сигналов ---
    connect(m_connectButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onConnectClicked);
    connect(m_closeButton, &QPushButton::clicked, this, &ISynchronizationView::closeRequested);
}

QWidget* MinimalSynchronizationView::getWidget() { return this; }
void MinimalSynchronizationView::updateStatus(const QString& status) { m_statusLabel->setText(status); }
void MinimalSynchronizationView::logMessage(const QString& msg) { m_logView->append(msg); }
void MinimalSynchronizationView::setProgress(int p) { m_progressBar->setValue(p); }
void MinimalSynchronizationView::setCloseButtonEnabled(bool en) { m_closeButton->setEnabled(en); }

void MinimalSynchronizationView::onConnectClicked()
{
    // Блокируем кнопку, чтобы избежать двойных нажатий
    m_connectButton->setEnabled(false);
    // Отправляем сигнал наружу с данными из полей
    emit connectRequested(m_emailEdit->text(), m_passwordEdit->text());
}
