#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T08:05:05
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "./include"
INCLUDEPATH += "./Assimp/include"

LIBS += -L"$$_PRO_FILE_PWD_/Assimp/lib64" -lassimp-vc140-mt

HEADERS  += \
    include/camera.h            \
    include/display.h           \
    include/drawable.h          \
    include/entity.h            \
    include/gl_debug.h          \
    include/input_manager.h     \
    include/mathematics.h       \
    include/mesh.h              \
    include/model.h             \
    include/model_loader.h      \
    include/scene.h             \
    include/scene_item.h        \
    include/scene_model.h       \
    include/scene_view.h        \
    include/shader_program.h    \
    include/transform.h         \
    include/ui_display.h        \
    include/ui_item.h

SOURCES +=  main.cpp            \
    Source/display.cpp          \
    Source/entity.cpp           \
    Source/gl_debug.cpp         \
    Source/input_manager.cpp    \
    Source/mesh.cpp             \
    Source/model.cpp            \
    Source/scene.cpp            \
    Source/scene_item.cpp       \
    Source/scene_view.cpp       \
    Source/shader_program.cpp   \
    Source/ui_item.cpp

FORMS += \
    display.ui

RESOURCES += \
    shaders.qrc
