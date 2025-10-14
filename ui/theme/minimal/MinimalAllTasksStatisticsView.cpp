#include "MinimalAllTasksStatisticsView.h"

// Включаем все необходимые заголовки для реализации
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QGraphicsDropShadowEffect>

MinimalAllTasksStatisticsView::MinimalAllTasksStatisticsView(QWidget *parent)
    : IAllTasksStatisticsView(parent)
{
    // --- 1. Определение стилей ---

    // Стиль для всего окна
    this->setStyleSheet("background-color: #f4f7fa;");

    // Стиль для заголовка
    const QString titleStyle = R"(
        font-size: 24px;
        font-weight: bold;
        color: #333;
    )";

    // Стиль для таблицы
    const QString tableViewStyle = R"(
        QTableView {
            border: 1px solid #dcdcdc;
            border-radius: 10px;
            background-color: #ffffff;
            gridline-color: #e0e0e0;
            font-size: 14px;
        }
        QTableView::item {
            padding: 10px;
        }
        QHeaderView::section {
            background-color: #eef4ff;
            color: #333;
            padding: 8px;
            font-weight: bold;
            border: none;
            border-bottom: 1px solid #dcdcdc;
        }
    )";

    // Общий стиль для кнопок
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
    )";

    // --- 1. Создание виджетов ---
    m_titleLabel = new QLabel("Общее время по задачам", this);
    m_closeButton = new QPushButton("Закрыть", this);

    // Экран загрузки
    auto loadingWidget = new QWidget(this);
    auto loadingLayout = new QVBoxLayout(loadingWidget);
    auto loadingLabel = new QLabel("Загрузка данных...", loadingWidget);
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingWidget->setLayout(loadingLayout);

    // Таблица для статистики
    m_statsTableView = new QTableView(this);
    m_model = new QStandardItemModel(0, 2, this);
    // НОВЫЕ ЗАГОЛОВКИ
    m_model->setHorizontalHeaderLabels({"Задача", "Затраченное время"});
    m_statsTableView->setModel(m_model);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_statsTableView);
    m_stackedWidget->addWidget(loadingWidget);

    // --- 2. Применение стилей ---
    m_titleLabel->setStyleSheet(titleStyle);
    m_statsTableView->setStyleSheet(tableViewStyle);
    m_closeButton->setStyleSheet(buttonStyle);
    m_closeButton->setCursor(Qt::PointingHandCursor);

    // Настройка таблицы
    m_statsTableView->verticalHeader()->hide();
    m_statsTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_statsTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_statsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // --- 3. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_stackedWidget); // Добавляем виджет-переключатель
    mainLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

    setLayout(mainLayout);
    setWindowTitle("Общая статистика");
    setMinimumSize(450, 600);

    // --- 4. Соединение сигналов ---
    connect(m_closeButton, &QPushButton::clicked, this, &IAllTasksStatisticsView::closeRequested);
}

QWidget* MinimalAllTasksStatisticsView::getWidget() { return this; }

// НОВАЯ РЕАЛИЗАЦИЯ
void MinimalAllTasksStatisticsView::displayTaskSummaries(const QVector<TaskTimeSummary>& summaries)
{
    m_model->removeRows(0, m_model->rowCount());

    if (summaries.isEmpty()) {
        // Можно добавить сообщение, если нет данных
        auto titleItem = new QStandardItem("Нет данных для отображения");
        m_model->appendRow(titleItem);
        return;
    }

    for (const auto& summary : summaries) {
        auto titleItem = new QStandardItem(summary.title);
        auto timeItem = new QStandardItem(formatMinutes(summary.totalMinutes));
        timeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_model->appendRow({titleItem, timeItem});
    }
}

void MinimalAllTasksStatisticsView::showLoading(bool isLoading)
{
    if (isLoading) {
        m_stackedWidget->setCurrentIndex(1); // Показываем загрузку
    } else {
        m_stackedWidget->setCurrentIndex(0); // Показываем таблицу
    }
}

QString MinimalAllTasksStatisticsView::formatMinutes(qint64 totalMinutes)
{
    if (totalMinutes < 60) {
        return QString::number(totalMinutes) + " мин.";
    }
    qint64 hours = totalMinutes / 60;
    qint64 minutes = totalMinutes % 60;
    return QString("%1 ч %2 мин.").arg(hours).arg(minutes);
}
