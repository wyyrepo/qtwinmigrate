#include "app.h"
#include "myhelper.h"

QString App::AppPath = "";

#ifdef Q_OS_WIN
int App::AppFontSize = 10;
QString App::AppFontName = "Microsoft YaHei";
#endif

#ifdef Q_OS_LINUX
#ifdef __arm__
int App::AppFontSize = 11;
QString App::AppFontName = "WenQuanYi Micro Hei";
#else
int App::AppFontSize = 11;
QString App::AppFontName = "WenQuanYi";
#endif
#endif

#ifdef Q_OS_MAC
int App::AppFontSize = 11;
QString App::AppFontName = "Heiti SC";
#endif

void App::ReadConfig()
{
    QString fileName = App::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");
    set->endGroup();
}

void App::WriteConfig()
{
    QString fileName = App::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup("AppConfig");
    set->endGroup();
}
