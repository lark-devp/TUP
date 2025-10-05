#pragma once

#include <QWidget>
#include <QVector>

class BarChartView : public QWidget
{
    Q_OBJECT

public:
    explicit BarChartView(QWidget *parent = nullptr);

    // Метод для передачи данных в виджет
    // Данные - это вектор из 7 значений (время в минутах для Пн, Вт, ..., Вс)
    void setData(const QVector<qint64>& weeklyData);

protected:
    // Переопределяем метод отрисовки
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<qint64> m_weeklyData; // Хранит данные для текущей недели
    QStringList m_dayLabels;      // "Пн", "Вт", "Ср", ...
};
