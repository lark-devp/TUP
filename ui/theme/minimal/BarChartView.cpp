#include "BarChartView.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <algorithm>

BarChartView::BarChartView(QWidget *parent)
    : QWidget(parent), m_weeklyData(7, 0)
{
    m_dayLabels << "Пн" << "Вт" << "Ср" << "Чт" << "Пт" << "Сб" << "Вс";
    setMinimumHeight(250);
}

void BarChartView::setData(const QVector<qint64>& weeklyData)
{
    if (weeklyData.size() == 7) {
        m_weeklyData = weeklyData;
        update();
    }
}

void BarChartView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int paddingLeft = 40;
    const int paddingRight = 10;
    const int paddingTop = 40;
    const int paddingBottom = 30;

    QRect chartRect(paddingLeft, paddingTop,
                    width() - paddingLeft - paddingRight,
                    height() - paddingTop - paddingBottom);

    if (!chartRect.isValid()) return;

    qint64 maxValue = *std::max_element(m_weeklyData.begin(), m_weeklyData.end());
    if (maxValue == 0) {
        maxValue = 60;
    }
    maxValue = ((maxValue + 29) / 30) * 30;

    const double yScale = static_cast<double>(chartRect.height()) / maxValue;

    painter.setPen(QPen(Qt::gray, 1, Qt::DotLine));

    int numGridLines = 4;
    for (int i = 0; i <= numGridLines; ++i) {
        int y = chartRect.bottom() - (i * chartRect.height() / numGridLines);
        painter.drawLine(chartRect.left(), y, chartRect.right(), y);

        qint64 labelValue = i * maxValue / numGridLines;
        painter.drawText(QRect(0, y - 10, paddingLeft - 5, 20), Qt::AlignRight, QString::number(labelValue));
    }
    painter.drawText(QRect(0, 5, paddingLeft - 5, 20), Qt::AlignRight, "мин");


    painter.setPen(Qt::black);
    painter.drawLine(chartRect.bottomLeft(), chartRect.bottomRight());
    painter.drawLine(chartRect.bottomLeft(), chartRect.topLeft());


    double barWidth = static_cast<double>(chartRect.width()) / m_dayLabels.size() * 0.6;
    double barSpacing = static_cast<double>(chartRect.width()) / m_dayLabels.size() * 0.4;

    for (int i = 0; i < m_dayLabels.size(); ++i) {
        double x = chartRect.left() + (i * (barWidth + barSpacing)) + (barSpacing / 2);

        painter.drawText(QRect(x, chartRect.bottom() + 5, barWidth, 20), Qt::AlignCenter, m_dayLabels[i]);

        qint64 value = m_weeklyData[i];
        int barHeight = static_cast<int>(value * yScale);

        QRectF barRect(x, chartRect.bottom() - barHeight, barWidth, barHeight);

        if (value > 0) {
            painter.setBrush(QColor("#4a90e2"));
            painter.setPen(Qt::NoPen);
            painter.drawRect(barRect);

            painter.setPen(Qt::black);
            QRectF textRect(barRect.left(), barRect.top() - 20, barRect.width(), 20);
            painter.drawText(textRect, Qt::AlignCenter, QString::number(value));

        } else {
            painter.setPen(QPen(QColor("#dddddd"), 2));
            int y_zero = chartRect.bottom();
            painter.drawLine(QPointF(x, y_zero), QPointF(x + barWidth, y_zero));
        }
    }
}
