// TaskEditorWindow.h
#ifndef TASKEDITORWINDOW_H
#define TASKEDITORWINDOW_H

#include <QWidget>

class TaskEditorWindow : public QWidget {
    Q_OBJECT

public:
    explicit TaskEditorWindow(QWidget *parent = nullptr);

signals:
    void backToSelector();
};

#endif // TASKEDITORWINDOW_H
