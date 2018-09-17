#ifndef FRMINPUTBOX_H
#define FRMINPUTBOX_H

#include <QDialog>

namespace Ui
{
    class frmInputBox;
}

class frmInputBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmInputBox(QWidget *parent = 0);
    ~frmInputBox();

    void SetMessage(QString title);
    QString GetValue()const {
        return value;
    }

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmInputBox *ui;

    void InitStyle();   //初始化无边框窗体

    QString value;
};

#endif // FRMINPUTBOX_H
