#include "qdbmanage.h"
#include "ui_qdbmanage.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QRegExp>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QGridLayout>
#include <QTreeWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QSplitter>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <QTreeWidget>
#include <QMessageBox>
#include <QFileDialog>
#include "qwinwidget.h"
#include "Common/styleinfo.h"

QdbManage::QdbManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QdbManage)
{
    initDB();  //打开数据库
    initUi();
    //initAddDlg();
    //setMinimumSize(1280,1024);
    showMaximized();
    QString qssFile = ":/qss/blue.css";
    StyleInfo::SetStyle(qssFile);
    ui->setupUi(this);
}

QdbManage::~QdbManage()
{
    //QMessageBox::about(NULL,"WARING","这是QT一个测试");
    delete ui;
}

//初始化数据库连接
void QdbManage::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.30.104");//192.168.84.137//
    db.setPort(3306);
    db.setDatabaseName("WXXH");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";
    }
    else
    {
        qDebug()<<db.databaseName();
    }
}

void QdbManage::initUi()
{
    m_pTableWidget = new StuManager;
    m_pTeacherManager = new TeacherManager;
    m_pSearch = new Form;

    QGridLayout *studentLayout = new QGridLayout;
    QtreeWidget = new QTreeWidget;

    pageWidget = new QHBoxLayout;
    hLayout = new QHBoxLayout;

    //Init Area TreeView
    InitAreaTreeView( QtreeWidget, "COMDB_TABLE_TYPE", "COMDB_TABLE_LIST" );
    //Init Area DaoHang
    InitAreaDaoHang(pageWidget);
    //Init Area GongNeng
    InitAreaGongNeng(hLayout);

    studentLayout->addWidget(QtreeWidget, 0,0,3,1);
    studentLayout->addWidget(m_pTableWidget, 0,1,1,2);
    studentLayout->addLayout(pageWidget, 1, 1, 1, 2);
    studentLayout->addWidget(m_pTeacherManager, 2, 1, 1, 2);
    studentLayout->addLayout(hLayout,3,0,1,3);

    studentLayout->setColumnStretch(1, 50);

    studentLayout->setRowStretch(0,20);
    studentLayout->setRowStretch(1,1);
    studentLayout->setRowStretch(2,3);
    studentLayout->setRowStretch(3,1);

    studentLayout->setRowMinimumHeight(2,1);

    setStyleSheet("QTabBar::tab{min-width:30ex; min-height:10ex;}");

    setLayout(studentLayout);
    setContentsMargins(5 , 10, 5 ,5);

    connect(m_pTableWidget,SIGNAL(mouseClicked(int)),this,SLOT(test(int)));
    connect(m_pSearch , SIGNAL(signalInfo(QString)) , this ,SLOT(onBtnSearch(QString)));
    connect(m_pSearch , SIGNAL(signalInfo1(QString)) , this ,SLOT(onBtnConditionSearch(QString)));
}


//AddByCL,20170925,Begin
//Init Area TreeView
void QdbManage::InitAreaTreeView( QTreeWidget * pTreeWidget, QString stTable_Type, QString stTable_List )
{
    //QtreeWidget = new QTreeWidget;
    pTreeWidget->header()->hide();

    //QTreeWidgetItem *root = new QTreeWidgetItem(QtreeWidget);
    //root->setText(0,"数据库结构树");

    QTreeWidgetItem *NodeMain = NULL;
    QTreeWidgetItem *NodeSub = NULL;

    QSqlQuery QMyqueryMain;
    QStringList lstValueMain;
    bool bResultMain = false;
    QString stSQLMain;
    QString stTypeNum;

    QSqlQuery QMyquerySub;
    QStringList lstValueSub;
    bool bResultSub = false;
    QString stSQLSub;

    stSQLMain =  QString( "select TYPENUM,TYPENAME from %1 " ).arg(stTable_Type);
    bResultMain = QMyqueryMain.exec(stSQLMain);
    if( bResultMain )
    {
        while( QMyqueryMain.next() )
        {
            NodeMain = new QTreeWidgetItem(QtreeWidget);//root
            NodeMain->setText(0, QMyqueryMain.value(1).toString());
            stTypeNum = QMyqueryMain.value(0).toString();

            stSQLSub =  QString( "select TABLENAME, TABLENAMEEN from %1 where TYPENUM = '%2'" ).arg(stTable_List).arg(stTypeNum);
            bResultSub = QMyquerySub.exec(stSQLSub);
            if( bResultSub )
            {
                while( QMyquerySub.next() )
                {
                    NodeSub = new QTreeWidgetItem(NodeMain);
                    NodeSub->setText(0, QMyquerySub.value(0).toString());
                }
            }

        }
    }
    else
    {
        return;
    }

    pTreeWidget->expandAll();
    pTreeWidget->addTopLevelItem(NodeMain);//root

    QGridLayout *studentLayout = new QGridLayout;
    studentLayout->addWidget(pTreeWidget, 0,0,2,1);

    QWidget *studentWidget = new QWidget;
    studentWidget->setLayout(studentLayout);

    //setCentralWidget(studentWidget);
    setContentsMargins(5, 10, 5 ,5);

    connect( pTreeWidget, &QTreeWidget::itemClicked, this, &QdbManage::TreeOP );
}

