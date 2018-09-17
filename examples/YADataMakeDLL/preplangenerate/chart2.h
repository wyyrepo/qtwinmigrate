#ifndef CHART2_H
#define CHART2_H

#include <QWidget>
#include <QPixmap>
#include <QRectF>

class Chart2 : public QWidget
{
    Q_OBJECT
public:
    explicit Chart2(QWidget *parent = nullptr);
    int pixHeight;
signals:

public slots:
    void receiveData(const QList<qreal> &);
    void handleData(const QRectF &);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int line;

    QPixmap *pix;
    QList<qreal> randNum;
};

#endif // CHART2_H
