// TaskSelectorWindow.cpp
#include "TaskSelectorWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

TaskSelectorWindow::TaskSelectorWindow(QWidget *parent) : QWidget(parent) {
    // Основной layout
    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    // Заголовок
    QLabel *title = new QLabel("Выберите задачу", this);
    title->setAlignment(Qt::AlignHCenter);
    title->setStyleSheet(
        "QLabel {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   margin-bottom: 20px;"
        "}"
        );
    layout->addWidget(title);

    // Список задач
    auto *taskList = new QListWidget(this);
    taskList->setSelectionMode(QAbstractItemView::SingleSelection);
    taskList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    taskList->setStyleSheet(
        "QListWidget {"
        "   border: 1px solid #ccc;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "   background-color: #fefefe;"
        "   font-size: 14px;"
        "}"
        "QListWidget::item {"
        "   padding: 12px;"
        "   margin: 2px 0;"
        "   border-radius: 5px;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #4a90e2;"
        "   color: white;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #e6f0ff;"
        "}"
        );
    layout->addWidget(taskList);

    // Пример добавления задач

    taskList->addItem("Задача 1: Встретиться с Ксюшей");
    taskList->addItem("Задача 2: Написать код");
    taskList->addItem("Задача 3: Тестирование");
    taskList->addItem("Задача 4: Исправить баги");
    taskList->addItem("Задача 5: Подготовить презентацию");

    // Подключаем сигнал выбора элемента
    connect(taskList, &QListWidget::itemClicked, this, [this](QListWidgetItem *item){
        Q_UNUSED(item); // если слот не использует сам элемент
        this->taskSelected(); // вызываем твой слот taskSelected
    });


    // Кнопка "Анализ нескольких задач"
    auto *multiTaskBtn = new QPushButton("Анализ нескольких задач", this);
    multiTaskBtn->setMinimumSize(260, 55);
    multiTaskBtn->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #333333, stop:1 #000000);"
        "   color: white;"
        "   border-radius: 12px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #444444, stop:1 #111111);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #111111, stop:1 #000000);"
        "}"
        );

    // Добавим тень кнопке
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 100));
    multiTaskBtn->setGraphicsEffect(shadow);

    layout->addWidget(multiTaskBtn, 0, Qt::AlignHCenter);

    // Сигнал нажатия кнопки
    connect(multiTaskBtn, &QPushButton::clicked, this, &TaskSelectorWindow::multiTaskAnalyzeRequested);
}
