#include "MinimalSynchronizationView.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QFont>
#include <QGraphicsDropShadowEffect>

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


    // --- 2. Создание виджетов ---

    m_titleLabel = new QLabel("Синхронизация с календарем", this);
    m_statusLabel = new QLabel("Инициализация...", this);
    m_logEdit = new QTextEdit(this);
    m_progressBar = new QProgressBar(this);
    m_closeButton = new QPushButton("Закрыть", this);


    // --- 3. Настройка виджетов и применение стилей ---

    m_titleLabel->setStyleSheet(titleStyle);
    m_statusLabel->setStyleSheet(statusStyle);
    m_logEdit->setStyleSheet(logStyle);
    m_progressBar->setStyleSheet(progressBarStyle);
    m_closeButton->setStyleSheet(buttonStyle);

    m_logEdit->setReadOnly(true); // Лог только для чтения
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);

    // Изначально кнопка "Закрыть" неактивна, пока процесс не завершится
    setCloseButtonEnabled(false);

    // Добавляем тень и курсор для кнопки
    m_closeButton->setCursor(Qt::PointingHandCursor);
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 80));
    m_closeButton->setGraphicsEffect(shadow);


    // --- 4. Компоновка ---

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(25, 25, 25, 25);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_statusLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_progressBar);
    mainLayout->addWidget(m_logEdit); // Лог займет основное пространство
    mainLayout->addWidget(m_closeButton);

    setLayout(mainLayout);
    setWindowTitle("Процесс синхронизации");
    setMinimumSize(500, 400);


    // --- 5. Соединение сигналов ---

    // Соединяем нажатие кнопки с сигналом интерфейса, который должен быть обработан в Presenter/Controller
    connect(m_closeButton, &QPushButton::clicked, this, &ISynchronizationView::closeRequested);
}


// --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСА ---

QWidget* MinimalSynchronizationView::getWidget()
{
    return this;
}

void MinimalSynchronizationView::updateStatus(const QString& statusMessage)
{
    m_statusLabel->setText(statusMessage);
}

void MinimalSynchronizationView::logMessage(const QString& message)
{
    // append добавляет текст с новой строки
    m_logEdit->append(message);
}

void MinimalSynchronizationView::setProgress(int percentage)
{
    // Ограничиваем значение в диапазоне 0-100
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    m_progressBar->setValue(percentage);
}

void MinimalSynchronizationView::setCloseButtonEnabled(bool enabled)
{
    m_closeButton->setEnabled(enabled);
}
