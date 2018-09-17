#include "handpreplan.h"

#include "chartwidget2.h"
#include <QTime>
#include "constract.h"
#include <QScrollBar>
#include <QScrollArea>
#include <preplangenerate/gatherinfotab.h>
#include <QTabWidget>
#include <QGroupBox>
#include <QDebug>




HandPrePlan::HandPrePlan(QWidget *parent) : QWidget(parent)
{

    initTopWidget();
    resultInfoWidget();
    preInfoWidget();
    tableInfoWidget();





    timer.start(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(receiveTimeOut()));
    connect(this, SIGNAL(emitChart2Data(QList<qreal>)),
            chartWidget2, SLOT(receiveData(QList<qreal>)));

    allLayout();

}




void HandPrePlan::initTopWidget()  //图像显示
{

    chartGroup = new QGroupBox(tr("图形区"),this); //图像布局
    rightLayout = new QVBoxLayout;

//    handgroupbox =new HandGroupBox();

    QHBoxLayout *layout = new QHBoxLayout;
    //    QHBoxLayout *layout1 = new QHBoxLayout;
    QWidget *widget = new QWidget(this);
    //    QWidget *widget1 = new QWidget(this);
    //QScrollBar *scrollBar = new QScrollBar(widget);

    //    chartWidget1 = new ChartWidget1(widget1);
    //    chartWidget1->setMinimumSize(400, 100);

    pArea = new QScrollArea(widget);
    chartWidget2 = new ChartWidget2(pArea);

    pArea->setWidget(chartWidget2);
    pArea->setWidgetResizable(true);
    pArea->setAlignment(Qt::AlignCenter);
    pArea->setStyleSheet("background-color:black");
    pArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //  隐藏时频图的滚动条
    //pArea->setVerticalScrollBar(scrollBar);

    layout->addWidget(pArea);
    //layout->addWidget(scrollBar);
    widget->setLayout(layout);
    widget->setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, PADDING, 0);    // 设置色卡的宽度

    //    layout1->addWidget(chartWidget1);
    //    widget1->setLayout(layout1);
    //    widget1->setContentsMargins(0, 0, 0, 0);
    /* layout1->setContentsMargins(0, 0, 0, 0); */    //设置时频图的右侧边距

    // widget->setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 blue,stop:0.3 green,stop:0.6 yellow,stop:1.0 red)");
    widget->setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #0000ff,stop:0.25 #00ffff,stop:0.5 #00ff00,stop:0.75 #ffff00,stop:1.0 #ff0000)");
    //    chartWidget1->setStyleSheet("background-color:black");
    rightLayout->addWidget(widget);
    //    rightLayout->addWidget(widget1);
    rightLayout->setSpacing(0);
    rightLayout->setMargin(0);
    rightLayout->setStretchFactor(widget, 4);
    //    rightLayout->setStretchFactor(widget1,3);
    chartGroup->setLayout(rightLayout);
}





HandPrePlan::~HandPrePlan()
{

}

