#include "MinimalTimerView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>
#include <QInputDialog>

MinimalTimerView::MinimalTimerView(QWidget *parent)
    : ITimerView(parent)
{

    this->setStyleSheet(R"(
        /* Общий фон для окна */
        QWidget {
            background-color: #f4f7fa;
        }

        /* Стиль для всех кнопок QPushButton */
        QPushButton {
           background-color: #4a90e2;
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 10px;
           border: none;
           min-width: 80px;
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
    )");


    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    m_taskTitleLabel = new QLabel("Название задачи", this);
    m_taskTitleLabel->setAlignment(Qt::AlignCenter);
    m_taskTitleLabel->setStyleSheet("font-size: 18px; color: #555; font-weight: bold; margin-bottom: 10px;");


    m_mainStack = new QStackedWidget(this);
    m_mainStack->addWidget(createModeSelectionPage()); //  0
    m_mainStack->addWidget(createStopwatchPage());   //  1
    m_mainStack->addWidget(createPomodoroPage());      //  2

    mainLayout->addWidget(m_taskTitleLabel);
    mainLayout->addWidget(m_mainStack, 1);

    setLayout(mainLayout);
    setWindowTitle("Таймер");
    setMinimumSize(450, 600);
}




QWidget* MinimalTimerView::createModeSelectionPage()
{
    auto pageWidget = new QWidget(this);
    auto layout = new QVBoxLayout(pageWidget);
    layout->setSpacing(15);
    layout->setAlignment(Qt::AlignCenter);

    auto title = new QLabel("Выберите режим", pageWidget);
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");



    auto stopwatchButton = new QPushButton("⏱️ Секундомер", pageWidget);

    stopwatchButton->setMinimumHeight(40);
    connect(stopwatchButton, &QPushButton::clicked, this, &ITimerView::timerModeSelected);


    auto pomodoroButton = new QPushButton("🍅 Таймер Помодоро", pageWidget);

    pomodoroButton->setMinimumHeight(40);
    connect(pomodoroButton, &QPushButton::clicked, this, &MinimalTimerView::onPomodoroButtonClicked);


    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(stopwatchButton);
    layout->addWidget(pomodoroButton);
    layout->addStretch();

    pageWidget->setLayout(layout);
    return pageWidget;
}

QWidget* MinimalTimerView::createStopwatchPage()
{
    auto pageWidget = new QWidget(this);
    auto layout = new QVBoxLayout(pageWidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    m_stopwatchTimeLabel = new QLabel("00:00:00", pageWidget);
    m_stopwatchTimeLabel->setStyleSheet("font-size: 54px; font-weight: bold; color: #333;");

    auto stopButton = new QPushButton("Завершить", pageWidget);

    stopButton->setMinimumSize(120, 40);
    connect(stopButton, &QPushButton::clicked, this, &ITimerView::stopClicked);

    layout->addStretch();
    layout->addWidget(m_stopwatchTimeLabel, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(stopButton, 0, Qt::AlignHCenter);

    pageWidget->setLayout(layout);
    return pageWidget;
}

QWidget* MinimalTimerView::createPomodoroPage()
{
    auto pageWidget = new QWidget(this);
    auto layout = new QVBoxLayout(pageWidget);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);

    m_pomodoroStateLabel = new QLabel("УЧЁБА", pageWidget);
    m_pomodoroStateLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #e74c3c;");

    m_pomodoroTimeLabel = new QLabel("25:00", pageWidget);
    m_pomodoroTimeLabel->setStyleSheet("font-size: 60px; font-weight: bold; color: #333;");

    m_pomodoroSessionLabel = new QLabel("", pageWidget);
    m_pomodoroSessionLabel->setStyleSheet("font-size: 24px;");

    auto finishButton = new QPushButton("Завершить", pageWidget);

    finishButton->setMinimumSize(150, 40);
    connect(finishButton, &QPushButton::clicked, this, &ITimerView::stopClicked);

    layout->addStretch();
    layout->addWidget(m_pomodoroStateLabel, 0, Qt::AlignHCenter);
    layout->addWidget(m_pomodoroTimeLabel, 0, Qt::AlignHCenter);
    layout->addWidget(m_pomodoroSessionLabel, 0, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(finishButton, 0, Qt::AlignHCenter);

    pageWidget->setLayout(layout);
    return pageWidget;
}




QWidget* MinimalTimerView::getWidget() { return this; }

void MinimalTimerView::setTaskTitle(const QString& title)
{
    m_taskTitleLabel->setText(title);
}

void MinimalTimerView::updateDisplayedTime(const QString& timeString)
{
    // Обновляем время на активном экране
    if (m_mainStack->currentIndex() == 1) {
        m_stopwatchTimeLabel->setText(timeString);
    } else if (m_mainStack->currentIndex() == 2) {
        m_pomodoroTimeLabel->setText(timeString);
    }
}

void MinimalTimerView::showModeSelection()
{
    m_mainStack->setCurrentIndex(0);
}

void MinimalTimerView::displayPomodoroState(int remainingSessions, bool isWorkSession)
{
    m_mainStack->setCurrentIndex(2); // Переключаемся на экран Помодоро
    if (isWorkSession) {
        m_pomodoroStateLabel->setText("УЧЁБА");
        m_pomodoroStateLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #e74c3c;");
    } else {
        m_pomodoroStateLabel->setText("ОТДЫХ");
        m_pomodoroStateLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2ecc71;");
    }

    QString tomatoes;
    for (int i = 0; i < remainingSessions; ++i) {
        tomatoes += "🍅 ";
    }
    m_pomodoroSessionLabel->setText(tomatoes.trimmed());
}

void MinimalTimerView::onPomodoroButtonClicked()
{
    bool ok;
    int workMinutes = QInputDialog::getInt(this, "Время учёбы", "Минут на задачу:", 25, 1, 120, 1, &ok);
    if (!ok) { // Пользователь нажал "Отмена"
        return;
    }

    int restMinutes = QInputDialog::getInt(this, "Время отдыха", "Минут на отдых:", 5, 0, 60, 1, &ok);
    if (!ok) {
        return;
    }


    emit pomodoroModeSelected(workMinutes, restMinutes);
}

void MinimalTimerView::closeEvent(QCloseEvent *event)
{
    emit closeRequested();
    ITimerView::closeEvent(event);
}
void MinimalTimerView::showStopwatchMode()
{
    // Просто переключаем QStackedWidget на страницу с обычным таймером (индекс 1)
    m_mainStack->setCurrentIndex(1);
}
