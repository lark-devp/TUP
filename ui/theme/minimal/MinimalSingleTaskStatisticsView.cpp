#include "MinimalSingleTaskStatisticsView.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QHeaderView>
#include <QCloseEvent>
#include <QGraphicsDropShadowEffect>

MinimalSingleTaskStatisticsView::MinimalSingleTaskStatisticsView(QWidget *parent)
    : ISingleTaskStatisticsView(parent)
{
    // --- 1. Определение стилей ---
    this->setStyleSheet("background-color: #f4f7fa; color: #333;");
    const QString titleStyle = "font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;";



    // --- 1. Создание виджетов ---
    m_taskTitleLabel = new QLabel("Статистика по задаче", this);
    m_loadingLabel = new QLabel("Загрузка данных...", this);

    // --- Новые виджеты для навигации по неделям ---
    m_prevWeekButton = new QPushButton("<", this);
    m_nextWeekButton = new QPushButton(">", this);
    m_weekRangeLabel = new QLabel("Текущая неделя", this);
    m_weekRangeLabel->setAlignment(Qt::AlignCenter);
    m_weekRangeLabel->setStyleSheet("font-weight: bold;");

    // --- Наш кастомный виджет диаграммы ---
    m_chartView = new BarChartView(this);




    // --- 3. Компоновка ---
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(15);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);

    // Компоновка для навигации
    auto navigationLayout = new QHBoxLayout();
    navigationLayout->addWidget(m_prevWeekButton);
    navigationLayout->addWidget(m_weekRangeLabel, 1); // Растягиваем метку
    navigationLayout->addWidget(m_nextWeekButton);

    m_mainLayout->addWidget(m_taskTitleLabel);
    m_mainLayout->addLayout(navigationLayout); // Добавляем навигацию
    m_mainLayout->addWidget(m_loadingLabel);
    m_mainLayout->addWidget(m_chartView); // Добавляем диаграмму


    m_chartView->hide();

    m_loadingLabel->show();

    setLayout(m_mainLayout);
    setWindowTitle("Статистика по задаче");
    setMinimumSize(500, 450);

    // --- 4. Соединение сигналов ---
    connect(m_prevWeekButton, &QPushButton::clicked, this, &MinimalSingleTaskStatisticsView::onPrevWeekClicked);
    connect(m_nextWeekButton, &QPushButton::clicked, this, &MinimalSingleTaskStatisticsView::onNextWeekClicked);

    // --- 5. Инициализация даты ---
    // Устанавливаем текущую дату на начало недели (понедельник)
    QDate today = QDate::currentDate();
    m_currentWeekStart = today.addDays(-(today.dayOfWeek() - 1));

}

// --- Реализация методов ---
QWidget* MinimalSingleTaskStatisticsView::getWidget() { return this; }
void MinimalSingleTaskStatisticsView::setTaskTitle(const QString& title) { m_taskTitleLabel->setText(title); }

void MinimalSingleTaskStatisticsView::displayWeeklyChart(const QVector<qint64>& weeklyData, const QString& weekRangeLabel)
{
    m_chartView->setData(weeklyData);
    m_weekRangeLabel->setText(weekRangeLabel);
}


void MinimalSingleTaskStatisticsView::showLoading(bool isLoading)
{
    if (isLoading) {
        m_chartView->hide();

        m_loadingLabel->show();
    } else {
        m_loadingLabel->hide();
        m_chartView->show();

    }
}

void MinimalSingleTaskStatisticsView::closeEvent(QCloseEvent *event)
{
    emit closeRequested();
    ISingleTaskStatisticsView::closeEvent(event);
}

// --- Реализация слотов навигации ---
void MinimalSingleTaskStatisticsView::onPrevWeekClicked()
{
    m_currentWeekStart = m_currentWeekStart.addDays(-7);
    emit weekChanged(m_currentWeekStart); // Отправляем сигнал с новой датой
}

void MinimalSingleTaskStatisticsView::onNextWeekClicked()
{
    m_currentWeekStart = m_currentWeekStart.addDays(7);
    emit weekChanged(m_currentWeekStart); // Отправляем сигнал с новой датой
}

