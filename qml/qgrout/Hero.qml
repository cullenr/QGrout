import QtQuick 2.0
import QGrout 1.0

Actor {
    id: hero

    property SpriteComponent sprite : SpriteComponent {
        material: Material {
            shader: scene.assets.textureShader
            texture: scene.assets.tiles
        }
        textureCoordinates: Qt.rect(224, 224, 32, 32)
    }

    components: [
        sprite
    ]
}
