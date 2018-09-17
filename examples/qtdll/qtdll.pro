QT       += sql widgets
TEMPLATE     = lib
CONFIG	    += dll
SOURCES	     = main.cpp \
    dbmanage/form.cpp \
    dbmanage/StuManager.cpp \
    dbmanage/TeacherManager.cpp \
    qdbmanage.cpp

TARGET	     = qtdialog
DLLDESTDIR   = $$[QT_INSTALL_PREFIX]/bin

include(../../src/qtwinmigrate.pri)

FORMS += \
    dbmanage/form.ui \
    dbmanage/StuManager.ui \
    dbmanage/TeacherManager.ui \
    qdbmanage.ui

HEADERS += \
    dbmanage/form.h \
    dbmanage/StuManager.h \
    dbmanage/TeacherManager.h \
    qdbmanage.h
