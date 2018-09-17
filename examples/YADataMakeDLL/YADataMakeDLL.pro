QT       += sql widgets
TEMPLATE     = lib
CONFIG	    += dll
SOURCES	     = main.cpp \
    api/app.cpp \
    api/appinit.cpp \
    api/iconhelper.cpp \
    help/help.cpp \
    help/helpinfo.cpp \
    preplangenerate/autopreplan.cpp \
    preplangenerate/chart2.cpp \
    preplangenerate/chartwidget2.cpp \
    preplangenerate/gatherinfotab.cpp \
    preplangenerate/handpreplan.cpp \
    preplangenerate/preinfotab.cpp \
    preplangenerate/topwidget.cpp \
    usercontrol/frminputbox.cpp \
    usercontrol/frmmessagebox.cpp \
    tableview.cpp \
    yadatamake.cpp

TARGET	     = YADataMake
DLLDESTDIR   = $$[QT_INSTALL_PREFIX]/bin

include(../../src/qtwinmigrate.pri)

RESOURCES += \
    resource.qrc

FORMS += \
    preplangenerate/topwidget.ui \
    usercontrol/frminputbox.ui \
    usercontrol/frmmessagebox.ui \
    yadatamake.ui


HEADERS += \
    api/app.h \
    api/appinit.h \
    api/iconhelper.h \
    api/myhelper.h \
    help/help.h \
    help/helpinfo.h \
    preplangenerate/autopreplan.h \
    preplangenerate/chart2.h \
    preplangenerate/chartwidget2.h \
    preplangenerate/cmdrsp_cdb.h \
    preplangenerate/constract.h \
    preplangenerate/gatherinfotab.h \
    preplangenerate/handpreplan.h \
    preplangenerate/preinfotab.h \
    preplangenerate/topwidget.h \
    usercontrol/frminputbox.h \
    usercontrol/frmmessagebox.h \
    tableview.h \
    yadatamake.h
