#ifndef GATHERINFOTAB_H
#define GATHERINFOTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "cmdrsp_cdb.h"


class GatherInfoTab : public QWidget
{
    Q_OBJECT
public:
    explicit GatherInfoTab(QWidget *parent = 0);

signals:
    void sendDataClient( char *, int );

public slots:

private:


    QVBoxLayout *mainLayout;
    QHBoxLayout *Layout;

    QLabel *samplerate;
    QComboBox *comboBox;
    QLabel *sampletime;
    QLineEdit *linedit1;
    QLabel *middle;
    QLineEdit *linedit2;
    QPushButton *query;
    QPushButton *retreat;
    QPushButton *play;
    QPushButton *advance;

    int iSerialNum;

};

#endif // GATHERINFOTAB_H
