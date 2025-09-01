// TaskTimerWindow.cpp
#include "TaskTimerWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QTime>
#include <QWidget>

// Класс для кругового таймера
class CircularTimer : public QWidget {

public:
    explicit CircularTimer(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(250, 250);
        m_time.start();
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() { update(); });
        timer->start(1000);
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int w = width();
        int h = height();
        int margin = 10;
        QRectF rect(margin, margin, w - 2*margin, h - 2*margin);

        // Фон круга
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(50, 50, 50));
        painter.drawEllipse(rect);

        // Процент заполнения (секунды в минуте)
        int secs = m_time.elapsed() / 1000;
        int angle = (secs % 60) * 6; // 360/60 = 6 градусов на секунду

        // Прогресс
        QPen pen(Qt::white, 12, Qt::SolidLine, Qt::FlatCap);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawArc(rect, 90 * 16, -angle * 16); // Qt использует 1/16 градуса

        // Текст времени
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        QTime displayTime(0,0,0);
        displayTime = displayTime.addSecs(secs);
        QString timeStr = displayTime.toString("HH:mm:ss");
        painter.drawText(rect, Qt::AlignCenter, timeStr);
    }

private:
    QElapsedTimer m_time;
};


TaskTimerWindow::TaskTimerWindow(QWidget *parent) : QWidget(parent) {
    setMinimumSize(500, 500);

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(30);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Круговой таймер
    auto *circleTimer = new CircularTimer(this);
    layout->addWidget(circleTimer, 0, Qt::AlignHCenter);

    // Кнопки
    auto *analyzeBtn = new QPushButton("Анализ задачи", this);
    auto *editBtn = new QPushButton("Изменить задачу", this);

    QString btnStyle =
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #333333, stop:1 #000000);"
        "   color: white;"
        "   border-radius: 15px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   padding: 15px 30px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #444444, stop:1 #111111);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #111111, stop:1 #000000);"
        "}";

    analyzeBtn->setStyleSheet(btnStyle);
    editBtn->setStyleSheet(btnStyle);

    for (auto *btn : {analyzeBtn, editBtn}) {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setOffset(0, 6);
        shadow->setColor(QColor(0, 0, 0, 120));
        btn->setGraphicsEffect(shadow);
        btn->setFixedSize(280, 70);
    }

    // Сигналы кнопок
    connect(analyzeBtn, &QPushButton::clicked, this, &TaskTimerWindow::analyzeTaskRequested);
    connect(editBtn, &QPushButton::clicked, this, &TaskTimerWindow::editTaskRequested);

    layout->addWidget(analyzeBtn, 0, Qt::AlignHCenter);
    layout->addWidget(editBtn, 0, Qt::AlignHCenter);
}

