#ifndef HANDPREPLAN_H
#define HANDPREPLAN_H
#include <QWidget>
#include <QTimer>

#include "chartwidget2.h"
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableView>
#include "gatherinfotab.h"
#include "preinfotab.h"
#include <QHBoxLayout>
//#include "tableview.h"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include "tableview.h"
//#include <QTableView>


class QTabWidget;

class HandPrePlan : public QWidget
{
    Q_OBJECT
public:
    explicit HandPrePlan(QWidget *parent = 0);
    ~HandPrePlan();

signals:

    void emitChart1Data(const QList<qreal> &data);
    void emitChart2Data(const QList<qreal> &data);


public slots:

private slots:

    void receiveTimeOut();
    void receiveConnectClick( QString ServerIP, int ServerPort, char WorkMode, int &iRandomPort );
    void receiveDisconnectClick();

private:


    void initTopWidget();
    void allLayout();
    void resultInfoWidget();
    void preInfoWidget();
    void tableInfoWidget();

    QTimer timer;
    ChartWidget2 *chartWidget2;
    QScrollArea *pArea;

    QCheckBox *checkbox1;
    QCheckBox *checkbox2;
    QCheckBox *checkbox3;
    QCheckBox *checkbox4;
    QCheckBox *checkbox5;
    QCheckBox *checkbox6;


    QVBoxLayout *leftLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *layout1;
    QVBoxLayout *layout2;
    QHBoxLayout *layout3;

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLabel *label8;

    QLineEdit *lineedit1;
    QLineEdit *lineedit2;
    QLineEdit *lineedit3;


    QComboBox *combox1;
    QPushButton *bottom1;
    QPushButton *bottom2;
    QPushButton *bottom3;

    TableView  *bottomWidget3;
    TableView  *bottomWidget4;

    QSignalMapper *signalMapper;
    QGroupBox *chartGroup;
    QGroupBox *resultGroup;
    QGroupBox *preInfoGroup;



    QTabWidget *tabWidget;
    GatherInfoTab *gatherInfoTab;
    PreInfoTab *preInfoTab;

    QGroupBox *groupBox;

    //publicsocket *tcpSocket;
};

#endif // HANDPREPLAN_H
