import QtQuick 2.0

Item {
    id:game
    width: 640
    height: 480

    property alias game : game                  //this is practically global to any QML component
    property alias scene : sceneLoader.item     //points to the current scene

    Loader {
        id: sceneLoader
        source: "SceneOne.qml"
    }
}




