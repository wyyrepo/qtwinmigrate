#ifndef YADATAMAKE_H
#define YADATAMAKE_H

#include <QWidget>

#include <QTabWidget>
#include "preplangenerate/autopreplan.h"
#include "preplangenerate/handpreplan.h"

namespace Ui {
class YADataMake;
}

class YADataMake : public QWidget
{
    Q_OBJECT

public:
    explicit YADataMake(QWidget *parent = 0);
    ~YADataMake();

private:
    QTabWidget *tabWidget;
    AutoPrePlan *autoPrePlanTab;
    HandPrePlan *handPrePlanTab;

private:
    Ui::YADataMake *ui;
};

#endif // YADATAMAKE_H