//Init Area DaoHang
void QdbManage::InitAreaDaoHang(QHBoxLayout * pHBoxDaoHang)
{
     firstButton = new QPushButton("第一页");
     prevButton = new QPushButton("前一页");
     nextButton = new QPushButton("下一页");
     lastButton = new QPushButton("最后一页");
     switchPageButton = new QPushButton("Go");
     switchPageLineEdit = new QLineEdit;
     switchPageLineEdit->setFixedWidth(20);
     QLabel *switchPage = new QLabel("转到");
     QLabel *page = new QLabel("页");
     totalPageLabel = new QLabel(this);
     currentPageLabel = new QLabel(this);

     pHBoxDaoHang->addWidget(firstButton);
     pHBoxDaoHang->addWidget(prevButton);
     pHBoxDaoHang->addWidget(nextButton);
     pHBoxDaoHang->addWidget(lastButton);
     pHBoxDaoHang->addWidget(switchPage);
     pHBoxDaoHang->addWidget(switchPageLineEdit);
     pHBoxDaoHang->addWidget(page);
     pHBoxDaoHang->addWidget(switchPageButton);
     pHBoxDaoHang->addWidget(new QSplitter());
     pHBoxDaoHang->addWidget(totalPageLabel);
     pHBoxDaoHang->addWidget(currentPageLabel);
     pHBoxDaoHang->addWidget(new QSplitter(this));

     connect(firstButton,SIGNAL(clicked()),this,SLOT(OnfirstButtonClick()));
     connect(prevButton,SIGNAL(clicked()),this,SLOT(OnPrevButtonClick()));
     connect(nextButton,SIGNAL(clicked()),this,SLOT(OnNextButtonClick()));
     connect(lastButton,SIGNAL(clicked()),this,SLOT(OnlastButtonClick()));
     connect(switchPageButton,SIGNAL(clicked()),this,SLOT(OnSwitchPageButtonClick()));

}

