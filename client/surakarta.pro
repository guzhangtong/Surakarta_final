QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AIGame.cpp \
    Board.cpp \
    connectdialog.cpp \
    connectinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    networkdata.cpp \
    networksocket.cpp \
    stage3/chatreceivestageop.cpp \
    stage3/chatstagemessage.cpp \
    stage3/endrevicestageop.cpp \
    stage3/leavestagemessage.cpp \
    stage3/moverevicestageop.cpp \
    stage3/movestagemessage.cpp \
    stage3/readyrevicestageop.cpp \
    stage3/readystagemessage.cpp \
    stage3/receivestageop.cpp \
    stage3/resignstagemessage.cpp \
    stage3/stagemessage.cpp \
    step.cpp
    stone.cpp

HEADERS += \
    AIGame.h \
    Board.h \
    connectdialog.h \
    connectinfo.h \
    mainwindow.h \
    networkdata.h \
    networksocket.h \
    stage3/chatreceivestageop.h \
    stage3/chatstagemessage.h \
    stage3/endrevicestageop.h \
    stage3/leavestagemessage.h \
    stage3/moverevicestageop.h \
    stage3/movestagemessage.h \
    stage3/readyrevicestageop.h \
    stage3/readystagemessage.h \
    stage3/receivestageop.h \
    stage3/resignstagemessage.h \
    stage3/stagemessage.h \
    step.h \
    stone.h

FORMS += \
    connectdialog.ui \
    mainwindow.ui


TRANSLATIONS += \
    surakarta_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
