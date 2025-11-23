#pragma once

#include <QWidget>
#include <QVector>

class BarChartView : public QWidget
{
    Q_OBJECT

public:
    explicit BarChartView(QWidget *parent = nullptr);


    void setData(const QVector<qint64>& weeklyData);

protected:

    void paintEvent(QPaintEvent *event) override;

private:
    QVector<qint64> m_weeklyData;
    QStringList m_dayLabels;
};
