#include "MinimalTimerView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QFont>
#include <QGraphicsDropShadowEffect>

MinimalTimerView::MinimalTimerView(QWidget *parent)
    : ITimerView(parent)
{
    // --- 1. Определение стилей (в духе вашего примера) ---

    this->setStyleSheet("background-color: #f4f7fa;");

    const QString titleStyle = R"(
        font-size: 16px;
        color: #555;
        font-weight: bold;
    )";

    const QString timeDisplayStyle = R"(
        font-size: 48px;
        font-weight: bold;
        color: #333;
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
           min-width: 80px; /* Минимальная ширина для кнопок */
        }
        QPushButton:hover {
           background-color: #5aa1f2;
        }
        QPushButton:pressed {
           background-color: #3a80d2;
        }
        QPushButton:disabled {
           background-color: #dcdcdc;
           color: #a0a0a0;
        }
    )";


    // --- 2. Создание виджетов ---
    m_taskTitleLabel = new QLabel("Название задачи", this);
    m_timeDisplayLabel = new QLabel("00:00:00", this);

    m_pauseButton = new QPushButton("⏸️ Пауза", this);
    m_stopButton = new QPushButton("⏹️ Стоп", this);


    // --- 3. Применение стилей и эффектов ---
    m_taskTitleLabel->setStyleSheet(titleStyle);
    m_taskTitleLabel->setAlignment(Qt::AlignCenter);

    m_timeDisplayLabel->setStyleSheet(timeDisplayStyle);
    m_timeDisplayLabel->setAlignment(Qt::AlignCenter);

    // Применяем общий стиль и эффекты ко всем кнопкам
    for (auto* button : {m_pauseButton, m_stopButton}) {
        button->setStyleSheet(buttonStyle);
        button->setCursor(Qt::PointingHandCursor);

        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }


    // --- 4. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    buttonLayout->addWidget(m_pauseButton);
    buttonLayout->addWidget(m_stopButton);

    mainLayout->addWidget(m_taskTitleLabel);
    mainLayout->addWidget(m_timeDisplayLabel, 1); // Даем дисплею времени растягиваться
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Таймер");
    setMinimumSize(450, 600);


    // --- 5. Соединение сигналов ---
    connect(m_pauseButton, &QPushButton::clicked, this, &ITimerView::pauseClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &ITimerView::stopClicked);
}

// --- Реализация методов интерфейсов ---

QWidget* MinimalTimerView::getWidget()
{
    // Так как этот класс и есть виджет, возвращаем себя
    return this;
}

void MinimalTimerView::setTaskTitle(const QString& title)
{
    m_taskTitleLabel->setText(title);
}

void MinimalTimerView::updateDisplayedTime(const QString& timeString)
{
    m_timeDisplayLabel->setText(timeString);
}

void MinimalTimerView::setTimerControlsEnabled(bool canPause, bool canStop)
{
    m_pauseButton->setEnabled(canPause);
    m_stopButton->setEnabled(canStop);
}

void MinimalTimerView::closeEvent(QCloseEvent *event)
{
    // Сообщаем "наружу", что пользователь хочет закрыть окно
    emit closeRequested();
    // Вызываем реализацию базового класса, чтобы окно действительно закрылось
    ITimerView::closeEvent(event);
}