//Init Area GongNeng
void QdbManage::InitAreaGongNeng(QHBoxLayout * pHBoxDaoHang)
{
     QPushButton *btnAdd = new QPushButton;
     btnAdd->setText(tr("添加"));
     QPushButton *btnEdit = new QPushButton;
     btnEdit->setText(tr("修改"));
     QPushButton *btnDel = new QPushButton;
     btnDel->setText(tr("删除"));
     QPushButton *btnClear = new QPushButton;
     btnClear->setText(tr("清空"));
     QPushButton *btnRefresh = new QPushButton;
     btnRefresh->setText(tr("刷新"));
     QPushButton *btnSearch = new QPushButton;
     btnSearch->setText(tr("检索"));

     QPushButton *btnInput = new QPushButton;
     btnInput->setText(tr("导入"));
     QPushButton *btnOutput = new QPushButton;
     btnOutput->setText(tr("导出"));
     QPushButton *btnTable = new QPushButton;
     btnTable->setText(tr("报表"));
     QPushButton *btnQuit = new QPushButton;
     btnQuit->setText(tr("退出"));


     QWidget *widget = new QWidget;
     widget->setMinimumSize(20 ,50);
     widget->setContentsMargins(0,0,0,10);

   //  hLayout = new QHBoxLayout(widget);
   //  hLayout->addWidget(search1);
     pHBoxDaoHang->addWidget(btnAdd);
     pHBoxDaoHang->addWidget(btnEdit);
     pHBoxDaoHang->addWidget(btnDel);
     pHBoxDaoHang->addWidget(btnClear);
     pHBoxDaoHang->addWidget(btnSearch);
     pHBoxDaoHang->addWidget(btnRefresh);
     pHBoxDaoHang->addWidget(btnInput);
     pHBoxDaoHang->addWidget(btnOutput);
     pHBoxDaoHang->addWidget(btnTable);
     pHBoxDaoHang->addWidget(btnQuit);

     connect(btnAdd , SIGNAL(clicked(bool)) , this ,SLOT(newAdd()));
     connect(btnEdit , SIGNAL(clicked(bool)), this ,SLOT(onBtnEdit()));
     connect(btnDel , SIGNAL(clicked(bool)) ,this , SLOT(onBtnDel()));
     connect(btnClear , SIGNAL(clicked(bool)) ,this , SLOT(onBtnClear()));
     connect(btnRefresh,SIGNAL(clicked(bool)),this,SLOT(onBtnRefresh()));
     connect(btnSearch , SIGNAL(clicked(bool)) ,this , SLOT(onBtnFind()));
     connect(btnInput,SIGNAL(clicked(bool)),this,SLOT(onBtnInput()));
     connect(btnOutput , SIGNAL(clicked(bool)) , this ,SLOT(outBtnOutput()));
     connect(btnTable,SIGNAL(clicked(bool)),this,SLOT(onBtnTable()));
     connect(btnQuit,SIGNAL(clicked(bool)),this,SLOT(onBtnClose()));
}
//AddByCL,20170925,End

//通过表中文名获取表英文名
QString QdbManage::GetTable_ENFromCN(QString stTable_CN_In)
{
    QSqlQuery QMyquery;
    bool bResult = false;
    QString stSQL;
    QString stTable_EN_Out;

    stSQL =  QString( "select TABLENAMEEN from COMDB_TABLE_LIST where TABLENAME = '%1' " ).arg(stTable_CN_In);
    bResult = QMyquery.exec(stSQL);
    if( bResult )
    {
        if( QMyquery.size() != 1 )
        {
            stTable_EN_Out = "";
            return stTable_EN_Out;
        }

        while( QMyquery.next() )
        {
            stTable_EN_Out = QMyquery.value(0).toString();
        }
    }

    return stTable_EN_Out;
}

void QdbManage::TreeOP(QTreeWidgetItem *item, int column)
{
    //QString stTable_CN;//表中文名
    //QString stTable_EN;//表英文名

    stTable_CN = item->text(column);
    //通过表中文名获取表英文名
    stTable_EN = GetTable_ENFromCN(stTable_CN);

    int limitIndex = 0;
    //设置主表表头信息
    m_pTableWidget->ShowMainTableHead( "WXXH", stTable_EN );//"XHCJSY_CJCSXX"
    //填写主表表数据内容
    RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",

    //设置子表表头信息
    m_pTeacherManager->ShowSubTableHead( "WXXH", stTable_EN );
    //清空子表数据
    m_pTeacherManager->clearData();
}

