QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/game.cpp \
    main.cpp \
    mainwindow.cpp \
    scene/blockimage.cpp \
    scene/figureimage.cpp \
    scene/scene.cpp \
    scene/view.cpp

HEADERS += \
    game/block.h \
    game/figure.h \
    game/game.h \
    globals.h \
    mainwindow.h \
    scene/blockimage.h \
    scene/figureimage.h \
    scene/scene.h \
    scene/view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
