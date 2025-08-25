#ifndef TASKTIMERWINDOW_H
#define TASKTIMERWINDOW_H

#include <QWidget>

class TaskTimerWindow : public QWidget {
    Q_OBJECT


public:
    explicit TaskTimerWindow (QWidget *parent = nullptr);

signals:
    void analyzeTaskRequested();
    void editTaskRequested();
};

#endif // TASKTIMERWINDOW_H
