QT       += core gui webenginewidgets webchannel
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appgpslocation.cpp \
    appinitgamedata.cpp \
    appwaypoint.cpp \
    logcard.cpp \
    logdata.cpp \
    loggingwaypoint.cpp \
    main.cpp \
    mainwindow.cpp \
    mapcontroller.cpp
RESOURCES += resources.qrc \
resources.qrc
HEADERS += \
    appgpslocation.h \
    appinitgamedata.h \
    appwaypoint.h \
    logcard.h \
    logdata.h \
    loggingwaypoint.h \
    mainwindow.h \
    mapcontroller.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    map.html