//**********************************************************************
// 函数: RecordQuery
// 功能: 记录查询
//*********************************************************************
void QdbManage::RecordQuery(QString stDBName, QString stTableName, int limitIndex)
{
    queryModel = new QSqlQueryModel(this);
    totalRecrodCount = GetTotalRecordCount(stTableName);
    totalPage = GetPageCount();
    UpdateStatus();
    SetTotalPageLabel();
    QSqlQuery query;
   //currentPage = 1;
   // QString databasecc = QString("use WXXH");//"use cc"
   QString databasecc = QString("use %1").arg(stDBName);//"use cc"
   bool ok = query.exec(databasecc);
   if(ok)
   {
       QString szQuery = QString("select * from "+stTableName+" limit %1,%2").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount));
       queryModel->setQuery(szQuery);

       bool ok = query.exec(szQuery);
       if(ok)
       {
           m_pTableWidget->clearTableData();
           while (query.next())
           {
               QStringList rowData;

               int iLoop = 0;
               int iCount = 0;//记录列数
               iCount = query.record().count();
               for( iLoop = 0; iLoop < iCount; iLoop++ )
               {
                   rowData <<query.value(iLoop).toString();
               }

               m_pTableWidget->appendRowData(rowData);
           }
         }
   }
}

//**********************************************************************
// 函数: UpdateStatus
// 功能: 刷新状态
//*********************************************************************
void QdbManage::UpdateStatus()
{
    QString szCurrentText = QString("当前第%1页").arg(QString::number(currentPage));
    currentPageLabel->setText(szCurrentText);
     if(currentPage == 1)
     {
         prevButton->setEnabled(false);
         nextButton->setEnabled(true);
     }
     else if(currentPage == totalPage)
   {
     prevButton->setEnabled(true);
     nextButton->setEnabled(false);
    }
     else{
      prevButton->setEnabled(true);
      nextButton->setEnabled(true);
     }
      if(totalPage == 1){
         prevButton->setEnabled(false);
         nextButton->setEnabled(false);
     }
}

//**********************************************************************
// 函数: GetTotalRecordCount
// 功能: 得到记录数
//*********************************************************************
int QdbManage::GetTotalRecordCount(QString stTableName)
{
    //queryModel->setQuery("select * from " +tableName);
    queryModel->setQuery("select * from " +stTableName);
    qDebug() << queryModel->rowCount();
    return queryModel->rowCount();
}

//**********************************************************************
// 函数: GetPageCount
// 功能: 得到页数
//*********************************************************************
int QdbManage::GetPageCount()
{
   return (totalRecrodCount % PageRecordCount == 0) ? (totalRecrodCount / PageRecordCount) : (totalRecrodCount / PageRecordCount + 1);
}

//**********************************************************************
// 函数: SetTotalPageLabel
// 功能: 设置总数页文本
//*********************************************************************
void QdbManage::SetTotalPageLabel()
{
   QString szPageCountText = QString("总共%1页").arg(QString::number(totalPage));
   totalPageLabel->setText(szPageCountText);
}

//**********************************************************************
// 函数: OnfirstButtonClick
// 功能: 第一页按钮按下
//*********************************************************************
void QdbManage::OnfirstButtonClick()
{
    int limitIndex = 0;
    RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",
    currentPage = 1;
    UpdateStatus();
}

//**********************************************************************
// 函数: OnPrevButtonClick
// 功能: 前一页按钮按下
//*********************************************************************
void QdbManage::OnPrevButtonClick()
{
   int limitIndex = (currentPage - 2) * PageRecordCount;
   RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",
   currentPage -= 1;
   UpdateStatus();
}

//**********************************************************************
// 函数: OnNextButtonClick
// 功能: 后一页按钮按下
//*********************************************************************
void QdbManage::OnNextButtonClick()
{
   int limitIndex = currentPage * PageRecordCount;
   RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",
   currentPage += 1;
   UpdateStatus();
}

//**********************************************************************
// 函数: OnlastButtonClick
// 功能: 最后一页按钮按下
//*********************************************************************
void QdbManage::OnlastButtonClick(){
    int limitIndex = (totalPage - 1) * PageRecordCount;
    RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",
    currentPage = totalPage;
    UpdateStatus();
}

