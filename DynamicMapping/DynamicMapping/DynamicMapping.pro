#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T15:51:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = D

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

unix:!macx: LIBS += -L/usr/local/lib/ \
-lopencv_core\
-lopencv_highgui\
-lopencv_imgproc\
-lopencv_legacy\
-lopencv_stitching



INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include


SOURCES += main.cpp \
    panaroma.cpp \
    cfar.cpp

HEADERS += \
    matcher.h \
    matcher.h \
    panaroma.h \
    cfar.h

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_calib3d

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lopencv_features2d

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lopencv_nonfree

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include
