#ifndef  TABLEVIEW_H
#define  TABLEVIEW_H
#include <QTableView>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QStringList>
#include <QPainter>
#include <QHeaderView>

class TableModel : public QAbstractTableModel//QSqlTableModel
{
    Q_OBJECT

public:

    TableModel(QObject *parent = 0);
    ~TableModel(void);
    void setHorizontalHeaderList(QStringList horizontalHeaderList);
    void setVerticalHeaderList(QStringList verticalHeaderList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setModalDatas(QList< QStringList > *rowlist);
    void refrushModel();

signals:

    void updateCount(int count);

private:

    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList< QStringList > *arr_row_list;

};

/********************ReadOnlyTableView********************/
class TableView : public QTableView
{
    Q_OBJECT

public:

    TableView(QWidget *parent=0);
    ~TableView(void);
    void addRow(QStringList rowList);
    int rowCount();
    TableModel *model;
    QList< QStringList > grid_data_list;
signals:
    void updateCount(int count);
public slots:
    void remove();
    void clear();
    void changeValue();
public:
    void initHeader( QStringList header);

private:

    //ProgressBarDelegate *progressbar_delegate;


};
class LogView : public QTableView
{
    Q_OBJECT

public:

    LogView(QWidget *parent=0);
    ~LogView(void);
    void addRow(QStringList rowList);
    int rowCount();
    //    QModelIndexList selectedIndexes();
    TableModel *model;
    QList< QStringList > grid_data_list;
signals:
    void updateCount(int count);
public slots:
    void remove();
    void clear();
    void changeValue();
private:
    void initHeader();

private:

    //ProgressBarDelegate *progressbar_delegate;


};
#endif // LOGIN_H
