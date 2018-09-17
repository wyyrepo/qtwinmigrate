#include "autopreplan.h"
#include "chartwidget2.h"
#include <QTime>
#include "constract.h"
#include <QScrollBar>
#include <QScrollArea>
#include "topwidget.h"


AutoPrePlan::AutoPrePlan(QWidget *parent) : QWidget(parent),
    bottomWidget2(new TableView)//抽屉
{
    maskType = 9;
    initRightWidget();
    initBottomWidget();
    initLayout();

    //connect(this, SIGNAL(clearLeftWidget()), leftWidget, SLOT(initWidget()));
    timer.start(100);  //刷新时间
    connect(&timer, SIGNAL(timeout()), this, SLOT(receiveTimeOut()));
    connect(this, SIGNAL(emitChart2Data(QList<qreal>)),
            chartWidget2, SLOT(receiveData(QList<qreal>)));

}


AutoPrePlan::~AutoPrePlan()
{

}

void AutoPrePlan::showWidget(int id)
{
//    leftLayout->removeWidget(leftWidget);
//    emit clearLeftWidget();
//    leftLayout->insertWidget(id + 1, leftWidget);
}

void AutoPrePlan::initRightWidget()  //图像显示
{
    topwidget = new TopWidget;


    chartGroup = new QGroupBox(tr("图形区"),this); //图像布局
    rightLayout = new QVBoxLayout;
    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *widget = new QWidget(this);

    pArea = new QScrollArea(widget);
    chartWidget2 = new ChartWidget2(pArea);

    pArea->setWidget(chartWidget2);
    pArea->setWidgetResizable(true);
    pArea->setAlignment(Qt::AlignCenter);
    pArea->setStyleSheet("background-color:black");
    pArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //隐藏时频图的滚动条
    //pArea->setVerticalScrollBar(scrollBar);

    layout->addWidget(pArea);
    //layout->addWidget(scrollBar);
    widget->setLayout(layout);
    widget->setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, PADDING, 0);    // 设置色卡的宽度

    widget->setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #0000ff,stop:0.25 #00ffff,stop:0.5 #00ff00,stop:0.75 #ffff00,stop:1.0 #ff0000)");
   // chartWidget1->setStyleSheet("background-color:black");
    rightLayout->addWidget(topwidget);

    rightLayout->addWidget(widget);
   // rightLayout->addWidget(widget1);
    rightLayout->setSpacing(0);
    rightLayout->setMargin(0);
    //rightLayout->setStretchFactor(widget, 4);
    //rightLayout->setStretchFactor(widget1,3);
    chartGroup->setLayout(rightLayout);


}

void AutoPrePlan::initBottomWidget()    //编辑表的信息
{

//   bottomwidget =new BottomWidget;

    bottomWidget2->setContextMenuPolicy(Qt::CustomContextMenu);
    // table_view->setSelectionMode(QAbstractItemView::MultiSelection);
    bottomWidget2->setSelectionMode(QAbstractItemView::SingleSelection);
  //  connect(maintableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
    QStringList header;

    header << tr("序号")<<tr("卫星信号类型") << tr("预案名称")<< tr("中频(MHZ)")<< tr("带宽(MHZ)") << tr("子信道数量") << tr("传输速率(Ksps)")<< tr("多普勒频移")<< tr("调制样式")<< tr("编码样式") << tr("生成时间")<<tr("预案文件路径");
    bottomWidget2->initHeader(header);
    QStringList dataList,dataList2;
    dataList << tr("1") << tr("QPSK") << tr("WGS卫星信号") << tr("2000") << tr("1000") << tr("100")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("2017-10-28 17:02")<< tr("C:\\WGS卫星信号数据");
    dataList2 << tr("2") << tr("FSK") << tr("WGS卫星信号") << tr("2000") << tr("1000") << tr("100")<< tr("100")<< tr("100")<< tr("QPSK")<< tr("QPSK")<< tr("2017-10-30 17:02")<< tr("C:\\WGS卫星信号数据");
    bottomWidget2->addRow(dataList);
    bottomWidget2->addRow(dataList2);
    bottomWidget2->setColumnWidth(0,80);
    bottomWidget2->setColumnWidth(1,125);
    bottomWidget2->setColumnWidth(2,125);
    bottomWidget2->setColumnWidth(3,125);
    bottomWidget2->setColumnWidth(4,125);
    bottomWidget2->setColumnWidth(5,125);
    bottomWidget2->setColumnWidth(6,125);
    bottomWidget2->setColumnWidth(7,125);
    bottomWidget2->setColumnWidth(8,125);
    bottomWidget2->setColumnWidth(9,125);
    bottomWidget2->setColumnWidth(10,125);
    bottomWidget2->setColumnWidth(11,160);
    bottomWidget2->setColumnWidth(12,125);

 }




void AutoPrePlan::initLayout()     //  AutoPreplan 的栏珊布局
{
    mainLayout = new QGridLayout;

    mainLayout->addWidget(topwidget,0,0,1,5);

    mainLayout->addWidget(chartGroup,1,0,3,5);

     mainLayout->addWidget(bottomWidget2,4,0,3,5);



    this->setLayout(mainLayout);
}



void AutoPrePlan::receiveTimeOut()   //随机点的生成，人工设置随机点的分布
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