//**********************************************************************
// 函数: OnSwitchPageButtonClick
// 功能: 转到页按钮按下
//*********************************************************************
void QdbManage::OnSwitchPageButtonClick()
{
    QString szText = switchPageLineEdit->text();
    QRegExp regExp("-?[0-9]*");
     if(!regExp.exactMatch(szText))
   {
        QMessageBox::information(this,tr("提示"), tr("请输入数字"));
        return;
   }if(szText.isEmpty())
   {
        QMessageBox::information(this, tr("提示"),tr("请输入跳转页码"));
        return;
   }
    int pageIndex = szText.toInt();
    if(pageIndex > totalPage || pageIndex <1)
   {
        QMessageBox::information(this, tr("提示"),tr("重新输入"));
        return;
   }

   int limitIndex = (pageIndex-1) * PageRecordCount;
   RecordQuery( "WXXH", stTable_EN, limitIndex );//"", "",
   currentPage = pageIndex;
   UpdateStatus();

}

void QdbManage::test(int x)
{
   QStringList rowdata = m_pTableWidget->getRowData(x);
   m_pTeacherManager->setEitdData(rowdata);
}

//添加表数据记录
void QdbManage::newAdd()
{
  QStringList info = m_pTeacherManager->getData();
  if(info.isEmpty())
  {
    QMessageBox::information(this ,tr("提示") , tr("请输入数据!"));
  }
  else
  {
    QString stValue;
    QString stSQL;
    stSQL = " insert into "+stTable_EN+" values (";
    int iCount = 0;
    int iLoop = 0;
    iCount = info.size();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        stValue = info.at(iLoop);
        stValue = "\'" + stValue + "\',";
        stSQL.append(stValue);
    }
    stSQL = stSQL.left(stSQL.length()-1);
    stSQL = stSQL + ")";

    qDebug()<<stSQL;
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        int limitIndex = 0;
        RecordQuery( "WXXH", stTable_EN, limitIndex);
        QMessageBox::information(this ,tr("提示") , tr("添加成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("添加失败!"));
    }

    m_pTeacherManager->clearData();
  }
}

//修改记录数据
void QdbManage::onBtnEdit()
{
    //从子表获取要更新的数据记录,Begin
    QStringList rowData;
    int iCountData = 0;
    rowData = m_pTeacherManager->getData();
    iCountData = rowData.size();
    if(rowData.isEmpty())
    {
        QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
        return ;
    }
    //从子表获取要更新的数据记录,End

    //获取要更新表的英文字段信息,Begin
    QSqlQuery QqueryCol;
    QStringList lstValueCol;
    bool bResultCol = false;
    int iColNum = 0;
    QString stSQLCol;
    QString stDBName;
    stDBName = "WXXH";
    stSQLCol =  QString( "select COLUMN_NAME,column_comment from INFORMATION_SCHEMA.Columns where table_name='%1' and table_schema='%2'" )
            .arg(stTable_EN).arg(stDBName);

    bResultCol = QqueryCol.exec(stSQLCol);
    if( bResultCol )
    {
        while( QqueryCol.next() )
        {
            lstValueCol<<QqueryCol.value(0).toString();
        }
    }
    else
    {
        QMessageBox::information(this, tr("提示") , tr("修改记录数据失败!"));
        return;
    }

    iColNum = lstValueCol.size();
    if( iCountData != iColNum )
    {
        QMessageBox::information(this, tr("提示") , tr("修改记录数据失败!"));
        return;
    }
    //获取要更新表的英文字段信息,End

    //执行更新数据记录操作,Begin
    QString stValueCol;
    QString stValueData;
    QString stValue;
    QString stSQL;
    stSQL = " update "+stTable_EN+" set ";
    int iLoop = 0;
    for( iLoop = 1; iLoop < iCountData; iLoop++ )
    {
        stValueCol = lstValueCol.at(iLoop);
        stValueData = rowData.at(iLoop);
        stValueData = "\'" + stValueData + "\',";
        stValue = stValueCol + "=" + stValueData;
        stSQL.append(stValue);
    }
    stSQL = stSQL.left(stSQL.length()-1);
    stValueCol = lstValueCol.at(0);
    stValueData = rowData.at(0);
    stValueData = "\'" + stValueData + "\'" ;
    stSQL = stSQL + " where " + stValueCol + "=" + stValueData;

    qDebug()<<stSQL;
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        int limitIndex = 0;
        RecordQuery( "WXXH", stTable_EN, limitIndex);
        QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
    }
    //执行更新数据记录操作,End
}

