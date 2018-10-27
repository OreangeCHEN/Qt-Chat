#-------------------------------------------------
#
# Project created by QtCreator 2015-05-11T16:52:48
#
#-------------------------------------------------

QT       += core gui sql
QT       += widgets
QT       +=network
TARGET = login
TEMPLATE = app

RC_FILE = myapp.rc


SOURCES += main.cpp\
        login.cpp \
    passwdedit.cpp \
    register.cpp \
    systemtrayicon.cpp\
    widget.cpp \
    drawer.cpp \
    server.cpp \
    client.cpp

HEADERS  += login.h \
    passwdedit.h \
    register.h \
    systemtrayicon.h\
     widget.h \
    drawer.h \
    server.h \
    client.h

FORMS    += login.ui \
    passwdedit.ui \
    register.ui\
        widget.ui \
    server.ui \
    client.ui



RESOURCES += \
    myqrc.qrc \
    lang.qrc \
    qss.qrc

TRANSLATIONS+=cn.ts\
              en.ts
