#include "appinit.h"
#include "myhelper.h"

AppInit::AppInit(QObject *parent) : QObject(parent)
{
    mousePressed = false;
    qApp->installEventFilter(this);
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("CanMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void AppInit::Load()
{
    myHelper::SetUTF8Code();
    myHelper::SetChinese();
    qApp->setFont(QFont(App::AppFontName, App::AppFontSize));

    App::AppPath = QApplication::applicationDirPath();

}
