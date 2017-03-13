#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T19:26:35
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = learning-graphics
TEMPLATE = app

SOURCES += main.cxx\
        game.cxx \
    player.cxx \
    enemy.cxx \
    bullet.cxx

HEADERS  += game.hxx \
    player.hxx \
    enemy.hxx \
    bullet.hxx

RESOURCES += \
    res.qrc
