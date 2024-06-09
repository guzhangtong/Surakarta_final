QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    networkdata.cpp \
    networkserver.cpp \
    stage3/chatstagemessage.cpp \
    stage3/chatstageop.cpp \
    stage3/endstagemessage.cpp \
    stage3/leavestagemessage.cpp \
    stage3/leavestageop.cpp \
    stage3/movestagemessage.cpp \
    stage3/movestageop.cpp \
    stage3/readystageop.cpp \
    stage3/resignstageop.cpp \
    stage3/serverreceivestageop.cpp \
    stage3/stagemessage.cpp \
    step.cpp \
    stone.cpp

HEADERS += \
    Board.h \
    logger.h \
    mainwindow.h \
    networkdata.h \
    networkserver.h \
    stage3/chatstagemessage.h \
    stage3/chatstageop.h \
    stage3/endstagemessage.h \
    stage3/leavestagemessage.h \
    stage3/leavestageop.h \
    stage3/movestagemessage.h \
    stage3/movestageop.h \
    stage3/readystageop.h \
    stage3/resignstageop.h \
    stage3/serverreceivestageop.h \
    stage3/stagemessage.h \
    step.h \
    stone.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
