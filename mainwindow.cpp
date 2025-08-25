#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), stack (new QStackedWidget(this)), taskTimerWindow(new TaskTimerWindow), singleAnalyticsWindow (new SingleTaskAnalyticsWindow),
    multiAnalyticsWindow(new MultiTaskAnalyticsWindow), taskSelectorWindow(new TaskSelectorWindow), taskEditorWindow(new TaskEditorWindow)
{

    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI() {
    stack->addWidget(taskSelectorWindow);      // index 0
    stack->addWidget(taskTimerWindow);          // index 1
    stack->addWidget(singleAnalyticsWindow);    // index 2
    stack->addWidget(multiAnalyticsWindow);       // index 3
    stack->addWidget(taskEditorWindow);         // index 4

    setCentralWidget (stack);
    stack->setCurrentWidget(taskSelectorWindow);
    setWindowTitle("Task Tracker");
    resize (800, 600);
}

void MainWindow::connectSignals() {
    // Пример: переход к окну таймера после выбора задачи
    connect(taskSelectorWindow, &TaskSelectorWindow::taskSelected, this, [this]() {
        stack->setCurrentWidget(taskTimerWindow);
    });

    // Пример: переход к аналитике одной задачи
    connect(taskTimerWindow, &TaskTimerWindow::analyzeTaskRequested, this, [this]() {
        stack->setCurrentWidget(singleAnalyticsWindow);
    });

    // Пример: переход к аналитике нескольких задач
    connect(taskSelectorWindow, &TaskSelectorWindow::multiTaskAnalyzeRequested, this, [this]() {
        stack->setCurrentWidget(multiAnalyticsWindow);
    });

    // Пример: редактирование задачи
    connect(taskTimerWindow, &TaskTimerWindow::editTaskRequested, this, [this]() {
        stack->setCurrentWidget(taskEditorWindow);
    });

    // Вернуться назад (например, из редактора к выбору задачи)
    connect(taskEditorWindow, &TaskEditorWindow::backToSelector, this, [this]() {
        stack->setCurrentWidget(taskSelectorWindow);
    });

}
