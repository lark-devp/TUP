#include "MinimalTaskSelectionView.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>
#include <QFont>
#include <QGraphicsDropShadowEffect> // Необходимо для тени

MinimalTaskSelectionView::MinimalTaskSelectionView(QWidget *parent)
    : ITaskSelectionView(parent)
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

    // Стиль для списка задач
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
        QPushButton:disabled {
           background-color: #dcdcdc;
           color: #a0a0a0;
        }
    )";


    // --- 2. Создание виджетов ---
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

    // Кнопки
    m_startTimerButton = new QPushButton("▶️ Старт", this);
    m_statsButton = new QPushButton("📊 Статистика", this);
    m_allStatsButton = new QPushButton("Статистика (все)", this);
    m_addTaskButton = new QPushButton("➕ Добавить", this);
    m_syncButton = new QPushButton("🔄 Синхронизация", this);
    m_refreshButton = new QPushButton("Обновить календарь", this);


    // --- 3. Применение стилей и эффектов ---
    m_titleLabel->setStyleSheet(titleStyle);
    m_listWidget->setStyleSheet(listWidgetStyle);

    // Применяем общий стиль ко всем кнопкам
    for (auto* button : findChildren<QPushButton*>()) {
        button->setStyleSheet(buttonStyle);
        button->setCursor(Qt::PointingHandCursor); // Меняем курсор при наведении

        // Добавляем тень к каждой кнопке
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 3);
        shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }

    // Изначально кнопки, требующие выбора задачи, неактивны
    m_startTimerButton->setEnabled(false);
    m_statsButton->setEnabled(false);


    // --- 4. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(15);

    buttonLayout->addWidget(m_startTimerButton, 0, 0);
    buttonLayout->addWidget(m_statsButton, 0, 1);
    buttonLayout->addWidget(m_addTaskButton, 1, 0);
    buttonLayout->addWidget(m_refreshButton, 1, 1);
    buttonLayout->addWidget(m_syncButton, 2, 0);
    buttonLayout->addWidget(m_allStatsButton, 2, 1);

    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_stackedWidget);
    mainLayout->addSpacing(10); // Небольшой отступ перед кнопками
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Выбор задачи");
    setMinimumSize(450, 600);


    // --- 5. Соединение сигналов и слотов (без изменений) ---
    connect(m_listWidget, &QListWidget::currentItemChanged, this, &MinimalTaskSelectionView::onTaskSelectionChanged);
    connect(m_startTimerButton, &QPushButton::clicked, this, &MinimalTaskSelectionView::onStartTimerClicked);
    connect(m_statsButton, &QPushButton::clicked, this, &MinimalTaskSelectionView::onShowStatsClicked);
    connect(m_allStatsButton, &QPushButton::clicked, this, &ITaskSelectionView::allTasksStatisticsRequested);
    connect(m_addTaskButton, &QPushButton::clicked, this, &ITaskSelectionView::addTaskRequested);
    connect(m_syncButton, &QPushButton::clicked, this, &ITaskSelectionView::synchronizationRequested);
    connect(m_refreshButton, &QPushButton::clicked, this, &ITaskSelectionView::refreshRequested);
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &MinimalTaskSelectionView::onItemDoubleClicked);
}

// --- Реализация методов интерфейсов и слотов (остается без изменений) ---

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
    // Сбрасываем выбор, чтобы кнопки снова стали неактивными
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
    // Предположим, у вас есть кнопка m_startButton и список m_taskListWidget
    connect(m_startTimerButton, &QPushButton::clicked, this, [this](){
        // 1. Получаем выбранный элемент из списка
        QListWidgetItem* selectedItem = m_listWidget->currentItem();

        if (selectedItem) {
            // 2. Извлекаем ID задачи (мы его сохраняли ранее через setData)
            QString taskId = selectedItem->data(Qt::UserRole).toString();

            // 3. ИСПУСКАЕМ СИГНАЛ ИНТЕРФЕЙСА
            // Окно не знает, кто его слушает. Оно просто кричит: "Выбрана задача для таймера!"
            emit taskSelectedForTimer(taskId);
        } else {
            // Показать сообщение, что нужно выбрать задачу
            showError("Пожалуйста, выберите задачу из списка.");
        }
    });

    connect(m_statsButton, &QPushButton::clicked, this, [this](){
        QListWidgetItem* selectedItem = m_listWidget->currentItem();
        if (selectedItem) {
            QString taskId = selectedItem->data(Qt::UserRole).toString();
            // ИСПУСКАЕМ НОВЫЙ СИГНАЛ
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
        // Отправляем сигнал "наружу", что пользователь хочет редактировать задачу
        emit editTaskRequested(taskId);
    }
}
