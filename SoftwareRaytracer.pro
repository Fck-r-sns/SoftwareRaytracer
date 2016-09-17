TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $${PWD}/bin

INCLUDEPATH = $${PWD}/src

SOURCES += \
    src/main.cpp \
    src/image/ImageWriter.cpp \
    src/image/Image.cpp \
    src/scene/SceneConfiguration.cpp \
    src/scene/Parser.cpp \
    src/Transform.cpp \
    src/raytracing/RayTracer.cpp \
    src/raytracing/Ray.cpp \
    src/scene/Primitive.cpp \
    src/scene/Material.cpp \
    src/scene/Triangle.cpp \
    src/raytracing/Intersection.cpp

HEADERS += \
    src/libs/FreeImage/FreeImage.h \
    src/image/ImageWriter.h \
    src/image/Pixel.h \
    src/image/Image.h \
    src/scene/SceneConfiguration.h \
    src/scene/Parser.h \
    src/Transform.h \
    src/raytracing/RayTracer.h \
    src/raytracing/Ray.h \
    src/scene/Primitive.h \
    src/scene/Material.h \
    src/scene/Triangle.h \
    src/raytracing/Intersection.h

HEADERS += \
    src/libs/glm/*.hpp \
    src/libs/glm/gtc/*.hpp \

win32: LIBS += -L$$PWD/src/libs/FreeImage/ -lFreeImage

INCLUDEPATH += $$PWD/src/libs/FreeImage
DEPENDPATH += $$PWD/src/libs/FreeImage
