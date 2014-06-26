#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T19:30:43
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -L../../../Libs/glew-1.10.0/lib/Release/Win32 -lglew32

INCLUDEPATH += ../../../Libs/glew-1.10.0/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrossEngine
TEMPLATE = app

DEFINES += "QTWINDOWS"

SOURCES +=\
        mainwindow.cpp \
    ../../../Src/GLRenderer.cpp \
    ../../../Src/Kernel.cpp \
    ../../../Src/main.cpp \
    ../../../Src/QtGLRenderer.cpp \
    ../../../Src/Renderer.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    ../../../Src/Base.h \
    ../../../Src/GLRenderer.h \
    ../../../Src/Kernel.h \
    ../../../Src/Platform.h \
    ../../../Src/QtGLRenderer.h \
    ../../../Src/Renderer.h \
    ../../../Src/Singleton.h \
    ../../../Src/Task.h \
    ../../../Src/Types.h \
    myglwidget.h

FORMS    += \
    mainwindow.ui

OTHER_FILES +=
