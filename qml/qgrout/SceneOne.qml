import QtQuick 2.0
import QGrout 1.0

Scene {
    id:scene

    //if we store assets in these dynamically created objects, we can create type safe references to
    //them
    property Item assets : Item {
        property TextureAsset tiles : TextureAsset {
            texturePath: ":/test/assets/minecraft_tilesheet.png"
        }
        property ShaderAsset textureShader : ShaderAsset {
            vertexShaderPath: ":/shaders/assets/shaders/texture.vert"
            fragmentShaderPath: ":/shaders/assets/shaders/texture.frag"
        }
    }

    actors: [
        Hero {}
    ]

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
                shader: assets.textureShader
                texture: assets.tiles
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
