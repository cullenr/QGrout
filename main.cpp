#include <QtQml/QQmlContext>
#include <QtCore/QObject>
#include "gameapplication.h"
#include "gamewindow.h"
#include "tilemap.h"
#include "tilesheet.h"
#include "shaderasset.h"
#include "scene.h"
#include "textureasset.h"
#include "material.h"
#include "abstractgameobject.h"
#include "actor.h"

int main(int argc, char *argv[])
{
    GameApplication app(argc, argv);
    const int major = 1;
    const int minor = 0;

    qmlRegisterType<TextureAsset>("QGrout", major, minor, "TextureAsset");
    qmlRegisterType<ShaderAsset>("QGrout", major, minor, "ShaderAsset");
    qmlRegisterType<Scene>("QGrout", major, minor, "Scene");
    qmlRegisterType<Material>("QGrout", major, minor, "Material");
    qmlRegisterType<TileSheet>("QGrout", major, minor, "TileSheet");
    qmlRegisterType<TileMap>("QGrout", major, minor, "TileMap");
    qmlRegisterType<Actor>("QGrout", major, minor, "Actor");

    GameWindow viewer;
    viewer.rootContext()->setContextProperty("Game", &viewer);
    viewer.setMainQmlFile(QStringLiteral("qml/qgrout/main.qml"));
    viewer.showExpanded();

    return app.exec();

}
