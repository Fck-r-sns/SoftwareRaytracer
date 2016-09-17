TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $${PWD}/bin

SOURCES += \
    src/main.cpp \
    src/ImageWriter.cpp \
    src/Image.cpp \
    src/SceneConfiguration.cpp \
    src/Parser.cpp

HEADERS += \
    src/libs/FreeImage/FreeImage.h \
    src/ImageWriter.h \
    src/defines.h \
    src/Image.h \
    src/SceneConfiguration.h \
    src/Parser.h

HEADERS += \
    src/libs/glm/*.hpp

win32: LIBS += -L$$PWD/src/libs/FreeImage/ -lFreeImage

INCLUDEPATH += $$PWD/src/libs/FreeImage
DEPENDPATH += $$PWD/src/libs/FreeImage
