#include "tableview.h"
#include <QApplication>
#include <QComboBox>
#include <QAction>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent), arr_row_list(NULL)
{

}

TableModel::~TableModel(void)
{
    arr_row_list = NULL;
}

void TableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
    horizontal_header_list = horizontalHeaderList;
}

void TableModel::setVerticalHeaderList(QStringList verticalHeaderList)
{
    vertical_header_list = verticalHeaderList;
}

int TableModel::rowCount(const QModelIndex &parent) const//返回行
{
    if(vertical_header_list.size() > 0)
        return vertical_header_list.size();

    if(NULL == arr_row_list)
        return 0;
    else
        return arr_row_list->size();
}

int TableModel::columnCount(const QModelIndex &parent) const//返回列
{
    if(horizontal_header_list.size() > 0)
        return horizontal_header_list.size();

    if(NULL == arr_row_list)
        return 0;
    else if(arr_row_list->size() < 1)
        return 0;
    else
        return arr_row_list->at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(NULL == arr_row_list)
        return QVariant();

    if(arr_row_list->size() < 1)
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        if(index.row() >= arr_row_list->size())
            return QVariant();
        if(index.column() >= arr_row_list->at(0).size())
            return QVariant();
        return arr_row_list->at(index.row()).at(index.column());
    }
    return QVariant();
}


/*
    headerData()函数返回固定的表头数据，设置水平表头的标题
*/
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)
    {
        if(orientation==Qt::Horizontal) // 水平表头
        {
            if(horizontal_header_list.size() > section)
                return horizontal_header_list[section];
            else
                return QVariant();
        }
        else
        {
            if(vertical_header_list.size() > section)
                return vertical_header_list[section]; // 垂直表头
            else
                return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);

    // flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑
    return flag;
}

void TableModel::setModalDatas(QList< QStringList > *rowlist)
{
    arr_row_list = rowlist;
}

void TableModel::refrushModel()
{

    beginResetModel();
    endResetModel();

    emit updateCount(this->rowCount(QModelIndex()));
}

/********************TableView********************/
TableView::TableView(QWidget *parent)
    : QTableView(parent)
{

    this->setAlternatingRowColors(true);
   // this->setStyleSheet( "QTableView{background-color: rgb(111, 181, 248);"
      //      "alternate-background-color: rgb(141, 209, 250);}" );
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setHighlightSections(false);
    this->verticalHeader()->setVisible(false);
    this->setShowGrid(true);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);

    model = new TableModel();
    this->setModel(model);
    this->setColumnWidth(0,685);
    this->setColumnWidth(1,85);
    this->setColumnWidth(2,85);
    this->setColumnWidth(3,85);
    this->setColumnWidth(4,85);
    this->setColumnWidth(5,85);
    this->setColumnWidth(6,85);
    //this->initHeader();
    model->setModalDatas(&grid_data_list);
   // progressbar_delegate = new ProgressBarDelegate();

  //  this->setItemDelegate(progressbar_delegate);
//    this->setStyleSheet("QTableView { border: none;"
//                        "background-color: #8EDE21;"
//                                   "selection-background-color: #999}"); //for demo purposes

    connect(model, &TableModel::updateCount, this, &TableView::updateCount);

    //this->initHeader();
}

TableView::~TableView(void)
{


    if(model) {
        delete model;
        model = NULL;
    }
    grid_data_list.clear();
}


void TableView::addRow(QStringList rowList)
{
    grid_data_list.append(rowList);
    model->refrushModel();
}

void TableView::remove()
{
    QModelIndexList model_index_list = this->selectedIndexes();
    int model_count = model_index_list.count();
    if(model_count <= 0)
        return;

    QList<int> list_row;
    for(int i=model_count-1; i>=0; i--)
    {
        QModelIndex model_index = model_index_list.at(i);
        int row = model_index.row();
        if(!list_row.contains(row))
            list_row.append(row);
    }

    if(list_row.isEmpty())
        return;

    qSort(list_row);

    for(int i=list_row.count()-1; i>=0; i--)
    {
        grid_data_list.removeAt(list_row.at(i));
    }

    model->refrushModel();
}

void TableView::clear()
{
    grid_data_list.clear();
    model->refrushModel();
}

