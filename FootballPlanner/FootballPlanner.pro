QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    bfsalgo.cpp \
    dfsgraph.cpp \
    djalgo.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    mapsouvenir.cpp \
    menuselectwindow.cpp \
    mstalgo.cpp \
    tripselectwindow.cpp

HEADERS += \
    adminwindow.h \
    bfsalgo.h \
    dfsgraph.h \
    djalgo.h \
    mainmenu.h \
    mainwindow.h \
    mapsouvenir.h \
    menuselectwindow.h \
    mstalgo.h \
    tripselectwindow.h

FORMS += \
    adminwindow.ui \
    mainmenu.ui \
    mainwindow.ui \
    menuselectwindow.ui \
    tripselectwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
