#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QVariantMap>
#include <QList>

static QString condition;
namespace Ui {
class Form;
}

typedef struct fieldname
{
    fieldname()
    {
       stName_CN.clear();
       stName_EN.clear();
    }

    QString stName_CN;
    QString stName_EN;
}FIELDNAME;

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

   bool btnSearchIsClicked;
   bool btnFormQuickSearchIsClicked;
   bool btnFormSearchIsClicked;
   bool btnCheckBoxClicked;

   QString stDBName;
   QString stTableName;

   QList<FIELDNAME> lstField;
   QStringList stlstNameEN;
   QStringList stlstNameCN;

   void getTableField();
   void setcomboBox1();
   void setcomboBox2();
   void setcomboBox3();

   void setQueryData();

   void dataClear();

   void closeEvent(QCloseEvent *event);

   QString TranFieldNameFromCNToEN(QString stNameCN);

public slots:
    void on_pushButton_3_clicked();

    void judge();

signals:
    void signalInfo(QString);
    void signalInfo1(QString);


private slots:

    void on_setQueryData_clicked();

    void on_quickSerchButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
