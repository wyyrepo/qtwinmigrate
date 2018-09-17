#include "chart2.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QDebug>
#include <QPaintEvent>
#include <QtMath>
#include <QPen>
#include "constract.h"
#include <QMouseEvent>

Chart2::Chart2(QWidget *parent) : QWidget(parent)
{
    line = 0;
    pixHeight = TIME_UNIT;
    pix = new QPixmap(FRAME_MAX, pixHeight);
    pix->fill(Qt::transparent);
}

void Chart2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->size().width(),pixHeight,*pix);

}

void Chart2::receiveData(const QList<qreal> &data)
{
    qreal x, y;
    int newPixHeight;
    QPixmap *newPix;

    randNum = data;
    newPixHeight = pixHeight + TIME_UNIT;
    pixHeight = newPixHeight;
    newPix = new QPixmap(FRAME_MAX, pixHeight);
    newPix->fill(Qt::transparent);
 //   qDebug() << sizeof(newPix);
    QPainter newPainter(newPix);
    newPainter.drawPixmap(0, 0, pix->width(), pix->height(), *pix);

    for (int i = 0; i < FRAME_MAX; i++) {      //  打点颜色选择
        qreal y = line + TIME_UNIT;

        if (randNum[i] < FREQ_LOW) {
            newPainter.setPen(QPen(Qt::blue, 1));
        } else if (randNum[i] < FREQ_MIDDLE) {
            newPainter.setPen(QPen(Qt::black, 1));
        } else {
            newPainter.setPen(QPen(Qt::red, 1));
        }

        //int index = randNum[i]
        newPainter.drawPoint(i, y);
    }

    delete pix;
    pix = newPix;

    setMinimumHeight(pixHeight);
    line+=TIME_UNIT;
    update();
}

void Chart2::handleData(const QRectF &rect) //框图数据
{
    if(rect.x() !=-1 &&rect.y() !=-1)
    {
        qreal startX, startY, endX, endY;

        startX = qFloor(rect.x() * FRAME_MAX / this->size().width());
        startY = qCeil(rect.y() / TIME_UNIT);

        endX = qCeil((rect.x() + rect.width()) * FRAME_MAX / this->size().width());
        endY = qFloor((rect.y() + rect.height()) / TIME_UNIT);

        qDebug() <<"开始时间"<<  startY <<"结束时间"<< endY;
        qDebug() <<"起始频率"<< startX << "终止频率"<< endX;
    }

//    qreal startX, startY, endX, endY;

//    startX = rect.x() * FRAME_MAX / this->size().width();
//    startY = qCeil(rect.y() / TIME_UNIT);
//    endX = (rect.x() + rect.width()) * FRAME_MAX / this->size().width();
//    endY = qFloor((rect.y() + rect.height()) / TIME_UNIT);


}
