#include "form.h"
#include "ui_form.h"
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QCloseEvent>


Form::Form(QWidget *parent) :QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
  // setGeometry(deskTopRect);
   // setFixedSize(430,300);
    btnSearchIsClicked = false;
    btnFormQuickSearchIsClicked = false;
    btnFormSearchIsClicked = false;
    btnCheckBoxClicked = false;
}

void Form::setcomboBox1()
{
    QStringList comboBox;
    comboBox.append("");

    for(int i = 0;i <= stlstNameCN.length()-1;i++)
    {
        comboBox.append(stlstNameCN.at(i));
    }

    ui->searchCondition1->addItems(comboBox);
    ui->searchCondition2->addItems(comboBox);
    ui->searchCondition3->addItems(comboBox);
    ui->searchCondition4->addItems(comboBox);
    ui->searchCondition5->addItems(comboBox);
    ui->searchCondition6->addItems(comboBox);
}

void Form::setcomboBox2()
{
    QStringList condition;
    condition.append("");
    condition.append(">");
    condition.append("=");
    condition.append("<");
    ui->compareCond1->addItems(condition);
    ui->compareCond2->addItems(condition);
    ui->compareCond3->addItems(condition);
    ui->compareCond4->addItems(condition);
    ui->compareCond5->addItems(condition);
    ui->compareCond6->addItems(condition);
}

void Form::setcomboBox3()
{
    QStringList condition;
    condition.append("");
    condition.append("and");
    condition.append("or");
    ui->fuzzyQuery1->addItems(condition);
    ui->fuzzyQuery2->addItems(condition);
    ui->fuzzyQuery3->addItems(condition);
    ui->fuzzyQuery4->addItems(condition);
    ui->fuzzyQuery5->addItems(condition);
    connect(ui->checkBox,SIGNAL(clicked(bool)),SLOT(judge()));
}

Form::~Form()
{
    delete ui;
}

void Form::judge()
{
    if(ui->checkBox->checkState() == Qt::Checked)
    {
      ui->compareCond1->setEnabled(false);
      ui->compareCond1->setCurrentText(tr(""));
      ui->compareCond2->setEnabled(false);
      ui->compareCond2->setCurrentText(tr(""));
      ui->compareCond3->setEnabled(false);
      ui->compareCond3->setCurrentText(tr(""));
      ui->compareCond4->setEnabled(false);
      ui->compareCond4->setCurrentText(tr(""));
      ui->compareCond5->setEnabled(false);
      ui->compareCond5->setCurrentText(tr(""));
      ui->compareCond6->setEnabled(false);
      ui->compareCond6->setCurrentText(tr(""));
      btnCheckBoxClicked = true;
    }

    if(ui->checkBox->checkState() == Qt::Unchecked)
    {
       ui->compareCond1->setEnabled(true);
       ui->compareCond2->setEnabled(true);
       ui->compareCond3->setEnabled(true);
       ui->compareCond4->setEnabled(true);
       ui->compareCond5->setEnabled(true);
       ui->compareCond6->setEnabled(true);
       btnCheckBoxClicked = false;
   }
}

void Form::setQueryData()
{
}

void Form::getTableField()
{
    lstField.clear();
    stlstNameEN.clear();
    stlstNameCN.clear();
    FIELDNAME stcFieldName;

    QString stSQL;
    stSQL = QString("select  column_comment, COLUMN_NAME from INFORMATION_SCHEMA.Columns where table_name='%1' and table_schema='%2';").arg(stTableName).arg(stDBName);
    QSqlQuery query;
    bool ok = query.exec(stSQL);
    if(ok)
    {
        while(query.next())
        {
            stcFieldName.stName_CN = query.value(0).toString();
            stcFieldName.stName_EN = query.value(1).toString();
            stlstNameCN<<stcFieldName.stName_CN;
            stlstNameEN<<stcFieldName.stName_EN;
            lstField.append(stcFieldName);
        }
    }

}


