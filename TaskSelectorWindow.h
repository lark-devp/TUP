// TaskSelectorWindow.h
#ifndef TASKSELECTORWINDOW_H
#define TASKSELECTORWINDOW_H

#include <QWidget>

class TaskSelectorWindow : public QWidget {
    Q_OBJECT

public:
    explicit TaskSelectorWindow(QWidget *parent = nullptr);

signals:
    void taskSelected();               // одна задача
    void multiTaskAnalyzeRequested();  // несколько задач
};

#endif // TASKSELECTORWINDOW_H
