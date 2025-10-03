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

    // Стиль для виджетов выбора даты
    const QString dateEditStyle = R"(
        QDateEdit {
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 8px;
            background-color: #ffffff;
            font-size: 14px;
        }
        QDateEdit::up-button, QDateEdit::down-button {
            width: 20px;
        }
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


    // --- 2. Создание виджетов ---
    m_titleLabel = new QLabel("Общая статистика", this);

    m_fromDateEdit = new QDateEdit(this);
    m_fromDateEdit->setDate(QDate::currentDate().addMonths(-1)); // По умолчанию - месяц назад
    m_fromDateEdit->setCalendarPopup(true);

    m_toDateEdit = new QDateEdit(this);
    m_toDateEdit->setDate(QDate::currentDate()); // По умолчанию - сегодня
    m_toDateEdit->setCalendarPopup(true);

    m_applyButton = new QPushButton("Применить", this);
    m_closeButton = new QPushButton("Закрыть", this);

    // Виджет-заглушка для экрана загрузки
    auto loadingWidget = new QWidget(this);
    auto loadingLayout = new QVBoxLayout(loadingWidget);
    auto loadingLabel = new QLabel("Загрузка данных...", loadingWidget);
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingWidget->setLayout(loadingLayout);

    // Таблица для статистики
    m_statsTableView = new QTableView(this);
    m_model = new QStandardItemModel(0, 2, this); // 0 строк, 2 колонки
    m_model->setHorizontalHeaderLabels({"Параметр", "Значение"});
    m_statsTableView->setModel(m_model);

    m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_statsTableView);
    m_stackedWidget->addWidget(loadingWidget);


    // --- 3. Применение стилей и эффектов ---
    m_titleLabel->setStyleSheet(titleStyle);
    m_fromDateEdit->setStyleSheet(dateEditStyle);
    m_toDateEdit->setStyleSheet(dateEditStyle);
    m_statsTableView->setStyleSheet(tableViewStyle);
    m_applyButton->setStyleSheet(buttonStyle);
    m_closeButton->setStyleSheet(buttonStyle);

    // Настройка внешнего вида таблицы
    m_statsTableView->verticalHeader()->hide();
    m_statsTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_statsTableView->horizontalHeader()->setStretchLastSection(true);
    m_statsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования
    m_statsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_statsTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Добавляем тень и курсор к кнопкам
    for (auto* button : {m_applyButton, m_closeButton}) {
        button->setCursor(Qt::PointingHandCursor);
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }


    // --- 4. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Горизонтальный layout для фильтра дат
    auto dateFilterLayout = new QHBoxLayout();
    dateFilterLayout->setSpacing(10);
    dateFilterLayout->addWidget(new QLabel("С:", this));
    dateFilterLayout->addWidget(m_fromDateEdit);
    dateFilterLayout->addSpacing(15);
    dateFilterLayout->addWidget(new QLabel("По:", this));
    dateFilterLayout->addWidget(m_toDateEdit);
    dateFilterLayout->addStretch(); // Растягиваем, чтобы кнопка была справа
    dateFilterLayout->addWidget(m_applyButton);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addLayout(dateFilterLayout);
    mainLayout->addWidget(m_stackedWidget);
    mainLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

    setLayout(mainLayout);
    setWindowTitle("Общая статистика");
    setMinimumSize(500, 450);


    // --- 5. Соединение сигналов и слотов ---
    connect(m_applyButton, &QPushButton::clicked, this, &MinimalAllTasksStatisticsView::onApplyDateRangeClicked);
    // Нажатие на кнопку "Закрыть" напрямую генерирует сигнал интерфейса
    connect(m_closeButton, &QPushButton::clicked, this, &IAllTasksStatisticsView::closeRequested);
}

QWidget* MinimalAllTasksStatisticsView::getWidget()
{
    return this;
}

void MinimalAllTasksStatisticsView::displayOverallStatistics(const QVariantMap& statsData)
{
    // Очищаем модель перед заполнением новыми данными
    m_model->removeRows(0, m_model->rowCount());

    // Итерируемся по карте и добавляем строки в таблицу
    for (auto it = statsData.constBegin(); it != statsData.constEnd(); ++it) {
        auto keyItem = new QStandardItem(it.key());
        auto valueItem = new QStandardItem(it.value().toString());

        // Для красивого выравнивания
        valueItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        m_model->appendRow({keyItem, valueItem});
    }
}

void MinimalAllTasksStatisticsView::showLoading(bool isLoading)
{
    if (isLoading) {
        m_stackedWidget->setCurrentIndex(1); // Показываем виджет загрузки
    } else {
        m_stackedWidget->setCurrentIndex(0); // Показываем таблицу
    }
}

void MinimalAllTasksStatisticsView::onApplyDateRangeClicked()
{
    const QDate from = m_fromDateEdit->date();
    const QDate to = m_toDateEdit->date();

    // Генерируем сигнал интерфейса, чтобы сообщить презентеру/контроллеру
    // о том, что пользователь запросил обновление данных.
    emit dateRangeChanged(from, to);
}
