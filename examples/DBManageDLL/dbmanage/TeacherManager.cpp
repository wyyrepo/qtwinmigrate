#include "TeacherManager.h"
#include "ui_TeacherManager.h"
#include "../qdbmanage.h"
#include <QSqlQuery>
#include <QDebug>


TeacherManager::TeacherManager(QWidget *parent) : QWidget(parent), ui(new Ui::TeacherManager)
{
    ui->setupUi(this);
}

TeacherManager::~TeacherManager()
{
    delete ui;
}

//Show SubTable HeadInfo
void TeacherManager::ShowSubTableHead(QString stDBName,QString stTableName)
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
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(1);
//    ui->tableWidget->resizeRowsToContents();
//    ui->tableWidget->resizeColumnsToContents();

}

//add data;
QStringList TeacherManager::getData()
{
    QString stValue;
    QStringList addData;
    int iCount = 0;
    int iLoop = 0;
    iCount = ui->tableWidget->columnCount();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        stValue = ui->tableWidget->item(0,iLoop)->text();
        addData.append(stValue);
    }

    return addData;

//   // QStringList addInfo;
//  auto  addInfo1 = ui->tableWidget->item(0,0);
//  auto  addInfo2 = ui->tableWidget->item(0,1);
//  auto  addInfo3 = ui->tableWidget->item(0,2);
//  auto  addInfo4 = ui->tableWidget->item(0,3);
//  auto  addInfo5 = ui->tableWidget->item(0,4);
//  auto  addInfo6 = ui->tableWidget->item(0,5);
//    QStringList addData;
//  if(addInfo1==0||addInfo2==0||addInfo3==0||addInfo4==0||addInfo5==0||addInfo6==0){
//      return addData;
//  }
//     addData.append(addInfo1->text());
//     addData.append(addInfo2->text());
//     addData.append(addInfo3->text());
//     addData.append(addInfo4->text());
//     addData.append(addInfo5->text());
//     addData.append(addInfo6->text());

//     return addData;
// // }
}

QStringList TeacherManager::getEitdData(){

    QStringList rowdata = m_pTableWidget->getCurrentRowData();
    int iLoop = 0;
    int iCount = 0;
    iCount = rowdata.size();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        ui->tableWidget->item(0,iLoop)->setText(rowdata.at(iLoop));
    }

    return rowdata;
}

void TeacherManager::clearData(){
    //ui->tableWidget->clear();

    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }

}

QStringList TeacherManager::setEitdData( QStringList rowdata )
{
    //插入空行,Begin
    int row = ui->tableWidget->rowCount();
    if( row == 0 )
    {
        ui->tableWidget->insertRow(row);
    }
    //插入空行,End

    //插入数据,Begin
    int iLoop = 0;
    int iCount = 0;
    iCount = rowdata.size();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        //ui->tableWidget->item(0,iLoop)->setText(rowdata.at(iLoop));
        ui->tableWidget->setItem(0 , iLoop ,new QTableWidgetItem(rowdata.at(iLoop)));
    }
    //插入数据,End

    //ui->tableWidget->resizeRowsToContents();
    //ui->tableWidget->resizeColumnsToContents();

    return rowdata;
}

