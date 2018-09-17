#ifndef APP_H
#define APP_H

class QString;

class App
{
public:
    static QString AppPath;             //应用程序路径
    static int AppFontSize;             //应用程序字体大小
    static QString AppFontName;         //应用程序字体名称

    static void ReadConfig();           //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();          //写入配置文件,在更改配置文件程序关闭时调用

};

#endif // APP_H
