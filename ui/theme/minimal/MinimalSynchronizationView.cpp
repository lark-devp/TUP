#include "MinimalSynchronizationView.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAction>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QColor>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QTime>

MinimalSynchronizationView::MinimalSynchronizationView(QWidget *parent)
    : ISynchronizationView(parent)
{
    this->setStyleSheet("background-color: #f4f7fa;");

    const QString titleStyle = R"(
        font-size: 22px; font-weight: bold; color: #333;
    )";
    const QString statusStyle = R"(
        font-size: 14px; color: #555;
    )";
    const QString inputStyle = R"(
        QLineEdit, QComboBox {
            background-color: #ffffff; border: 1px solid #dcdcdc; border-radius: 8px;
            padding: 10px; font-size: 14px;
        }
        QLineEdit:focus, QComboBox:focus { border-color: #4a90e2; }
        QComboBox::drop-down { border: none; }
    )";
    const QString listStyle = R"(
        QListWidget {
            background-color: #ffffff; border: 1px solid #dcdcdc; border-radius: 8px;
            font-size: 14px; alternate-background-color: #f7f9fc;
        }
        QListWidget::item { padding: 10px; border-bottom: 1px solid #eee; }
        QListWidget::item:selected { background-color: #4a90e2; color: white; }
    )";
    const QString logStyle = R"(
        QTextEdit {
            background-color: #2b2b2b; border: 1px solid #444; border-radius: 8px;
            font-family: 'Courier New', Courier, monospace; font-size: 12px; color: #a9b7c6;
        }
    )";
    const QString progressBarStyle = R"(
        QProgressBar {
            border: 1px solid #dcdcdc; border-radius: 8px; text-align: center;
            background-color: #ffffff; color: #333; height: 24px;
        }
        QProgressBar::chunk { background-color: #4CAF50; border-radius: 7px; }
    )";
    const QString primaryButtonStyle = R"(
        QPushButton {
           background-color: #4a90e2; color: white; border-radius: 8px;
           font-size: 14px; font-weight: bold; padding: 10px; border: none;
        }
        QPushButton:hover { background-color: #5aa1f2; }
        QPushButton:pressed { background-color: #3a80d2; }
        QPushButton:disabled { background-color: #dcdcdc; color: #a0a0a0; }
    )";
    const QString secondaryButtonStyle = R"(
        QPushButton {
           background-color: #6c757d; color: white; border-radius: 8px;
           font-size: 14px; font-weight: bold; padding: 10px; border: none;
        }
        QPushButton:hover { background-color: #868e96; }
        QPushButton:pressed { background-color: #5a6268; }
    )";

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(25, 25, 25, 25);
    m_mainLayout->setSpacing(20);

    setupLoginUi();
    setupSyncUi();

    m_statusLabel = new QLabel("Готово.", this);
    m_statusLabel->setStyleSheet(statusStyle);
    m_progressBar = new QProgressBar(this);
    m_progressBar->setStyleSheet(progressBarStyle);
    m_logView = new QTextEdit(this);
    m_logView->setReadOnly(true);
    m_logView->setStyleSheet(logStyle);
    m_logView->setFixedHeight(100);

    m_mainLayout->addWidget(m_loginWidget);
    m_mainLayout->addWidget(m_syncWidget);
    m_mainLayout->addWidget(m_statusLabel);
    m_mainLayout->addWidget(m_progressBar);
    m_mainLayout->addWidget(new QLabel("Лог операций:", this));
    m_mainLayout->addWidget(m_logView);

    for (auto* button : findChildren<QPushButton*>()) {
        button->setCursor(Qt::PointingHandCursor);
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15); shadow->setOffset(0, 3); shadow->setColor(QColor(0, 0, 0, 80));
        button->setGraphicsEffect(shadow);
    }
    m_connectButton->setStyleSheet(primaryButtonStyle);
    m_getTasksButton->setStyleSheet(primaryButtonStyle);
    m_confirmButton->setStyleSheet(primaryButtonStyle);
    m_closeButton->setStyleSheet(secondaryButtonStyle);
    m_disconnectButton->setStyleSheet(secondaryButtonStyle);
    m_emailEdit->setStyleSheet(inputStyle);
    m_passwordEdit->setStyleSheet(inputStyle);
    m_calendarCombo->setStyleSheet(inputStyle);
    m_tasksList->setStyleSheet(listStyle);
    m_loginTitle->setStyleSheet(titleStyle);
    m_syncTitle->setStyleSheet(titleStyle);
    m_closeLoginButton->setStyleSheet(secondaryButtonStyle);

    setMinimumSize(500, 700);
    setWindowTitle("Синхронизация с Tweek");

    connect(m_closeButton, &QPushButton::clicked, this, &ISynchronizationView::closeRequested);
    showState(ViewState::Login);
}

void MinimalSynchronizationView::setupLoginUi() {
    m_loginWidget = new QWidget(this);
    auto layout = new QVBoxLayout(m_loginWidget);
    layout->setSpacing(15);

    m_loginTitle = new QLabel("Подключение к Tweek", this);
    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setPlaceholderText("your@example.com");
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setPlaceholderText("••••••••");
    m_connectButton = new QPushButton("Войти", this);

    m_passwordVisibilityAction = m_passwordEdit->addAction(createEyeIcon(true), QLineEdit::TrailingPosition);
    m_passwordVisibilityAction->setToolTip("Показать/скрыть пароль");
    connect(m_passwordVisibilityAction, &QAction::triggered, this, &MinimalSynchronizationView::onPasswordVisibilityToggled);

    m_closeLoginButton = new QPushButton("Закрыть", this);

    connect(m_closeLoginButton, &QPushButton::clicked, this, &ISynchronizationView::closeRequested);

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_closeLoginButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_connectButton);

    layout->addWidget(m_loginTitle, 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("Email:", this));
    layout->addWidget(m_emailEdit);
    layout->addWidget(new QLabel("Пароль:", this));
    layout->addWidget(m_passwordEdit);
    layout->addStretch();

    layout->addLayout(buttonLayout);

    connect(m_connectButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onConnectClicked);
}

