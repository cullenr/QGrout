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

    //maybe used the gameobject find method here instead of manualy adding and removing.
    onInit: {
        var a = sprite;
        //console.trace(sprite);
        hero.addComponent(sprite);
    }
}
