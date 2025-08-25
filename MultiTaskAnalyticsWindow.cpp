// MultiTaskAnalyticsWindow.cpp
#include "MultiTaskAnalyticsWindow.h"
#include <QVBoxLayout>
#include <QLabel>

MultiTaskAnalyticsWindow::MultiTaskAnalyticsWindow(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Анализ задач"));
}
