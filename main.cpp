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
#include "spritecomponent.h"
#include "actor.h"
#include "sceneitem.h"
#include "sceneelementinterface.h"

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
    qmlRegisterType<SpriteComponent>("QGrout", major, minor, "SpriteComponent");
    qmlRegisterType<SceneItem>();// SceneItem is abstract, therefore we registr it this way.

    GameWindow viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qgrout/main.qml"));
    viewer.showExpanded();

    return app.exec();

}
