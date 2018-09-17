#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QGroupBox>

namespace Ui {
class TopWidget;
}

class TopWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit TopWidget(QWidget *parent = 0);
    ~TopWidget();

private:
    Ui::TopWidget *ui;
};

#endif // TOPWIDGET_H