int TableView::rowCount()
{
    return model->rowCount(QModelIndex());
}

void TableView::initHeader(QStringList header)
{
   // QStringList header;
  //  header << tr("name") << tr("size") << tr("progress") << tr("speed") << tr("left time") << tr("state");
   //   header << tr("任务名称")<<tr("任务编号") << tr("操作者") << tr("任务目标") << tr("任务状态")<< tr("开始时间")<< tr("结束时间") << tr("任务描述") ;
    model->setHorizontalHeaderList(header);
}

void TableView::changeValue()
{
    //这里以10行尾列进行更新
    int row_count = this->rowCount();
    if(row_count < 10)
        return;

    for(int i=0; i<10; i++)
    {
        QStringList file_list = grid_data_list.at(i);
        int progress = rand()%100;
        QStringList row_list;
        row_list <<  file_list.at(0) << file_list.at(1) << QString::number(progress) << file_list.at(3) << file_list.at(4) << file_list.at(5);
        grid_data_list.replace(i, row_list);
    }

    model->refrushModel();
}



//+++++++++++++++++++++++++++++++++++++++++++++++++++

LogView::LogView(QWidget *parent)
    : QTableView(parent)
{
    this->setAlternatingRowColors(true);
   // this->setStyleSheet( "QTableView{background-color: rgb(111, 181, 248);"
      //      "alternate-background-color: rgb(141, 209, 250);}" );
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->horizontalHeader()->setStretchLastSection(true);
    this->horizontalHeader()->setHighlightSections(false);
    this->verticalHeader()->setVisible(false);
    this->setShowGrid(true);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);

    model = new TableModel();
    this->setModel(model);
    //this->initHeader();

    model->setModalDatas(&grid_data_list);
   // progressbar_delegate = new ProgressBarDelegate();

  //  this->setItemDelegate(progressbar_delegate);
//    this->setStyleSheet("QTableView { border: none;"
//                        "background-color: #8EDE21;"
//                                   "selection-background-color: #999}"); //for demo purposes
 //   model->sort(0,Qt::AscendingOrder);

    connect(model, &TableModel::updateCount, this, &LogView::updateCount);

    this->initHeader();
}

LogView::~LogView(void)
{
//    if(progressbar_delegate) {
//        delete progressbar_delegate;
//        progressbar_delegate = NULL;
//    }

    if(model) {
        delete model;
        model = NULL;
    }
    grid_data_list.clear();
}
//QModelIndexList TableView::selectedIndexes()
//{
//    QModelIndexList list;
//    list=selectedIndexes();
//    return list;
//}

void LogView::addRow(QStringList rowList)
{
    grid_data_list.append(rowList);
    model->refrushModel();
}

void LogView::remove()
{
    QModelIndexList model_index_list = this->selectedIndexes();
    int model_count = model_index_list.count();
    if(model_count <= 0)
        return;

    QList<int> list_row;
    for(int i=model_count-1; i>=0; i--)
    {
        QModelIndex model_index = model_index_list.at(i);
        int row = model_index.row();
        if(!list_row.contains(row))
            list_row.append(row);
    }

    if(list_row.isEmpty())
        return;

    qSort(list_row);

    for(int i=list_row.count()-1; i>=0; i--)
    {
        grid_data_list.removeAt(list_row.at(i));
    }

    model->refrushModel();
}

void LogView::clear()
{
    grid_data_list.clear();
    model->refrushModel();
}

int LogView::rowCount()
{
    return model->rowCount(QModelIndex());
}

void LogView::initHeader()
{
    QStringList header;
      header << tr("操作时间") << tr("操作者") << tr("操作内容") << tr("操作结果")<< tr("备注") ;
    model->setHorizontalHeaderList(header);
}

void LogView::changeValue()
{
    //这里以10行尾列进行更新
    int row_count = this->rowCount();
    if(row_count < 10)
        return;

    for(int i=0; i<10; i++)
    {
        QStringList file_list = grid_data_list.at(i);
        int progress = rand()%100;
        QStringList row_list;
        row_list <<  file_list.at(0) << file_list.at(1) << QString::number(progress) << file_list.at(3) << file_list.at(4) << file_list.at(5);
        grid_data_list.replace(i, row_list);
    }

    model->refrushModel();
}