//删除记录数据
void QdbManage::onBtnDel()
{
    //从主表获取要删除的数据记录,Begin
    QStringList rowData;
    int iCountData = 0;
    rowData = m_pTableWidget->getCurrentRowData();
    iCountData = rowData.size();
    if(rowData.isEmpty())
    {
        QMessageBox::information(this, tr("提示") , tr("请选中需要删除的数据!"));
        return ;
    }
    //从主表获取要删除的数据记录,End

    //确认删除操作,Begin
    QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
    if(button == QMessageBox::No)
    {
        //删除操作
        return;
    }
    //确认删除操作,End

    //获取要删除表的英文字段信息,Begin
    QSqlQuery QqueryCol;
    QStringList lstValueCol;
    bool bResultCol = false;
    int iColNum = 0;
    QString stSQLCol;
    QString stDBName;
    stDBName = "WXXH";
    stSQLCol =  QString( "select COLUMN_NAME,column_comment from INFORMATION_SCHEMA.Columns where table_name='%1' and table_schema='%2'" )
            .arg(stTable_EN).arg(stDBName);

    bResultCol = QqueryCol.exec(stSQLCol);
    if( bResultCol )
    {
        while( QqueryCol.next() )
        {
            lstValueCol<<QqueryCol.value(0).toString();
        }
    }
    else
    {
        QMessageBox::information(this, tr("提示") , tr("删除记录数据失败!"));
        return;
    }

    iColNum = lstValueCol.size();
    //获取要删除表的英文字段信息,End

    //执行删除数据记录操作,Begin
    QString stValueCol;
    QString stValueData;
    QString stSQL;
    stSQL = " delete from "+stTable_EN;
    stValueCol = lstValueCol.at(0);
    stValueData = rowData.at(0);
    stValueData = "\'" + stValueData + "\'" ;
    stSQL = stSQL + " where " + stValueCol + "=" + stValueData;

    qDebug()<<stSQL;
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        int limitIndex = 0;
        RecordQuery( "WXXH", stTable_EN, limitIndex);
        QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
    }
    //执行删除数据记录操作,End
}

//清空记录数据
void QdbManage::onBtnClear()
{
    //确认清空操作,Begin
    QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确认清空表记录？"));
    if(button == QMessageBox::No)
    {
        //清空操作
        return;
    }
    //确认清空操作,End

    //执行清空数据记录操作,Begin
    QString stSQL;
    stSQL = " delete from "+stTable_EN;

    qDebug()<<stSQL;
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        int limitIndex = 0;
        RecordQuery( "WXXH", stTable_EN, limitIndex);
        QMessageBox::information(this ,tr("提示") , tr("清空成功!"));
    }
    else
    {
        QMessageBox::information(this ,tr("提示") , tr("清空失败!"));
    }
    //执行清空数据记录操作,End
}

//刷新记录数据
void QdbManage::onBtnRefresh()
{
    int limitIndex = 0;
    RecordQuery( "WXXH", stTable_EN, limitIndex);
}

//查找记录数据
void QdbManage::onBtnFind()
{
    if(!m_pSearch->btnSearchIsClicked)
    {
        m_pSearch->stDBName = "WXXH";
        m_pSearch->stTableName = stTable_EN;
        m_pSearch->getTableField();
        m_pSearch->setcomboBox1();
        m_pSearch->setcomboBox2();
        m_pSearch->setcomboBox3();
        m_pSearch->activateWindow();
        m_pSearch->setWindowTitle(tr("检索数据"));
        m_pSearch->show();
        m_pSearch->btnSearchIsClicked = true;
    }
    else
    {
        m_pSearch->activateWindow();
        m_pSearch->setWindowTitle(tr("检索数据"));
        m_pSearch->show();
    }

}

