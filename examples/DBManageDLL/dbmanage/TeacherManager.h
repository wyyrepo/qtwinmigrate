#ifndef TEACHERMANAGERWIDGET_H
#define TEACHERMANAGERWIDGET_H
#include "StuManager.h"

#include <QWidget>

namespace Ui {
class TeacherManager;
}

class TeacherManager : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherManager(QWidget *parent = 0);
    ~TeacherManager();

    QStringList getData();

    void clearData();

    QStringList getEitdData();

    //Show SubTable HeadInfo
    void ShowSubTableHead(QString stDBName,QString stTableName);
    QStringList setEitdData( QStringList rowdata );

private:
    Ui::TeacherManager *ui;
    StuManager *m_pTableWidget;
};

#endif // TEACHERMANAGERWIDGET_H
