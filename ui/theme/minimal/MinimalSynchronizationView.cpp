#include "MinimalSynchronizationView.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QEvent>

MinimalSynchronizationView::MinimalSynchronizationView(QWidget *parent)
    : ISynchronizationView(parent)
{
    // --- 1. Определение стилей ---

    this->setStyleSheet("background-color: #f4f7fa;"); // Общий фон

    const QString titleStyle = R"(
        QLabel {
            font-size: 20px;
            font-weight: bold;
            color: #333;
            margin-bottom: 15px;
            qproperty-alignment: 'AlignCenter';
        }
    )";

    const QString labelStyle = R"(
        QLabel {
            font-size: 14px;
            font-weight: bold;
            color: #333;
            margin-bottom: 5px;
        }
    )";

    const QString statusStyle = R"(
        font-size: 14px;
        color: #555;
        margin-bottom: 15px;
    )";

    const QString inputStyle = R"(
        QLineEdit, QComboBox {
            background-color: #ffffff;
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox::down-arrow {
            image: url(:/icons/down-arrow.png); /* Пример: нужна иконка в ресурсах */
        }
    )";

    const QString listStyle = R"(
        QListWidget {
            background-color: #ffffff;
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            font-size: 14px;
        }
        QListWidget::item {
            padding: 8px;
        }
        QListWidget::item:selected {
            background-color: #4a90e2;
            color: white;
        }
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
            height: 24px;
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


    // --- 2. Создание ОБЩИХ виджетов и применение стилей ---
    m_mainLayout = new QVBoxLayout(this);
    m_statusLabel = new QLabel("Готово.", this);
    m_statusLabel->setStyleSheet(statusStyle);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setStyleSheet(progressBarStyle);

    m_logView = new QTextEdit(this);
    m_logView->setReadOnly(true);
    m_logView->setStyleSheet(logStyle);

    m_closeButton = new QPushButton("Закрыть", this);
    m_closeButton->setStyleSheet(buttonStyle);




    // --- 3. Создание виджетов для каждого состояния ---
    setupLoginUi();
    setupSyncUi();

    // Применение стилей к элементам, созданным в setup-методах
    m_emailEdit->setStyleSheet(inputStyle);
    m_passwordEdit->setStyleSheet(inputStyle);
    m_connectButton->setStyleSheet(buttonStyle);
    m_calendarCombo->setStyleSheet(inputStyle);
    m_getTasksButton->setStyleSheet(buttonStyle);
    m_tasksList->setStyleSheet(listStyle);
    m_confirmButton->setStyleSheet(buttonStyle);


    // --- 4. Компоновка ---
    m_mainLayout->addWidget(m_loginWidget);
    m_mainLayout->addWidget(m_syncWidget);
    m_mainLayout->addSpacing(15);
    m_mainLayout->addWidget(m_statusLabel);
    m_mainLayout->addWidget(m_progressBar);
    m_mainLayout->addWidget(m_logView);
    m_mainLayout->addWidget(m_closeButton, 0, Qt::AlignRight);

    setLayout(m_mainLayout);
    setMinimumSize(450, 500);

    // --- 5. Соединение сигналов ---
    connect(m_closeButton, &QPushButton::clicked, this, &ISynchronizationView::closeRequested);

    // По умолчанию показываем экран входа
    showState(ViewState::Login);
}

void MinimalSynchronizationView::setupLoginUi() {
    m_loginWidget = new QWidget(this);
    auto layout = new QVBoxLayout(m_loginWidget);
    auto formLayout = new QFormLayout();
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);


    auto titleLabel = new QLabel("Введите данные от Tweek", this);
    titleLabel->setStyleSheet(R"(
        font-size: 20px;
        font-weight: bold;
        color: #333;
        margin-bottom: 15px;
    )");


    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setPlaceholderText("your@example.com");
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_connectButton = new QPushButton("Подключить", this);

    formLayout->addRow("Email:", m_emailEdit);
    formLayout->addRow("Пароль:", m_passwordEdit);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addLayout(formLayout);
    layout->addWidget(m_connectButton);

    connect(m_connectButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onConnectClicked);
}

