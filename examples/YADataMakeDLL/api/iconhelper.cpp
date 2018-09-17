#include "iconhelper.h"
#include "app.h"

IconHelper *IconHelper::_instance = 0;
IconHelper::IconHelper(QObject *):
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);
}

void IconHelper::SetIcon(QLabel *lab, QChar c)
{
    iconFont.setPointSize(App::AppFontSize);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::SetIcon(QPushButton *btn, QChar c)
{
    iconFont.setPointSize(App::AppFontSize);
    btn->setFont(iconFont);
    btn->setText(c);
}
