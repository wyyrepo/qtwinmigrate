#include "helpinfo.h"
#include <QLabel>
#include <QHBoxLayout>
helpInfo::helpInfo(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *label = new QLabel("帮助");
    layout->addStretch();
    layout->addWidget(label);
        layout->addStretch();
    setLayout(layout);
}