void MinimalSynchronizationView::setupSyncUi() {
    m_syncWidget = new QWidget(this);
    auto layout = new QVBoxLayout(m_syncWidget);
    layout->setSpacing(5);

    m_syncTitle = new QLabel("Импорт задач", this);
    m_calendarCombo = new QComboBox(this);
    m_calendarCombo->installEventFilter(this);
    m_getTasksButton = new QPushButton("Получить задачи на сегодня", this);

    m_tasksList = new QListWidget(this);
    m_tasksList->setSelectionMode(QAbstractItemView::MultiSelection);
    m_confirmButton = new QPushButton("Импортировать выбранные", this);

    auto buttonLayout = new QHBoxLayout();
    m_disconnectButton = new QPushButton("Сменить аккаунт", this);
    m_closeButton = new QPushButton("Закрыть", this);
    buttonLayout->addWidget(m_disconnectButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_closeButton);

    layout->addWidget(m_syncTitle, 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("1. Выберите календарь:", this));
    layout->addWidget(m_calendarCombo);
    layout->addWidget(m_getTasksButton);
    layout->addWidget(new QLabel("2. Выберите задачи для импорта:", this));
    layout->addWidget(m_tasksList);
    layout->addWidget(m_confirmButton);
    layout->addStretch();
    layout->addLayout(buttonLayout);

    connect(m_getTasksButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onGetTasksClicked);
    connect(m_confirmButton, &QPushButton::clicked, this, &MinimalSynchronizationView::onConfirmClicked);
    connect(m_disconnectButton, &QPushButton::clicked, this, &ISynchronizationView::disconnectRequested);
}

void MinimalSynchronizationView::showState(ViewState state) {
    if (state == ViewState::Login) {
        m_loginWidget->show();
        m_syncWidget->hide();
        updateStatus("Требуется вход в Tweek.");
        m_calendarCombo->clear();
        m_tasksList->clear();
        m_logView->clear();
        m_emailEdit->clear();
        m_passwordEdit->clear();
        setProgress(0);
    } else {
        m_loginWidget->hide();
        m_syncWidget->show();
        updateStatus("Подключено. Выберите календарь для импорта задач.");
    }
}

QWidget* MinimalSynchronizationView::getWidget() { return this; }
void MinimalSynchronizationView::updateStatus(const QString& status) { m_statusLabel->setText(status); }
void MinimalSynchronizationView::logMessage(const QString& msg) { m_logView->append(QString("[%1] %2").arg(QTime::currentTime().toString("hh:mm:ss")).arg(msg)); }
void MinimalSynchronizationView::setProgress(int p) { m_progressBar->setValue(p); }

void MinimalSynchronizationView::displayCalendars(const QVector<TweekCalendar>& calendars) {
    m_calendarCombo->clear();
    m_calendarCombo->addItem("— Выберите календарь —", QVariant());
    for (const auto& calendar : calendars) {
        m_calendarCombo->addItem(calendar.name, calendar.id);
    }
    logMessage(QString("Найдено %1 календарей.").arg(calendars.size()));
}

void MinimalSynchronizationView::selectCalendar(const QString& calendarId)
{
    int index = m_calendarCombo->findData(calendarId);
    if (index != -1) {
        m_calendarCombo->setCurrentIndex(index);
    }
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
    m_getTasksButton->setEnabled(enabled);
    m_confirmButton->setEnabled(enabled);
    m_calendarCombo->setEnabled(enabled);
    m_disconnectButton->setEnabled(enabled);
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
        logMessage("Задачи для импорта не выбраны.");
        return;
    }
    setControlsEnabled(false);
    emit tasksSelected(selectedTasks);
}

bool MinimalSynchronizationView::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_calendarCombo && event->type() == QEvent::MouseButtonPress) {
        m_tasksList->clear();
        m_taskMap.clear();
        updateStatus("Выберите календарь и нажмите 'Получить задачи'.");
    }
    return QObject::eventFilter(watched, event);
}

void MinimalSynchronizationView::onPasswordVisibilityToggled()
{
    if (m_passwordEdit->echoMode() == QLineEdit::Password) {
        m_passwordEdit->setEchoMode(QLineEdit::Normal);
        m_passwordVisibilityAction->setIcon(createEyeIcon(false));
    } else {
        m_passwordEdit->setEchoMode(QLineEdit::Password);
        m_passwordVisibilityAction->setIcon(createEyeIcon(true));
    }
}

QIcon MinimalSynchronizationView::createEyeIcon(bool shown)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor penColor = palette().color(QPalette::Text);
    painter.setPen(penColor);

    QPainterPath path;
    path.moveTo(1, 8);
    path.quadTo(8, 2, 15, 8);
    path.quadTo(8, 14, 1, 8);
    painter.drawPath(path);

    painter.setBrush(penColor);
    painter.drawEllipse(6, 6, 4, 4);
    painter.setBrush(Qt::NoBrush);

    if (!shown) {
        painter.setPen(QPen(penColor, 1.5));
        painter.drawLine(2, 2, 14, 14);
    }

    return QIcon(pixmap);
}
