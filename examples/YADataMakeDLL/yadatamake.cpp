#include "yadatamake.h"
#include "ui_yadatamake.h"
#include <QVBoxLayout>
#include "api/myhelper.h"
#include "help/helpinfo.h"

YADataMake::YADataMake(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YADataMake)
{
    tabWidget = new QTabWidget(this);

    autoPrePlanTab = new AutoPrePlan(tabWidget);
    tabWidget->addTab(autoPrePlanTab, tr("参数预案生成"));

    handPrePlanTab = new HandPrePlan(tabWidget);
    tabWidget->addTab(handPrePlanTab, tr("人工预案生成"));

    QHBoxLayout *layout=new QHBoxLayout();
    layout->addWidget(tabWidget);
    setLayout(layout);

    //blue.css
    //setWindowTitle("采集数据导入导出软件");
    this->setWindowIcon(QIcon(":/sysButton/titleicon.png"));
    this->setWindowIcon(QIcon());
    QString qssFile = ":/qss/blue.css";
    myHelper::SetStyle(qssFile);

    setMinimumSize(1280,1024);

    showMaximized();

    ui->setupUi(this);
}

YADataMake::~YADataMake()
{
    delete ui;
}
