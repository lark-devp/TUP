#include "MinimalSingleTaskStatisticsView.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>

MinimalSingleTaskStatisticsView::MinimalSingleTaskStatisticsView(QWidget *parent)
    : ISingleTaskStatisticsView(parent)
{
    this->setStyleSheet("background-color: #f4f7fa; color: #333;");

    const QString titleStyle = "font-size: 20px; font-weight: bold; color: #2c3e50;";
    const QString weekRangeStyle = "font-size: 16px; font-weight: bold; color: #333;";
    const QString navButtonStyle = R"(
        QPushButton {
            background-color: #ffffff;
            border: 1px solid #dcdcdc;
            color: #333;
            font-weight: bold;
            border-radius: 15px;
        }
        QPushButton:hover { background-color: #eef4ff; }
        QPushButton:pressed { background-color: #dce8fa; }
    )";
    const QString closeButtonStyle = R"(
        QPushButton {
           background-color: #4a90e2; color: white; border-radius: 8px;
           font-size: 14px; font-weight: bold; padding: 10px 15px; border: none;
        }
        QPushButton:hover { background-color: #5aa1f2; }
        QPushButton:pressed { background-color: #3a80d2; }
    )";
    const QString chartContainerStyle = "background-color: #ffffff; border-radius: 10px;";

    m_taskTitleLabel = new QLabel("Статистика по задаче", this);
    m_taskTitleLabel->setStyleSheet(titleStyle);
    m_taskTitleLabel->setAlignment(Qt::AlignCenter);

    m_prevWeekButton = new QPushButton("<", this);
    m_prevWeekButton->setStyleSheet(navButtonStyle);
    m_prevWeekButton->setFixedSize(30, 30);
    m_prevWeekButton->setCursor(Qt::PointingHandCursor);

    m_nextWeekButton = new QPushButton(">", this);
    m_nextWeekButton->setStyleSheet(navButtonStyle);
    m_nextWeekButton->setFixedSize(30, 30);
    m_nextWeekButton->setCursor(Qt::PointingHandCursor);

    m_closeButton = new QPushButton("Закрыть", this);
    m_closeButton->setStyleSheet(closeButtonStyle);
    m_closeButton->setCursor(Qt::PointingHandCursor);

    m_weekRangeLabel = new QLabel("Текущая неделя", this);
    m_weekRangeLabel->setAlignment(Qt::AlignCenter);
    m_weekRangeLabel->setStyleSheet(weekRangeStyle);

    auto chartContainer = new QWidget(this);
    chartContainer->setStyleSheet(chartContainerStyle);

    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 70));
    chartContainer->setGraphicsEffect(shadow);

    m_loadingLabel = new QLabel("Загрузка данных...", this);
    m_loadingLabel->setAlignment(Qt::AlignCenter);
    m_loadingLabel->setStyleSheet("font-size: 16px; color: #888;");

    m_chartView = new BarChartView(this);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_chartView);
    m_stackedWidget->addWidget(m_loadingLabel);

    auto containerLayout = new QVBoxLayout(chartContainer);
    containerLayout->addWidget(m_stackedWidget);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    auto navigationLayout = new QHBoxLayout();
    navigationLayout->addWidget(m_prevWeekButton);
    navigationLayout->addStretch();
    navigationLayout->addWidget(m_weekRangeLabel);
    navigationLayout->addStretch();
    navigationLayout->addWidget(m_nextWeekButton);

    mainLayout->addWidget(m_taskTitleLabel);
    mainLayout->addLayout(navigationLayout);
    mainLayout->addWidget(chartContainer, 1);
    mainLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

    setLayout(mainLayout);
    setWindowTitle("Статистика по задаче");
    setMinimumSize(450, 600);

    connect(m_prevWeekButton, &QPushButton::clicked, this, &MinimalSingleTaskStatisticsView::onPrevWeekClicked);
    connect(m_nextWeekButton, &QPushButton::clicked, this, &MinimalSingleTaskStatisticsView::onNextWeekClicked);
    connect(m_closeButton, &QPushButton::clicked, this, &ISingleTaskStatisticsView::closeRequested);

    QDate today = QDate::currentDate();
    m_currentWeekStart = today.addDays(-(today.dayOfWeek() - 1));
}

QWidget* MinimalSingleTaskStatisticsView::getWidget() { return this; }

void MinimalSingleTaskStatisticsView::setTaskTitle(const QString& title)
{
    m_taskTitleLabel->setText(title);
}

void MinimalSingleTaskStatisticsView::displayWeeklyChart(const QVector<qint64>& weeklyData, const QString& weekRangeLabel)
{
    m_weekRangeLabel->setText(weekRangeLabel);
    m_chartView->setData(weeklyData);
}

void MinimalSingleTaskStatisticsView::showLoading(bool isLoading)
{
    m_stackedWidget->setCurrentIndex(isLoading ? 1 : 0);
}

void MinimalSingleTaskStatisticsView::onPrevWeekClicked()
{
    m_currentWeekStart = m_currentWeekStart.addDays(-7);
    emit weekChanged(m_currentWeekStart);
}

void MinimalSingleTaskStatisticsView::onNextWeekClicked()
{
    m_currentWeekStart = m_currentWeekStart.addDays(7);
    emit weekChanged(m_currentWeekStart);
}