//数据记录导入
void QdbManage::onBtnInput()
{
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,Begin
    QTextCodec *pCodec = QTextCodec::codecForName("UTF8");
    if(pCodec)
    {
        QTextCodec::setCodecForLocale(pCodec);
    }
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,End

    QString stTableName;
    QString stFileName;
    stTableName = stTable_EN;

    //选择导入文件,Begin
    stFileName =QFileDialog::getOpenFileName(this,"选择导入文件","","*.sql");
    if( stFileName.isEmpty() )
    {
        QMessageBox::information(this,"提示","未选择文件,导入失败!");
        return;
    }
    else
    {
        if(!stFileName.endsWith(".sql"))
        {
            stFileName+=".sql";
        }
    }
    //选择导入文件,End

    //打开文件对象,Begin
    QFile *file = NULL;
    file =new QFile(stFileName);
    if( file->open(QIODevice::ReadOnly |QIODevice::Text) == false )
    {
        QMessageBox::information(this,"提示","打开导入文件失败,导入失败!");
        return;
    }

    QTextStream  qts(file);
    qts.setCodec(pCodec);//此处设置UTF8文件编码方式存储数据可以避免sql文件中文乱码
    //打开文件对象,End

    //从文件读取SQL语句并执行,Begin
    QString stSQL;
    stSQL = qts.readAll();
    qDebug()<<stSQL;
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        QMessageBox::information(this,"提示","导入成功");
        int limitIndex = 0;
        RecordQuery( "WXXH", stTable_EN, limitIndex);
    }
    else
    {
        QMessageBox::information(this,"提示","导入失败");
    }
    //从文件读取SQL语句并执行,End

    //关闭文件对象,Begin
    file->close();
    delete file;
    file = NULL;
    //关闭文件对象,End
}

//数据记录导出
void QdbManage::outBtnOutput()
{
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,Begin
    QTextCodec *pCodec = QTextCodec::codecForName("UTF8");
    if(pCodec)
    {
        QTextCodec::setCodecForLocale(pCodec);
    }
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,End

    QString stTableName;
    QString stFileName;
    stTableName = stTable_EN;

    //选择导出文件,Begin
    stFileName =QFileDialog::getSaveFileName(this,"选择导出文件","","*.sql");
    if( stFileName.isEmpty() )
    {
        QMessageBox::information(this,"提示","未选择文件,导出失败!");
        return;
    }
    else
    {
        if(!stFileName.endsWith(".sql"))
        {
            stFileName+=".sql";
        }
    }
    //选择导出文件,End


    //打开文件对象,Begin
    QFile *file = NULL;
    file =new QFile(stFileName);
    if( file->open(QIODevice::WriteOnly |QIODevice::Text) == false )
    {
        QMessageBox::information(this,"提示","创建导出文件失败,导出失败!");
        return;
    }

    QTextStream  qts(file);
    qts.setCodec(pCodec);//此处设置UTF8文件编码方式存储数据可以避免sql文件中文乱码
 //   qts<<title;
    qts.flush();
    //打开文件对象,End

    //拼接InsertInto的SQL语句,Begin
    QString stValue;
    QString stSQL;
    QSqlQuery query(QString("SELECT * FROM %1").arg(stTableName));
    while(query.next())
    {
        stSQL = "insert into " + stTableName + " values(";

        int iLoop = 0;
        int iCount = 0;//记录列数
        QByteArray QBA;
        iCount = query.record().count();
        for( iLoop = 0; iLoop < iCount; iLoop++ )
        {
            stValue = query.value(iLoop).toString();
            QBA = stValue.toUtf8();
            //stValue = QString::fromUtf8(QBA);
            stSQL = stSQL + "\'" + stValue + "\',";
        }
        stSQL = stSQL.left(stSQL.length()-1);
        stSQL = stSQL+");\n";
        qDebug()<<stSQL;
        //把InsertInto的SQL语句写入文件
        qts<<stSQL;
    }
    //拼接InsertInto的SQL语句,End

    //关闭文件对象,Begin
    file->close();
    delete file;
    file = NULL;
    //关闭文件对象,End

    QMessageBox::information(this,"提示","导出成功");
}

