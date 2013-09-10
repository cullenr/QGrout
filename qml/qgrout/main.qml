import QtQuick 2.0
import QGrout 1.0

Item{
    width: 640
    height: 480

    Scene{
        id: sceneOne

        Text {
            id: testText
            text: sceneOne.cameraPosition.x + sceneOne.cameraPosition.y
            scale: 4
        }

        tilemap: TileMap {
            mapWidth: 10
            map: [1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                  1, 2, 0, 0, 0, 0, 0, 0, 0, 1,
                  1, 0, 3, 0, 0, 0, 0, 0, 0, 1,
                  1, 0, 0, 4, 0, 0, 0, 0, 0, 1,
                  1, 0, 0, 0, 5, 0, 0, 0, 0, 1,
                  1, 0, 0, 0, 0, 6, 0, 0, 0, 1,
                  1, 0, 0, 0, 0, 0, 7, 0, 0, 1,
                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
            tileSheet: TileSheet {
                material: Material {
                    shader: ShaderAsset {
                        vertexShaderPath: ":/shaders/assets/shaders/texture.vert"
                        fragmentShaderPath: ":/shaders/assets/shaders/texture.frag"
                    }
                    texture: TextureAsset{
                        texturePath: ":/test/assets/minecraft_tilesheet.png"
                    }
                }
                tilesAcross: 16
                tilesSize: 32
            }

        }
        focus: true
        Keys.onUpPressed: sceneOne.cameraPosition.y -= 1
        Keys.onDownPressed: sceneOne.cameraPosition.y += 1
        Keys.onLeftPressed: sceneOne.cameraPosition.x += 1
        Keys.onRightPressed: sceneOne.cameraPosition.x -= 1
    }
}



