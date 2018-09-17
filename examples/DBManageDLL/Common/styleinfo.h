#ifndef STYLEINFO_H
#define STYLEINFO_H


#include <QtCore>
#include <QDialog>
#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

class StyleInfo: public QObject
{

public:
    //设置编码为UTF8
    static void SetUTF8Code() {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //设置指定样式
    static void SetStyle(const QString &qssFile) {
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly)) {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            QString PaletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(QColor(PaletteColor)));
            file.close();
        }
    }
    //加载中文字符
    static void SetChinese() {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/image/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    //窗体居中显示
    static void FormInCenter(QWidget *frm) {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.availableGeometry().width();
        int deskHeight = w.availableGeometry().height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

};

#endif // STYLEINFO_H