//报表生成
void QdbManage::onBtnTable()
{
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,Begin
    QTextCodec *pCodec = QTextCodec::codecForName("UTF8");
    if(pCodec)
    {
        QTextCodec::setCodecForLocale(pCodec);
    }
    //此处设置UTF8文件编码方式存储数据可以避免中文乱码,End

    QString stTableName;
    QString stFileName;
    stTableName = stTable_EN;

    //选择导出文件,Begin
    stFileName =QFileDialog::getSaveFileName(this,"选择导出文件","","*.txt");
    if( stFileName.isEmpty() )
    {
        QMessageBox::information(this,"提示","未选择文件,报表生成失败!");
        return;
    }
    else
    {
        if(!stFileName.endsWith(".txt"))
        {
            stFileName+=".txt";
        }
    }
    //选择导出文件,End


    //打开文件对象,Begin
    QFile *file = NULL;
    file =new QFile(stFileName);
    if( file->open(QIODevice::WriteOnly |QIODevice::Text) == false )
    {
        QMessageBox::information(this,"提示","创建报表文件失败,报表生成失败!");
        return;
    }
    QTextStream  qts(file);
    qts.setCodec(pCodec);//此处设置UTF8文件编码方式存储数据可以避免sql文件中文乱码
    //写入报表文件头信息,Begin
    QString lstHeadInfo;
    lstHeadInfo.clear();
    lstHeadInfo = m_pTableWidget->GetHeadLabel();
    qts<<lstHeadInfo;
    //写入报表文件头信息,End
    qts.flush();
    //打开文件对象,End

    //写入表数据内容,Begin
    QString stValue;
    QString stTableInfo;
    QSqlQuery query(QString("SELECT * FROM %1").arg(stTableName));
    while(query.next())
    {
        int iLoop = 0;
        int iCount = 0;//记录列数
        stTableInfo.clear();
        iCount = query.record().count();
        for( iLoop = 0; iLoop < iCount; iLoop++ )
        {
            stValue = query.value(iLoop).toString();
            stTableInfo = stTableInfo + stValue + "\t";
        }
        stTableInfo = stTableInfo+"\n";
        qDebug()<<stTableInfo;
        //写入表数据内容
        qts<<stTableInfo;
    }
    //写入表数据内容,End

    //关闭文件对象,Begin
    file->close();
    delete file;
    file = NULL;
    //关闭文件对象,End

    QMessageBox::information(this,"提示","报表生成成功");

}

//退出
void QdbManage::onBtnClose()
{
    close();
}

//快速搜索
void QdbManage::onBtnSearch(QString stSQL)
{
   int limitIndex = 0;
   QString stDBName = "WXXH";
   queryModel = new QSqlQueryModel(this);
   QSqlQuery query;
   QString databasecc = QString("use %1").arg(stDBName);//"use cc"
   bool ok = query.exec(databasecc);
   if(ok)
   {
       QString szQuery = QString(stSQL+" limit %1,%2").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount));
       queryModel->setQuery(szQuery);

       bool ok = query.exec(szQuery);
       if(ok)
       {
           m_pTableWidget->clearTableData();
           while (query.next())
           {
               QStringList rowData;

               int iLoop = 0;
               int iCount = 0;//记录列数
               iCount = query.record().count();
               for( iLoop = 0; iLoop < iCount; iLoop++ )
               {
                   rowData <<query.value(iLoop).toString();
               }

               m_pTableWidget->appendRowData(rowData);
           }
         }
   }
}

//条件搜索
void QdbManage::onBtnConditionSearch(QString stSQL)
{
    int limitIndex = 0;
    QString stDBName = "WXXH";
    queryModel = new QSqlQueryModel(this);
    QSqlQuery query;
    QString databasecc = QString("use %1").arg(stDBName);//"use cc"
    bool ok = query.exec(databasecc);
    if(ok)
    {
        QString szQuery = QString(stSQL+" limit %1,%2").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount));
        queryModel->setQuery(szQuery);

        bool ok = query.exec(szQuery);
        if(ok)
        {
            m_pTableWidget->clearTableData();
            while (query.next())
            {
                QStringList rowData;

                int iLoop = 0;
                int iCount = 0;//记录列数
                iCount = query.record().count();
                for( iLoop = 0; iLoop < iCount; iLoop++ )
                {
                    rowData <<query.value(iLoop).toString();
                }

                m_pTableWidget->appendRowData(rowData);
            }
          }
    }
}