void MinimalSynchronizationView::setupSyncUi() {
    m_syncWidget = new QWidget(this);
    auto layout = new QVBoxLayout(m_syncWidget);

    const QString labelStyle = R"(
        font-size: 14px;
        font-weight: bold;
        color: #333;
        margin-bottom: 5px;
    )";

    auto calendarLabel = new QLabel("Выберите календарь:", this);
    calendarLabel->setStyleSheet(labelStyle);

    m_calendarCombo = new QComboBox(this);
    m_calendarCombo->installEventFilter(this);

    m_getTasksButton = new QPushButton("Получить задачи на сегодня", this);
    m_tasksList = new QListWidget(this);
    m_tasksList->setSelectionMode(QAbstractItemView::MultiSelection);
    m_confirmButton = new QPushButton("Добавить выбранные задачи", this);

    auto tasksLabel = new QLabel("Задачи на сегодня:", this);
    tasksLabel->setStyleSheet(labelStyle);


    layout->addWidget(calendarLabel);
    layout->addWidget(m_calendarCombo);
    layout->addWidget(m_getTasksButton);
    layout->addWidget(tasksLabel);
    layout->addWidget(m_tasksList);
    layout->addWidget(m_confirmButton);

    connect(m_getTasksButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onGetTasksClicked);
    connect(m_confirmButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onConfirmClicked);
}

// ... (остальной код остается без изменений) ...

void MinimalSynchronizationView::showState(ViewState state) {
    if (state == ViewState::Login) {
        m_loginWidget->show();
        m_syncWidget->hide();
        updateStatus("Требуется вход в Tweek.");
    } else {
        m_loginWidget->hide();
        m_syncWidget->show();
        updateStatus("Подключено к Tweek. Ожидание данных..."); // Изменим статус

    }
}

QWidget* MinimalSynchronizationView::getWidget() { return this; }
void MinimalSynchronizationView::updateStatus(const QString& status) { m_statusLabel->setText(status); }
void MinimalSynchronizationView::logMessage(const QString& msg) { m_logView->append(msg); }
void MinimalSynchronizationView::setProgress(int p) { m_progressBar->setValue(p); }

void MinimalSynchronizationView::displayCalendars(const QVector<TweekCalendar>& calendars) {
    m_calendarCombo->clear();
    for (const auto& calendar : calendars) {
        m_calendarCombo->addItem(calendar.name, calendar.id);
    }
    logMessage(QString("Найдено %1 календарей.").arg(calendars.size()));
}

void MinimalSynchronizationView::displayTasks(const QVector<TweekTask>& tasks) {
    m_tasksList->clear();
    m_taskMap.clear();
    for (const auto& task : tasks) {
        auto* item = new QListWidgetItem(task.title, m_tasksList);
        item->setData(Qt::UserRole, task.id);
        m_taskMap[task.id] = task;
    }
    logMessage(QString("Найдено %1 задач на сегодня.").arg(tasks.size()));
}

void MinimalSynchronizationView::setControlsEnabled(bool enabled) {
    m_connectButton->setEnabled(enabled);
    m_closeButton->setEnabled(enabled);
    m_getTasksButton->setEnabled(enabled);
    m_confirmButton->setEnabled(enabled);
    m_calendarCombo->setEnabled(enabled);
}

void MinimalSynchronizationView::onConnectClicked() {
    setControlsEnabled(false);
    emit connectRequested(m_emailEdit->text(), m_passwordEdit->text());
}

void MinimalSynchronizationView::onGetTasksClicked() {
    QString calendarId = m_calendarCombo->currentData().toString();
    if (calendarId.isEmpty()) {
        logMessage("Ошибка: календарь не выбран.");
        return;
    }
    setControlsEnabled(false);
    updateStatus("Загрузка задач...");
    emit tasksRequested(calendarId);
}

void MinimalSynchronizationView::onConfirmClicked() {
    QVector<TweekTask> selectedTasks;
    for (auto* item : m_tasksList->selectedItems()) {
        QString taskId = item->data(Qt::UserRole).toString();
        if (m_taskMap.contains(taskId)) {
            selectedTasks.append(m_taskMap[taskId]);
        }
    }

    if (selectedTasks.isEmpty()) {
        logMessage("Задачи не выбраны.");
        return;
    }

    setControlsEnabled(false);
    updateStatus("Сохранение задач...");
    emit tasksSelected(selectedTasks);
}

bool MinimalSynchronizationView::eventFilter(QObject* watched, QEvent* event)
{
    // Сначала проверяем, что событие пришло именно от того объекта, за которым мы следим
    if (watched == m_calendarCombo) {

        // Затем проверяем, что тип события - это именно нажатие кнопки мыши
        if (event->type() == QEvent::MouseButtonPress) {

            // Если оба условия верны - выполняем наше действие!
            m_tasksList->clear();
            m_taskMap.clear();
            updateStatus("Выберите календарь и нажмите 'Получить задачи'.");
        }
    }

    // ВАЖНО: передаем событие дальше для стандартной обработки.
    // Если этого не сделать, выпадающий список не откроется после клика.
    return QObject::eventFilter(watched, event);
}
