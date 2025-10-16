// SingleTaskAnalyticsWindow.cpp
#include "SingleTaskAnalyticsWindow.h"
#include <QVBoxLayout>
#include <QLabel>

SingleTaskAnalyticsWindow::SingleTaskAnalyticsWindow(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Анализ задачи"));
}
