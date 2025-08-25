// TaskEditorWindow.cpp
#include "TaskEditorWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

TaskEditorWindow::TaskEditorWindow(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);

    auto *backBtn = new QPushButton("Назад к списку задач", this);
    connect(backBtn, &QPushButton::clicked, this, &TaskEditorWindow::backToSelector);

    layout->addWidget(new QPushButton("Редактировать задачу"));
    layout->addWidget(backBtn);
}
