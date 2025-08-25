#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>



#include "TaskTimerWindow.h"
#include "SingleTaskAnalyticsWindow.h"
#include "MultiTaskAnalyticsWindow.h"
#include "TaskSelectorWindow.h"
#include "TaskEditorWindow.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); // explicit - конструктор должен использоваться только в явных преобразованиях типов
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stack;



    TaskTimerWindow *taskTimerWindow;
    SingleTaskAnalyticsWindow *singleAnalyticsWindow;
    MultiTaskAnalyticsWindow *multiAnalyticsWindow;
    TaskSelectorWindow *taskSelectorWindow;
    TaskEditorWindow *taskEditorWindow;


    void setupUI();
    void connectSignals();
};
#endif // MAINWINDOW_H