void HandPrePlan::resultInfoWidget()
{
    resultGroup = new QGroupBox(tr("信号分析结果"),this);
    layout1 =new QHBoxLayout;


    checkbox1 = new QCheckBox;
    label1 =new QLabel(tr("卫星信号类型"));
    combox1 =new QComboBox;
    combox1->addItem("WGS卫星");
    combox1->addItem("UFO卫星");
    combox1->addItem("INSTAT卫星");
    combox1->addItem("海事卫星");
    combox1->addItem("图莱雅");
    combox1->addItem("铱星");

    checkbox2 = new QCheckBox;
    label2 =new QLabel(tr("中频"));
    lineedit1 = new QLineEdit(tr("500"));
    lineedit1->setFixedWidth(40);
    label3 =new QLabel(tr("MHz"));

    checkbox3 = new QCheckBox;
    label4 =new QLabel(tr("带宽"));
    lineedit2 = new  QLineEdit(tr("3"));
    lineedit2->setFixedWidth(40);
    label5 =new QLabel(tr("MHz"));

    checkbox4 = new QCheckBox;
    label6 =new QLabel(tr("传输速率"));
    lineedit3 = new QLineEdit(tr("3000"));
    lineedit3->setFixedWidth(40);

    layout1->addWidget(checkbox1);
    layout1->addWidget(label1);
    layout1->addWidget(combox1);
    layout1->addWidget(checkbox2);
    layout1->addWidget(label2);
    layout1->addWidget(lineedit1);
    layout1->addWidget(label3);
    layout1->addWidget(checkbox3);
    layout1->addWidget(label4);
    layout1->addWidget(lineedit2);
    layout1->addWidget(label5);
    layout1->addWidget(checkbox4);
    layout1->addWidget(label6);
    layout1->addWidget(lineedit3);

    checkbox3 = new QCheckBox;
    checkbox4 = new QCheckBox;
    checkbox5 = new QCheckBox;
    checkbox6 = new QCheckBox;
    checkbox5 = new QCheckBox;
    label7 =new QLabel(tr("调制样式"));
    QComboBox *combox2 =new QComboBox();
    combox2->addItem("BPSK");
    combox2->addItem("QPSK");
    combox2->addItem("OQPSK");
    combox2->addItem("8PSK");
    combox2->addItem("16QAM");

    checkbox6 = new QCheckBox;
    label8 =new QLabel(tr("编码样式"));
    QComboBox *combox3 =new QComboBox();
    combox3->addItem("RS");
    combox3->addItem("卷积");
    combox3->addItem("级联码");
    combox3->addItem("TURBO");
    combox3->addItem("LDPC");

    bottom1 =new QPushButton(tr("检索"));
    bottom2 =new QPushButton(tr("启动播放"));
    bottom3 =new QPushButton(tr("暂停播放"));


    layout1->addWidget(checkbox5);
    layout1->addWidget(label7);
    layout1->addWidget(combox2);
    layout1->addWidget(checkbox6);
    layout1->addWidget(label8);
    layout1->addWidget(combox3);
    layout1->addWidget(bottom1);
    layout1->addWidget(bottom2);
    layout1->addWidget(bottom3);
    layout1->addStretch();




    bottomWidget3 =new TableView;

    bottomWidget3->setContextMenuPolicy(Qt::CustomContextMenu);
    // table_view->setSelectionMode(QAbstractItemView::MultiSelection);
    bottomWidget3->setSelectionMode(QAbstractItemView::SingleSelection);
    //  connect(maintableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
    QStringList header;

    header << tr("序号")<<tr("卫星信号类型") << tr("预案名称")<< tr("中频(MHZ)")<< tr("带宽(MHZ)") << tr("传输速率(Ksps)")<< tr("多普勒频移")<< tr("调制样式")<< tr("编码样式") << tr("采集数据地址")<<tr("采集时间");
    bottomWidget3->initHeader(header);
    QStringList dataList,dataList2;
    dataList << tr("1") << tr("QPSK") << tr("WGS卫星信号") << tr("2000") << tr("1000")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("C:\\WGS卫星信号数据")<< tr("2017-10-28 17:02");
    dataList2 << tr("2") << tr("FSK") << tr("WGS卫星信号") << tr("2000") << tr("1000")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("C:\\WGS卫星信号数据")<< tr("2017-10-30 17:02");
    bottomWidget3->addRow(dataList);
    bottomWidget3->addRow(dataList2);
    bottomWidget3->setColumnWidth(0,80);
    bottomWidget3->setColumnWidth(1,125);
    bottomWidget3->setColumnWidth(2,125);
    bottomWidget3->setColumnWidth(3,125);
    bottomWidget3->setColumnWidth(4,125);
    bottomWidget3->setColumnWidth(5,125);
    bottomWidget3->setColumnWidth(6,125);
    bottomWidget3->setColumnWidth(7,125);
    bottomWidget3->setColumnWidth(8,125);
    bottomWidget3->setColumnWidth(9,125);
    bottomWidget3->setColumnWidth(10,125);
    bottomWidget3->setColumnWidth(11,160);



    layout3 =new QHBoxLayout;
    layout3->addWidget(bottomWidget3);

    layout2 =new QVBoxLayout;
    layout2->addLayout(layout1);
    layout2->addLayout(layout3);


    resultGroup->setLayout(layout2);


}



