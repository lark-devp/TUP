#include "MinimalTaskSelectionView.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>

MinimalTaskSelectionView::MinimalTaskSelectionView(QWidget *parent)
    : ITaskSelectionView(parent)
{
    this->setStyleSheet("background-color: #f4f7fa;");
    const QString titleStyle = "font-size: 24px; font-weight: bold; color: #333;";
    const QString listWidgetStyle = R"(
        QListWidget {
           border: 1px solid #dcdcdc;
           border-radius: 10px;
           padding: 5px;
           background-color: #ffffff;
           font-size: 14px;
        }
        QListWidget::item {
           padding: 12px;
           margin: 2px 0;
           border-radius: 5px;
        }
        QListWidget::item:hover {
           background-color: #eef4ff;
        }
        QListWidget::item:selected {
           background-color: #4a90e2;
           color: white;
           font-weight: bold;
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

    m_titleLabel = new QLabel("Выберите задачу", this);
    m_listWidget = new QListWidget(this);

    auto loadingWidget = new QWidget(this);
    auto loadingLayout = new QVBoxLayout(loadingWidget);
    auto loadingLabel = new QLabel("Загрузка...", loadingWidget);
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingWidget->setLayout(loadingLayout);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_listWidget);
    m_stackedWidget->addWidget(loadingWidget);

    m_startTimerButton = new QPushButton("▶️ Старт", this);
    m_statsButton = new QPushButton("📊 Статистика", this);
    m_allStatsButton = new QPushButton("Статистика (все)", this);
    m_addTaskButton = new QPushButton("➕ Добавить", this);
    m_syncButton = new QPushButton("🔄 Синхронизация", this);
    m_refreshButton = new QPushButton("Обновить календарь", this);

    m_titleLabel->setStyleSheet(titleStyle);
    m_listWidget->setStyleSheet(listWidgetStyle);

    const QList<QPushButton*> actionButtons = {
        m_startTimerButton, m_statsButton, m_allStatsButton,
        m_addTaskButton, m_syncButton, m_refreshButton
    };
    for (auto* button : actionButtons) {
        button->setStyleSheet(buttonStyle);
        button->setCursor(Qt::PointingHandCursor);
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }

    m_startTimerButton->setEnabled(false);
    m_statsButton->setEnabled(false);
    m_refreshButton->setEnabled(false);


    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    auto buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(15);
    buttonLayout->addWidget(m_startTimerButton, 0, 0);
    buttonLayout->addWidget(m_statsButton, 0, 1);
    buttonLayout->addWidget(m_addTaskButton, 1, 0);
    buttonLayout->addWidget(m_refreshButton, 1, 1);
    buttonLayout->addWidget(m_syncButton, 2, 0);
    buttonLayout->addWidget(m_allStatsButton, 2, 1);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_stackedWidget, 1);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Выбор задачи");
    setMinimumSize(450, 600);


    connect(m_listWidget, &QListWidget::currentItemChanged, this, &MinimalTaskSelectionView::onTaskSelectionChanged);
    connect(m_startTimerButton, &QPushButton::clicked, this, &MinimalTaskSelectionView::onStartTimerClicked);
    connect(m_statsButton, &QPushButton::clicked, this, &MinimalTaskSelectionView::onShowStatsClicked);
    connect(m_allStatsButton, &QPushButton::clicked, this, &ITaskSelectionView::allTasksStatisticsRequested);
    connect(m_addTaskButton, &QPushButton::clicked, this, &ITaskSelectionView::addTaskRequested);
    connect(m_syncButton, &QPushButton::clicked, this, &ITaskSelectionView::synchronizationRequested);
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &MinimalTaskSelectionView::onItemDoubleClicked);
    connect(m_refreshButton, &QPushButton::clicked, this, [this](){
        if (auto* item = m_listWidget->currentItem()) {
            emit syncSingleTaskRequested(item->data(Qt::UserRole).toString());
        }
    });
}



QWidget* MinimalTaskSelectionView::getWidget()
{
    return this;
}

void MinimalTaskSelectionView::displayTasks(const QVector<TaskDisplayData>& tasks)
{
    m_listWidget->clear();
    for (const auto& task : tasks) {
        auto item = new QListWidgetItem(task.title, m_listWidget);
        item->setData(Qt::UserRole, task.id);
    }
    m_listWidget->setCurrentItem(nullptr);
    onTaskSelectionChanged(nullptr, nullptr);
}

void MinimalTaskSelectionView::showLoading(bool isLoading)
{
    if (isLoading) {
        m_stackedWidget->setCurrentIndex(1);
    } else {
        m_stackedWidget->setCurrentIndex(0);
    }
}

void MinimalTaskSelectionView::showError(const QString& message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MinimalTaskSelectionView::onTaskSelectionChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous);
    bool isTaskSelected = (current != nullptr);
    m_startTimerButton->setEnabled(isTaskSelected);
    m_statsButton->setEnabled(isTaskSelected);
    m_refreshButton->setEnabled(isTaskSelected);
}

void MinimalTaskSelectionView::onStartTimerClicked()
{
    if (auto currentItem = m_listWidget->currentItem()) {
        QString taskId = currentItem->data(Qt::UserRole).toString();
        emit taskSelectedForTimer(taskId);
    }
}

void MinimalTaskSelectionView::onShowStatsClicked()
{
    if (auto currentItem = m_listWidget->currentItem()) {
        QString taskId = currentItem->data(Qt::UserRole).toString();
        emit statisticsRequestedForTask(taskId);
    }
}
void MinimalTaskSelectionView::setupConnections()
{
    connect(m_startTimerButton, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = m_listWidget->currentItem();

        if (selectedItem) {
            QString taskId = selectedItem->data(Qt::UserRole).toString();

            emit taskSelectedForTimer(taskId);
        } else {
            showError("Пожалуйста, выберите задачу из списка.");
        }
    });

    connect(m_statsButton, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = m_listWidget->currentItem();
        if (selectedItem) {
            QString taskId = selectedItem->data(Qt::UserRole).toString();
            emit statisticsRequestedForTask(taskId);
        } else {
            showError("Пожалуйста, выберите задачу из списка.");
        }
    });
    connect(m_allStatsButton, &QPushButton::clicked,
            this, &MinimalTaskSelectionView::allTasksStatisticsRequested);

    connect(m_syncButton, &QPushButton::clicked,
            this, &MinimalTaskSelectionView::synchronizationRequested);

    connect(m_addTaskButton, &QPushButton::clicked,
            this, &MinimalTaskSelectionView::addTaskRequested);
}
void MinimalTaskSelectionView::onItemDoubleClicked(QListWidgetItem* item)
{
    if (item) {
        QString taskId = item->data(Qt::UserRole).toString();
        emit editTaskRequested(taskId);
    }
}
void MinimalTaskSelectionView::onRefreshClicked()
{
    if (auto currentItem = m_listWidget->currentItem()) {
        QString taskId = currentItem->data(Qt::UserRole).toString();
        emit syncSingleTaskRequested(taskId);
    }
}
