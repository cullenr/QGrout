#include <QtGui/QGuiApplication>
#include "gamewindow.h"
#include "tilemap.h"
#include "shaderassetmanager.h"
#include "shaderasset.h"
#include "textureassetmanager.h"
#include "resourcemanager.h"
#include "scene.h"
#include <QtQml/QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    const int major = 1;
    const int minor = 0;

    qmlRegisterType<Tilemap>("QGrout", major, minor, "Tilemap");
    qmlRegisterType<ShaderAsset>("QGrout", major, minor, "ShaderAsset");
    qmlRegisterType<AssetManager>("QGrout", major, minor, "ResourceManager");
    qmlRegisterType<TextureAssetManager>("QGrout", major, minor, "TextureAssetManager");
    qmlRegisterType<ShaderAssetManager>("QGrout", major, minor, "ShaderAssetManager");
    qmlRegisterType<Scene>("QGrout", major, minor, "Scene");

    GameWindow viewer;
    viewer.rootContext()->setContextProperty("Window", &viewer);
    viewer.setMainQmlFile(QStringLiteral("qml/qgrout/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
