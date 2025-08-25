#include "TaskTimerWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

TaskTimerWindow::TaskTimerWindow(QWidget *parent) : QWidget (parent){
    auto *layout = new QVBoxLayout(this);

    auto *analyzeBtn = new QPushButton ("Анализ задачи", this);
    auto *editBtn = new QPushButton("Изменить задачу", this);

    connect(analyzeBtn, &QPushButton::clicked, this, &TaskTimerWindow::analyzeTaskRequested);
    connect(editBtn, &QPushButton::clicked, this, &TaskTimerWindow::editTaskRequested);

    layout->addWidget(analyzeBtn);
    layout->addWidget(editBtn);
};
