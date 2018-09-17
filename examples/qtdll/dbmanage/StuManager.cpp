#include "StuManager.h"
#include "ui_StuManager.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include "../qdbmanage.h"
#include <QSqlQuery>
#include "QDebug"

StuManager::StuManager(QWidget *parent) : QWidget(parent), ui(new Ui::StuManager)
{
    ui->setupUi(this);
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(editClickedSlot(int,int)));
}

void StuManager::editClickedSlot(int x ,int y)
{
   emit mouseClicked(x);
}

StuManager::~StuManager()
{
    delete ui;
}

void StuManager::appendRowData(QStringList rowData)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    for(int i  = 0 ; i < rowData.size() ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }

    //ui->tableWidget->resizeRowsToContents();
    //ui->tableWidget->resizeColumnsToContents();
}


void StuManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList StuManager::getCurrentRowData()
{
    QStringList rowData;

    int iRow = -1;//行号
    int iCol = -1;//列号
    iRow = ui->tableWidget->currentRow();
    iCol = ui->tableWidget->columnCount();
    rowData.clear();
    int iLoop = 0;

    if( iRow != -1 )
    {
        for( iLoop = 0; iLoop < iCol; iLoop++ )
        {
            rowData << ui->tableWidget->item( iRow, iLoop )->text();
        }
    }

    return rowData;
}

QString StuManager::getCurrentID()
{
    QString ID ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID =  ui->tableWidget->item(row , 0)->text();
    }
    return ID;
}

//Show MainTable HeadInfo
void StuManager::ShowMainTableHead(QString stDBName,QString stTableName)
{
    QSqlQuery QMyquery;
    QStringList lstValue;
    bool bResult = false;
    int iColNum = 0;
    QString stSQL;
    stSQL =  QString( "select COLUMN_NAME,column_comment from INFORMATION_SCHEMA.Columns where table_name='%1' and table_schema='%2'" )
            .arg(stTableName).arg(stDBName);

    bResult = QMyquery.exec(stSQL);
    if( bResult )
    {
        while( QMyquery.next() )
        {
            lstValue<<QMyquery.value(1).toString();
        }
    }
    else
    {
        return;
    }

    //Set MainTable HeadInfo
    iColNum = lstValue.size();
    ui->tableWidget->setColumnCount(iColNum);
    ui->tableWidget->setHorizontalHeaderLabels(lstValue);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//
    //ui->tableWidget->resizeRowsToContents();
    //ui->tableWidget->resizeColumnsToContents();

}

QStringList StuManager::getRowData(int row)
{
    QStringList rowdata;
    int iLoop = 0;
    int iCol = 0;
    iCol = ui->tableWidget->columnCount();

    if(row != -1)
    {
        for( iLoop = 0; iLoop < iCol; iLoop++ )
        {
            rowdata << ui->tableWidget->item(row,iLoop)->text();
        }
    }

    return rowdata;
}

//获取列表表头信息
QString StuManager::GetHeadLabel()
{
    QString HeadInfo;
    HeadInfo.clear();
    QString stValue;
    int iLoop = 0;
    int iCount = 0;
    iCount = ui->tableWidget->horizontalHeader()->count();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        stValue = ui->tableWidget->horizontalHeaderItem(iLoop)->text();
        stValue = stValue + "\t";
        HeadInfo.append(stValue);
    }
    HeadInfo = HeadInfo+"\n";

    return HeadInfo;
}
