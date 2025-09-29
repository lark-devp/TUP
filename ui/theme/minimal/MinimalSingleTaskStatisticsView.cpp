#include "MinimalSingleTaskStatisticsView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QCloseEvent>
#include <QGraphicsDropShadowEffect>

MinimalSingleTaskStatisticsView::MinimalSingleTaskStatisticsView(QWidget *parent)
    : ISingleTaskStatisticsView(parent)
{
    // --- 1. Определение стилей ---
    this->setStyleSheet("background-color: #f4f7fa; color: #333;");

    const QString titleStyle = R"(
        font-size: 18px;
        font-weight: bold;
        color: #2c3e50;
        margin-bottom: 10px;
    )";

    const QString dateEditStyle = R"(
        QDateEdit {
            border: 1px solid #bdc3c7;
            border-radius: 4px;
            padding: 5px;
            background-color: white;
            font-size: 14px;
        }
        QDateEdit::up-button, QDateEdit::down-button {
            width: 20px;
        }
    )";

    const QString tableViewStyle = R"(
        QTableView {
            border: 1px solid #e0e0e0;
            border-radius: 4px;
            font-size: 14px;
            gridline-color: #e0e0e0;
        }
        QHeaderView::section {
            background-color: #ecf0f1;
            padding: 8px;
            border: none;
            border-bottom: 1px solid #dcdcdc;
            font-weight: bold;
        }
    )";

    // --- 2. Создание виджетов ---
    m_taskTitleLabel = new QLabel("Статистика по задаче", this);
    m_loadingLabel = new QLabel("Загрузка данных...", this);

    // Виджеты для выбора диапазона дат
    m_fromDateEdit = new QDateEdit(QDate::currentDate().addMonths(-1), this);
    m_toDateEdit = new QDateEdit(QDate::currentDate(), this);
    m_fromDateEdit->setCalendarPopup(true);
    m_toDateEdit->setCalendarPopup(true);

    // Таблица для отображения статистики
    m_statisticsView = new QTableView(this);
    m_statisticsModel = new QStandardItemModel(0, 2, this); // 0 строк, 2 колонки
    m_statisticsModel->setHorizontalHeaderLabels({"Параметр", "Значение"});
    m_statisticsView->setModel(m_statisticsModel);


    // --- 3. Применение стилей и эффектов ---
    m_taskTitleLabel->setStyleSheet(titleStyle);
    m_taskTitleLabel->setAlignment(Qt::AlignCenter);

    m_loadingLabel->setAlignment(Qt::AlignCenter);
    m_loadingLabel->setStyleSheet("font-size: 16px; color: #7f8c8d;");

    m_fromDateEdit->setStyleSheet(dateEditStyle);
    m_toDateEdit->setStyleSheet(dateEditStyle);

    m_statisticsView->setStyleSheet(tableViewStyle);
    m_statisticsView->verticalHeader()->setVisible(false);
    m_statisticsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_statisticsView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования

    // Добавим тень для таблицы
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 2);
    shadow->setColor(QColor(0, 0, 0, 70));
    m_statisticsView->setGraphicsEffect(shadow);


    // --- 4. Компоновка ---
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(15);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);

    // Компоновка для выбора дат
    auto dateLayout = new QHBoxLayout();
    dateLayout->addWidget(new QLabel("С:", this));
    dateLayout->addWidget(m_fromDateEdit);
    dateLayout->addSpacing(20);
    dateLayout->addWidget(new QLabel("По:", this));
    dateLayout->addWidget(m_toDateEdit);
    dateLayout->addStretch();

    m_mainLayout->addWidget(m_taskTitleLabel);
    m_mainLayout->addLayout(dateLayout);
    m_mainLayout->addWidget(m_loadingLabel); // Добавляем виджет загрузки
    m_mainLayout->addWidget(m_statisticsView);

    // Изначально виджеты статистики и загрузки скрыты
    m_statisticsView->hide();
    m_loadingLabel->hide();

    setLayout(m_mainLayout);
    setWindowTitle("Статистика");
    setMinimumSize(400, 500);


    // --- 5. Соединение сигналов ---
    connect(m_fromDateEdit, &QDateEdit::dateChanged, this, &MinimalSingleTaskStatisticsView::onDateWidgetsChanged);
    connect(m_toDateEdit, &QDateEdit::dateChanged, this, &MinimalSingleTaskStatisticsView::onDateWidgetsChanged);

    // Отправляем сигнал с начальными датами при создании
    onDateWidgetsChanged();
}

// --- Реализация методов интерфейсов ---

QWidget* MinimalSingleTaskStatisticsView::getWidget()
{
    return this;
}

void MinimalSingleTaskStatisticsView::setTaskTitle(const QString& title)
{
    m_taskTitleLabel->setText(title);
}

void MinimalSingleTaskStatisticsView::displayStatistics(const QVariantMap& statsData)
{
    m_statisticsModel->removeRows(0, m_statisticsModel->rowCount()); // Очищаем старые данные

    for (auto it = statsData.constBegin(); it != statsData.constEnd(); ++it) {
        QList<QStandardItem*> newRow;
        newRow.append(new QStandardItem(it.key()));
        newRow.append(new QStandardItem(it.value().toString()));
        m_statisticsModel->appendRow(newRow);
    }
}

void MinimalSingleTaskStatisticsView::showLoading(bool isLoading)
{
    if (isLoading) {
        m_statisticsView->hide();
        m_loadingLabel->show();
    } else {
        m_loadingLabel->hide();
        m_statisticsView->show();
    }
}

// --- Реализация переопределенных методов ---

void MinimalSingleTaskStatisticsView::closeEvent(QCloseEvent *event)
{
    emit closeRequested();
    ISingleTaskStatisticsView::closeEvent(event);
}

// --- Реализация приватных слотов ---

void MinimalSingleTaskStatisticsView::onDateWidgetsChanged()
{
    // Отправляем сигнал наружу с текущими датами из виджетов
    emit dateRangeChanged(m_fromDateEdit->date(), m_toDateEdit->date());
}
