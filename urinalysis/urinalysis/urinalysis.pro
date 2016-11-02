#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T13:46:11
#
#-------------------------------------------------

QT       += core gui printsupport sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = urinalysis
TEMPLATE = app


SOURCES += main.cpp\
        urinalysis.cpp \
    printforms.cpp \
    database.cpp \
    serialport.cpp \
    slavethread.cpp \
    mlineedit.cpp

HEADERS  += urinalysis.h \
    printforms.h \
    database.h \
    define.h \
    serialport.h \
    slavethread.h \
    mlineedit.h

FORMS    += urinalysis.ui \
    printforms.ui

RESOURCES += \
    resource.qrc\
