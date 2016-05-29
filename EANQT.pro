#-------------------------------------------------
#
# Project created by QtCreator 2016-05-28T14:16:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EANQT
TEMPLATE = app

INCLUDEPATH += /usr/local/boost/

SOURCES += main.cpp\
        mainwindow.cpp\
        logicmain.cpp\
        DataReader.cpp\
        NumericalPeriodSpline.cpp\
        IntervalPeriodSpline.cpp\
        Utilities.cpp

HEADERS  += mainwindow.h\
            DataReader.h\
            Exceptions.h\
            IntervalPeriodSpline.h\
            NumericalPeriodSpline.h\
            Interval.h\
            Utilities.h\
            logicmain.h\



FORMS    += mainwindow.ui


CONFIG += c++11

LIBS += /usr/lib/x86_64-linux-gnu/libmpfr.a
LIBS += /usr/lib/x86_64-linux-gnu/libgmp.a
INCLUDEPATH += /usr/include

RESOURCES += \
    myresources.qrc

