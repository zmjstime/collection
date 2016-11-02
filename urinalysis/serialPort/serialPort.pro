#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T14:26:58
#
#-------------------------------------------------

QT       += core gui serialport sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialPort
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    serialport.cpp \
    database.cpp \
    exportforms.cpp

HEADERS  += widget.h \
    serialport.h \
    database.h \
    exportforms.h

FORMS +=
