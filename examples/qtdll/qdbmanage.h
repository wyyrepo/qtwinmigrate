#ifndef QDBMANAGE_H
#define QDBMANAGE_H

#include <QWidget>
#include <QDialog>
#include "dbmanage/StuManager.h"
#include "dbmanage/TeacherManager.h"
#include "dbmanage/form.h"
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSqlQueryModel>

namespace Ui {
class QdbManage;
}

class QdbManage : public QWidget
{
    Q_OBJECT

public:
    explicit QdbManage(QWidget *parent = 0);
    ~QdbManage();

    StuManager *m_pTableWidget;
    TeacherManager *m_pTeacherManager;
    Form *m_pSearch;

    QTreeWidget *QtreeWidget;
    QHBoxLayout *pageWidget;
    QHBoxLayout *hLayout;

    QLabel    *totalPageLabel;
    QLabel    *currentPageLabel;    //当前页文本
    QLineEdit *switchPageLineEdit; //转到页输入框
    QPushButton *firstButton;      //第一页按钮
    QPushButton   *prevButton;      //前一页按钮
    QPushButton   *nextButton;      //下一页按钮
    QPushButton  *lastButton;       //最后一页
    QPushButton   *switchPageButton;    //转到页按钮
    int       currentPage=1;      //当前页
    int       totalPage;    //总页数
    int       totalRecrodCount;     //总记录数
    enum      {PageRecordCount = 5};//每页显示记录数

    QSqlQueryModel    *queryModel;       //查询模型

    //初始化数据库连接
    void initDB();
    void initUi();


    //AddByCL,20170925,Begin
    //Init Area TreeView
    void InitAreaTreeView( QTreeWidget * pTreeWidget, QString stTable_Type, QString stTable_List );
    //Init Area DaoHang
    void InitAreaDaoHang(QHBoxLayout * pHBoxDaoHang);
    //Init Area GongNeng
    void InitAreaGongNeng(QHBoxLayout * pHBoxDaoHang);
    //AddByCL,20170925,End

    QString stTable_CN;//表中文名
    QString stTable_EN;//表英文名

    //通过表中文名获取表英文名
    QString GetTable_ENFromCN(QString stTable_CN_In);

    int   GetTotalRecordCount(QString stTableName);
    int   GetPageCount();
    void  RecordQuery(QString stDBName, QString stTableName, int limitIndex);
    void  UpdateStatus();
    void  SetTotalPageLabel();


signals:

public slots:
   void TreeOP(QTreeWidgetItem *item, int column);

   void OnPrevButtonClick();          //前一页按钮按下
   void OnNextButtonClick();          //后一页按钮按下
   void OnSwitchPageButtonClick();   //转到页按钮按下
   void OnfirstButtonClick();        // 第一页按钮
   void OnlastButtonClick();        //最后一页

   void test(int );

   void newAdd();
   void onBtnEdit();
   void onBtnDel();
   void onBtnClear();
   void onBtnRefresh();
   void onBtnFind();
   void onBtnInput();
   void outBtnOutput();
   void onBtnTable();
   void onBtnClose();

   //快速搜索
   void onBtnSearch(QString stSQL);
   //条件搜索
   void onBtnConditionSearch(QString stSQL);

private:
    Ui::QdbManage *ui;
};

#endif // QDBMANAGE_H
