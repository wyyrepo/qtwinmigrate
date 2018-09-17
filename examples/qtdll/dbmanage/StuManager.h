#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

namespace Ui {
class StuManager;
}

class StuManager : public QWidget
{
    Q_OBJECT

public:
    explicit StuManager(QWidget *parent = 0);
    ~StuManager();

    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();

    //Show MainTable HeadInfo
    void ShowMainTableHead(QString stDBName,QString stTableName);

    QStringList getRowData(int row);

    //获取列表表头信息
    QString GetHeadLabel();

signals:
    void  mouseClicked(int);
public slots:
    void editClickedSlot(int x ,int y);

private:
    Ui::StuManager *ui;

};

#endif // TABLEWIDGET_H
