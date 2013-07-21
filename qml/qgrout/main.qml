import QtQuick 2.0
import QGrout 1.0

Item{
    width: 800
    height: 640

    Scene{
        id: sceneOne
        resources: ResourceManager {
            textures: TextureAssetManager {
                texturePaths: [":/test/assets/minecraft_tilesheet.png"]
            }
            shaders: ShaderAssetManager {
                ShaderAsset {
                    objectName: "texture-shader"
                    vertexShaderPath: ":/shaders/assets/shaders/texture.vert"
                    fragmentShaderPath: ":/shaders/assets/shaders/texture.frag"
                }
                ShaderAsset {
                    objectName: "textureShader"
                    vertexShaderPath: ":/shaders/assets/shaders/texture.vert"
                    fragmentShaderPath: ":/shaders/assets/shaders/texture.frag"
                }
            }
        }

        Tilemap {

        }
    }

    Text {
        id: tf
        text: "poo"
    }


    Connections{
       target: Window
       onSceneGraphInitialized : tf.text = sceneOne.resources.shaders.shaderSources[1].vertexShaderPath
    }
}



