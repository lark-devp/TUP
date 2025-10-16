#include "BarChartView.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <algorithm> // Для std::max_element

BarChartView::BarChartView(QWidget *parent)
    : QWidget(parent), m_weeklyData(7, 0) // Инициализируем 7 нулями
{
    m_dayLabels << "Пн" << "Вт" << "Ср" << "Чт" << "Пт" << "Сб" << "Вс";
    setMinimumHeight(250); // Задаем минимальную высоту для диаграммы
}

void BarChartView::setData(const QVector<qint64>& weeklyData)
{
    if (weeklyData.size() == 7) {
        m_weeklyData = weeklyData;
        update(); // Вызываем перерисовку виджета
    }
}

void BarChartView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // --- 1. Определяем константы и геометрию ---
    const int paddingLeft = 40;
    const int paddingRight = 10;
    const int paddingTop = 20;
    const int paddingBottom = 30;

    QRect chartRect(paddingLeft, paddingTop,
                    width() - paddingLeft - paddingRight,
                    height() - paddingTop - paddingBottom);

    if (!chartRect.isValid()) return;

    // --- 2. Находим максимальное значение для масштабирования ---
    qint64 maxValue = *std::max_element(m_weeklyData.begin(), m_weeklyData.end());
    if (maxValue == 0) {
        maxValue = 60; // Если данных нет, ось будет до 60 минут
    }
    // Округляем до ближайших 30 минут вверх для красивой шкалы
    maxValue = ((maxValue + 29) / 30) * 30;

    const double yScale = static_cast<double>(chartRect.height()) / maxValue;

    // --- 3. Рисуем оси и сетку ---
    painter.setPen(QPen(Qt::gray, 1, Qt::DotLine));

    // Горизонтальные линии сетки и метки на оси Y
    int numGridLines = 4;
    for (int i = 0; i <= numGridLines; ++i) {
        int y = chartRect.bottom() - (i * chartRect.height() / numGridLines);
        painter.drawLine(chartRect.left(), y, chartRect.right(), y);

        qint64 labelValue = i * maxValue / numGridLines;
        painter.drawText(QRect(0, y - 10, paddingLeft - 5, 20), Qt::AlignRight, QString::number(labelValue));
    }
    painter.drawText(QRect(0, paddingTop-20, paddingLeft - 5, 20), Qt::AlignRight, "min");


    // Ось X
    painter.setPen(Qt::black);
    painter.drawLine(chartRect.bottomLeft(), chartRect.bottomRight());
    // Ось Y
    painter.drawLine(chartRect.bottomLeft(), chartRect.topLeft());


    // --- 4. Рисуем столбцы и метки дней недели ---
    double barWidth = static_cast<double>(chartRect.width()) / m_dayLabels.size() * 0.6;
    double barSpacing = static_cast<double>(chartRect.width()) / m_dayLabels.size() * 0.4;

    for (int i = 0; i < m_dayLabels.size(); ++i) {
        double x = chartRect.left() + (i * (barWidth + barSpacing)) + (barSpacing / 2);

        // Рисуем метку дня недели
        painter.drawText(QRect(x, chartRect.bottom() + 5, barWidth, 20), Qt::AlignCenter, m_dayLabels[i]);

        qint64 value = m_weeklyData[i];
        int barHeight = static_cast<int>(value * yScale);

        QRectF barRect(x, chartRect.bottom() - barHeight, barWidth, barHeight);

        if (value > 0) {
            // Рисуем столбец
            painter.setBrush(QColor("#4a90e2"));
            painter.setPen(Qt::NoPen);
            painter.drawRect(barRect);
        } else {
            // Рисуем линию у нуля, если времени не было
            painter.setPen(QPen(QColor("#4a90e2"), 3));
            int y_zero = chartRect.bottom();
            painter.drawLine(QPointF(x, y_zero), QPointF(x + barWidth, y_zero));
        }
    }
}
