#ifndef CHARTWIDGET2_H
#define CHARTWIDGET2_H

#include <QWidget>
#include <QPointF>
#include "chart2.h"

class ChartWidget2 : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget2(QWidget *parent = nullptr);

signals:
    void selectData(const QRectF &);

public slots:
    void receiveData(const QList<qreal> &);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Chart2 *chart;
    QWidget *mask;
    bool isPress;
    bool isMove;
    bool isErase;
    QPointF startPoint;
    QPointF endPoint;
    QPointF newStartPoint;
    QPointF newEndPoint;
};

#endif // CHARTWIDGET2_H
