#ifndef AUTOPREPLAN_H
#define AUTOPREPLAN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableView>

#include <QTimer>
#include "chartwidget2.h"
#include <QScrollArea>
#include "topwidget.h"

//#include <QTableView>
#include <tableview.h>

class AutoPrePlan : public QWidget
{
    Q_OBJECT
public:
    explicit AutoPrePlan(QWidget *parent = 0);
    ~AutoPrePlan();

signals:
    void clearLeftWidget();
    void emitChart1Data(const QList<qreal> &data);
    void emitChart2Data(const QList<qreal> &data);

public slots:

private slots:
    void showWidget(int id);
    void receiveTimeOut();

private:
    void initLeftWidget();
    void initRightWidget();
    void initBottomWidget();
    void initLayout();
    void initTopLayout();


    int maskType;
    QVBoxLayout *leftLayout;
    QGridLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QList<QPushButton *> leftButtons;
    QSignalMapper *signalMapper;
    QGroupBox *chartGroup;

    TableView  *bottomWidget2;

    QTimer timer;
    ChartWidget2 *chartWidget2;
    QScrollArea *pArea;

    TopWidget *topwidget;

};

#endif // AUTOPREPLAN_H
