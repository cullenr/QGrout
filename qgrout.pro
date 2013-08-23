# Add more folders to ship with the application, here
folder_01.source = qml/qgrout
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += opengl

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    tilemap.cpp \
    gamewindow.cpp \
    scene.cpp \
    resourcemanager.cpp \
    shaderassetmanager.cpp \
    textureassetmanager.cpp \
    shaderasset.cpp \
    textureasset.cpp \
    genericmanager.cpp \
    materialmanager.cpp \
    material.cpp \
    tilestrip.cpp \
    initialisationvisitor.cpp \
    drawvisitor.cpp \
    mesh.cpp \
    tilesheet.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    tilemap.h \
    gamewindow.h \
    scene.h \
    resourcemanager.h \
    shaderassetmanager.h \
    textureassetmanager.h \
    shaderasset.h \
    textureasset.h \
    genericmanager.h \
    materialmanager.h \
    material.h \
    vertexdata.h \
    tilestrip.h \
    visitee.h \
    visitor.h \
    initialisationvisitor.h \
    drawvisitor.h \
    mesh.h \
    tilesheet.h

RESOURCES += test_assets.qrc \
    shaders.qrc

CONFIG += c++11
