#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T16:17:18
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CPU/team.cpp \
    Anton_CPU/CommunicationMinister.cpp \
    Anton_CPU/Defence.cpp \
    Anton_CPU/Finance.cpp \
    Anton_CPU/ForeignMinister.cpp \
    Anton_CPU/Government.cpp \
    Anton_CPU/HealthMinister.cpp \
    Anton_CPU/Minister.cpp \
    Anton_CPU/ministerFSB.cpp \
    Anton_CPU/MinisterOfJustice.cpp \
    Anton_CPU/MVD.cpp \
    Anton_CPU/President.cpp \
    Anton_CPU/TSOP.cpp \
    CPU/maincpu.cpp \
    listofgovernments.cpp \
    CPU/rialto.cpp \
    whataboutproofdial.cpp \
    Anton_CPU/secretary.cpp



HEADERS  += mainwindow.h \
    CPU/team.h \
    Anton_CPU/CommunicationMinister.h \
    Anton_CPU/Constants.h \
    Anton_CPU/Defence.h \
    Anton_CPU/Finance.h \
    Anton_CPU/ForeignMinister.h \
    Anton_CPU/Government.h \
    Anton_CPU/HealthMinister.h \
    Anton_CPU/Minister.h \
    Anton_CPU/ministerFSB.h \
    Anton_CPU/MinisterOfJustice.h \
    Anton_CPU/MVD.h \
    Anton_CPU/President.h \
    CPU/maincpu.h \
    listofgovernments.h \
    CPU/rialto.h \
    CPU/nukesinair.h \
    whataboutproofdial.h \
    Anton_CPU/secretary.h \
    CPU/reconinformation.h




FORMS    += mainwindow.ui \
    whataboutproofdial.ui
