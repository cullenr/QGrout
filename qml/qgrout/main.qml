import QtQuick 2.0
import QGrout 1.0

Item{
    width: 640
    height: 480

    Scene{
        id: sceneOne
        resources: ResourceManager {
            textures: TextureAssetManager {
                TextureAsset{
                    id: minecraftTiles
                    texturePath: ":/test/assets/minecraft_tilesheet.png"
                }
            }
            shaders: ShaderAssetManager {
                ShaderAsset {
                    id: texture
                    vertexShaderPath: ":/shaders/assets/shaders/texture.vert"
                    fragmentShaderPath: ":/shaders/assets/shaders/texture.frag"
                }
//                ShaderAsset {
//                    id: squircle
//                    vertexShaderPath: ":/shaders/assets/shaders/squircle.vert"
//                    fragmentShaderPath: ":/shaders/assets/shaders/squircle.frag"
//                }
//                ShaderAsset {
//                    id: basic
//                    vertexShaderPath: ":/shaders/assets/shaders/basic.vert"
//                    fragmentShaderPath: ":/shaders/assets/shaders/basic.frag"
//                }
            }
            materials: MaterialManager{
                Material {
                    id: textureMaterial
                    shader: texture
                    texture: minecraftTiles
                }
            }
        }

        Text {
            id: blasd
            text: sceneOne.cameraPosition.x + sceneOne.cameraPosition.y
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
                material: textureMaterial
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