void Form::on_setQueryData_clicked()
{
   QString stSQL;
   QString stValue;

   QString searchCondition1 = ui->searchCondition1->currentText();
   searchCondition1 = TranFieldNameFromCNToEN(searchCondition1);
   QString searchCondition2 = ui->searchCondition2->currentText();
   searchCondition2 = TranFieldNameFromCNToEN(searchCondition2);
   QString searchCondition3 = ui->searchCondition3->currentText();
   searchCondition3 = TranFieldNameFromCNToEN(searchCondition3);
   QString searchCondition4 = ui->searchCondition4->currentText();
   searchCondition4 = TranFieldNameFromCNToEN(searchCondition4);
   QString searchCondition5 = ui->searchCondition5->currentText();
   searchCondition5 = TranFieldNameFromCNToEN(searchCondition5);
   QString searchCondition6 = ui->searchCondition6->currentText();
   searchCondition6 = TranFieldNameFromCNToEN(searchCondition6);

   QString compareCond1 = ui->compareCond1->currentText();
   QString compareCond2 = ui->compareCond2->currentText();
   QString compareCond3 = ui->compareCond3->currentText();
   QString compareCond4 = ui->compareCond4->currentText();
   QString compareCond5 = ui->compareCond5->currentText();
   QString compareCond6 = ui->compareCond6->currentText();

   QString fuzzyQuery1 = ui->fuzzyQuery1->currentText();
   QString fuzzyQuery2 = ui->fuzzyQuery2->currentText();
   QString fuzzyQuery3 = ui->fuzzyQuery3->currentText();
   QString fuzzyQuery4 = ui->fuzzyQuery4->currentText();
   QString fuzzyQuery5 = ui->fuzzyQuery5->currentText();

    QString inputData1 = ui->inputData1->text();
    QString inputData2 = ui->inputData2->text();
    QString inputData3 = ui->inputData3->text();
    QString inputData4 = ui->inputData4->text();
    QString inputData5 = ui->inputData5->text();
    QString inputData6 = ui->inputData6->text();

    stSQL = "select * from " + stTableName + " where ";
    if( compareCond1.isEmpty() )
    {
        stValue = searchCondition1 + " like \'%" + inputData1 + "%\' ";
    }
    else
    {
        stValue = searchCondition1 + compareCond1 + " \'" + inputData1 + "\' ";
    }
    stSQL = stSQL+stValue;

    stValue.clear();
    if( fuzzyQuery1.isEmpty() )
    {
        emit signalInfo1(stSQL);
        return;
    }
    else
    {
        stValue = fuzzyQuery1 + " ";
    }
    if( compareCond2.isEmpty() )
    {
        stValue += searchCondition2 + " like \'%" + inputData2 + "%\' ";
    }
    else
    {
        stValue += searchCondition2 + " " + compareCond2 + " \'" + inputData2 + "\' ";
    }
    stSQL = stSQL+stValue;

    stValue.clear();
    if( fuzzyQuery2.isEmpty() )
    {
        emit signalInfo1(stSQL);
        return;
    }
    else
    {
        stValue = fuzzyQuery2 + " ";
    }
    if( compareCond3.isEmpty() )
    {
        stValue += searchCondition3 + " like \'%" + inputData3 + "%\' ";
    }
    else
    {
        stValue += searchCondition3 + " " + compareCond3 + " \'" + inputData3 + "\' ";
    }
    stSQL = stSQL+stValue;

    stValue.clear();
    if( fuzzyQuery3.isEmpty() )
    {
        emit signalInfo1(stSQL);
        return;
    }
    else
    {
        stValue = fuzzyQuery3 + " ";
    }
    if( compareCond4.isEmpty() )
    {
        stValue += searchCondition4 + " like \'%" + inputData4 + "%\' ";
    }
    else
    {
        stValue += searchCondition4 + " " + compareCond4 + " \'" + inputData4 + "\' ";
    }
    stSQL = stSQL+stValue;

    stValue.clear();
    if( fuzzyQuery4.isEmpty() )
    {
        emit signalInfo1(stSQL);
        return;
    }
    else
    {
        stValue = fuzzyQuery4 + " ";
    }
    if( compareCond5.isEmpty() )
    {
        stValue += searchCondition5 + " like \'%" + inputData5 + "%\' ";
    }
    else
    {
        stValue += searchCondition5 + " " + compareCond5 + " \'" + inputData5 + "\' ";
    }
    stSQL = stSQL+stValue;

    stValue.clear();
    if( fuzzyQuery5.isEmpty() )
    {
        emit signalInfo1(stSQL);
        return;
    }
    else
    {
        stValue = fuzzyQuery5 + " ";
    }
    if( compareCond6.isEmpty() )
    {
        stValue += searchCondition6 + " like \'%" + inputData6 + "%\' ";
    }
    else
    {
        stValue += searchCondition6 + " " + compareCond6 + " \'" + inputData6 + "\' ";
    }
    stSQL = stSQL+stValue;

    qDebug()<<stSQL;

    emit signalInfo1(stSQL);
}

void Form::dataClear()
{
    ui->quickSearch->clear();
    ui->searchCondition1->clear();
    ui->searchCondition2->clear();
    ui->searchCondition3->clear();
    ui->searchCondition4->clear();
    ui->searchCondition5->clear();
    ui->searchCondition6->clear();

    ui->compareCond1->clear();
    ui->compareCond2->clear();
    ui->compareCond3->clear();
    ui->compareCond4->clear();
    ui->compareCond5->clear();
    ui->compareCond6->clear();

    ui->fuzzyQuery1->clear();
    ui->fuzzyQuery2->clear();
    ui->fuzzyQuery3->clear();
    ui->fuzzyQuery4->clear();
    ui->fuzzyQuery5->clear();

    ui->inputData1->clear();
    ui->inputData2->clear();
    ui->inputData3->clear();
    ui->inputData4->clear();
    ui->inputData5->clear();
    ui->inputData6->clear();
}

void Form::on_pushButton_3_clicked()
{
//    dataClear();
//    btnSearchIsClicked = false;
//    btnFormQuickSearchIsClicked = false;
//    btnFormSearchIsClicked = false;
//    ui->checkBox->setChecked(false);
    close();
}

void Form::closeEvent(QCloseEvent *event)
{
    dataClear();
    btnSearchIsClicked = false;
    btnFormQuickSearchIsClicked = false;
    btnFormSearchIsClicked = false;
    ui->checkBox->setChecked(false);
    event->accept();
}

void Form::on_quickSerchButton_clicked()
{
    QString stSQL;
    QString stValue;
    QString qsearch = ui->quickSearch->text();
    stSQL = "select * from " + stTableName + " where ";
    int iLoop = 0;
    int iCount = 0;
    iCount = stlstNameEN.size();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        stValue = stlstNameEN.at(iLoop);
        stValue += " like \'%" + qsearch + "%\' or ";
        stSQL += stValue;
    }
    stSQL = stSQL.left(stSQL.length()-4);

    qDebug()<<stSQL;

    emit signalInfo(stSQL);
}

QString Form::TranFieldNameFromCNToEN(QString stNameCN)
{
    QString stNameEN;
    FIELDNAME stcFieldName;
    int iLoop = 0;
    int iCount = 0;
    iCount = lstField.size();
    for( iLoop = 0; iLoop < iCount; iLoop++ )
    {
        stcFieldName = lstField.at(iLoop);
        if( stNameCN.compare(stcFieldName.stName_CN) == 0 )
        {
            stNameEN = stcFieldName.stName_EN;
            break;
        }
    }

    return stNameEN;
}

