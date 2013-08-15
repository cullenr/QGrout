#include <QtGui/QGuiApplication>
#include "gamewindow.h"
#include "tilemap.h"
#include "shaderassetmanager.h"
#include "shaderasset.h"
#include "textureassetmanager.h"
#include "resourcemanager.h"
#include "scene.h"
#include "textureasset.h"
#include "material.h"
#include "materialmanager.h"
#include <QtQml/QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    const int major = 1;
    const int minor = 0;

    qmlRegisterType<TextureAsset>("QGrout", major, minor, "TextureAsset");
    qmlRegisterType<TextureAssetManager>("QGrout", major, minor, "TextureAssetManager");
    qmlRegisterType<ShaderAsset>("QGrout", major, minor, "ShaderAsset");
    qmlRegisterType<ShaderAssetManager>("QGrout", major, minor, "ShaderAssetManager");
    qmlRegisterType<AssetManager>("QGrout", major, minor, "ResourceManager");
    qmlRegisterType<Scene>("QGrout", major, minor, "Scene");
    qmlRegisterType<Material>("QGrout", major, minor, "Material");
    qmlRegisterType<MaterialManager>("QGrout", major, minor, "MaterialManager");
    qmlRegisterType<Tilemap>("QGrout", major, minor, "Tilemap");

    GameWindow viewer;
    viewer.rootContext()->setContextProperty("Window", &viewer);
    viewer.setMainQmlFile(QStringLiteral("qml/qgrout/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
