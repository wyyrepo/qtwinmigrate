#include "chartwidget2.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

ChartWidget2::ChartWidget2(QWidget *parent) : QWidget(parent)
{
    isPress = false;
    isMove = false;
    isErase = false;
    startPoint = endPoint = newStartPoint = newEndPoint = QPointF(0,0);
    chart = new Chart2(this);
    mask = new QWidget(this);

    //this->chart->setStyleSheet(QString("background-color: rgba(255, 255, 255, 55%);"));
    mask->setStyleSheet(QString("background-color:transparent;"));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(chart);
    layout->setSpacing(0);
    layout->setMargin(0);
    this->setLayout(layout);

    mask->installEventFilter(this);
//    mask->setMouseTracking(true);
    connect(this, &ChartWidget2::selectData, chart, &Chart2::handleData);
}

void ChartWidget2::receiveData(const QList<qreal> &data)
{
    chart->receiveData(data);
}

bool ChartWidget2::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent;
    if (event->type() == QEvent::MouseButtonPress) {
        isPress = true;
        mouseEvent = static_cast<QMouseEvent *>(event);
        newStartPoint = mouseEvent->pos();
        update();
    } else if (event->type() == QEvent::MouseMove && isPress) {
        isMove = true;
        mouseEvent = static_cast<QMouseEvent *>(event);
        newEndPoint = mouseEvent->pos();
        mask->update();
    } else if (event->type() == QEvent::MouseButtonRelease && isPress) {
        isPress = false;
        isMove = false;
        emit selectData(QRectF(startPoint, endPoint));
    } else if (event->type() == QEvent::Paint) {
        QPainter painter(mask);
        painter.setPen(QPen(Qt::white, 1));
        if (isPress == false) {
            painter.drawRect(QRectF(startPoint, endPoint));
        } else if (isMove == false) {
            startPoint = endPoint = QPointF(-1,-1);
        } else {
            startPoint = newStartPoint;
            endPoint = newEndPoint;
            painter.drawRect(QRectF(startPoint, endPoint));
        }
    }

    return QWidget::eventFilter(watched, event);
}

void ChartWidget2::resizeEvent(QResizeEvent *event) //鼠标拖框
{
   mask->setGeometry(0,0,this->size().width(),this->size().height());
}
