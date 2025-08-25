// TaskSelectorWindow.cpp
#include "TaskSelectorWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

TaskSelectorWindow::TaskSelectorWindow(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);

    auto *singleTaskBtn = new QPushButton("Начать задачу", this);
    auto *multiTaskBtn = new QPushButton("Анализ нескольких задач", this);

    connect(singleTaskBtn, &QPushButton::clicked, this, &TaskSelectorWindow::taskSelected);
    connect(multiTaskBtn, &QPushButton::clicked, this, &TaskSelectorWindow::multiTaskAnalyzeRequested);

    layout->addWidget(singleTaskBtn);
    layout->addWidget(multiTaskBtn);
}