void HandPrePlan::preInfoWidget()
{
    preInfoGroup = new QGroupBox(tr("预案数据生成"),this);
    QHBoxLayout *layout =new QHBoxLayout;
    QLabel *label1 =new QLabel(tr("频段："));
    QLineEdit *edit1 =new QLineEdit(tr("500"));
    QLabel *label2 =new QLabel(tr("---"));
    QLineEdit *edit2 =new QLineEdit(tr("800"));
    QLabel *label5 =new QLabel(tr("MHz"));

    QLabel *label3 =new QLabel(tr("时段："));
    QLineEdit *edit3 =new QLineEdit(tr("2017/10/30 9:12:23"));
    QLabel *label4 =new QLabel(tr("---"));
    QLineEdit *edit4 =new QLineEdit(tr("2017/10/30 9:40:23"));

    QPushButton *bottom =new QPushButton(tr("生成预案"));

    layout->addWidget(label1);
    layout->addWidget(edit1);
    layout->addWidget(label2);
    layout->addWidget(edit2);
    layout->addWidget(label5);
    layout->addWidget(label3);
    layout->addWidget(edit3);
    layout->addWidget(label4);
    layout->addWidget(edit4);
    layout->addWidget(bottom);

    preInfoGroup->setLayout(layout);
}

void HandPrePlan::tableInfoWidget()
{
    bottomWidget4 =new TableView;

    bottomWidget4->setContextMenuPolicy(Qt::CustomContextMenu);
    // table_view->setSelectionMode(QAbstractItemView::MultiSelection);
    bottomWidget4->setSelectionMode(QAbstractItemView::SingleSelection);
    //  connect(maintableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
    QStringList header;

    header << tr("序号")<<tr("卫星信号类型") << tr("预案名称")<< tr("中频(MHZ)")<< tr("带宽(MHZ)")<< tr("子信道数量") << tr("传输速率(Ksps)")<< tr("多普勒频移")<< tr("调制样式")<< tr("编码样式") << tr("采集数据地址")<<tr("采集时间");
    bottomWidget4->initHeader(header);
    QStringList dataList,dataList2;
    dataList << tr("1") << tr("QPSK") << tr("WGS卫星信号") << tr("2000") << tr("1000")<< tr("100")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("C:\\WGS卫星信号数据")<< tr("2017-10-28 17:02");
    dataList2 << tr("2") << tr("FSK") << tr("WGS卫星信号") << tr("2000") << tr("1000")<< tr("100")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("C:\\WGS卫星信号数据")<< tr("2017-10-30 17:02");
    bottomWidget4->addRow(dataList);
    bottomWidget4->addRow(dataList2);
    bottomWidget4->setColumnWidth(0,80);
    bottomWidget4->setColumnWidth(1,125);
    bottomWidget4->setColumnWidth(2,125);
    bottomWidget4->setColumnWidth(3,125);
    bottomWidget4->setColumnWidth(4,125);
    bottomWidget4->setColumnWidth(5,125);
    bottomWidget4->setColumnWidth(6,125);
    bottomWidget4->setColumnWidth(7,125);
    bottomWidget4->setColumnWidth(8,125);
    bottomWidget4->setColumnWidth(9,125);
    bottomWidget4->setColumnWidth(10,125);
    bottomWidget4->setColumnWidth(11,125);
    bottomWidget4->setColumnWidth(12,160);





}

void HandPrePlan::receiveTimeOut()   //随机点的生成，人工设置随机点的分布
{
    QTime t;
    QList<qreal> tmpData;

    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    qreal randNum;
    QList<qreal> nums;
    for (int i = 0; i < 50; i++) {
        qreal num = qrand() % FRAME_MAX;
        nums.append(num);
    }

    for (int i = 0; i < FRAME_MAX; i++) {
        if (nums.contains(i)) {
            randNum = qrand() % FREQ_MAX;
        } else {
            randNum = qrand() % FREQ_MIDDLE;
        }
        tmpData.append(randNum);
    }

    emit emitChart1Data(tmpData);
    emit emitChart2Data(tmpData);
}



void HandPrePlan::allLayout()
{
    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(resultGroup);
    mainLayout->addWidget(chartGroup);
    mainLayout->addWidget(preInfoGroup);
    mainLayout->addWidget(bottomWidget4);

    this->setLayout(mainLayout);
}

void HandPrePlan::receiveConnectClick( QString ServerIP, int ServerPort, char WorkMode, int &iRandomPort )
{
    qDebug() << "receive connect click";
    //tcpSocket->CreateClient(ServerIP, ServerPort, WorkMode, iRandomPort);
}

void HandPrePlan::receiveDisconnectClick()
{
    //tcpSocket->CloseClient();
}


