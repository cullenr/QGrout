#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <QtCore/QRect>
#include <QtCore/QObject>
#include "abstractsceneitem.h"
#include "mesh.h"
#include "sceneitemupdatevisitor.h"
#include "sceneiteminitvisitor.h"

class Material;

class SpriteComponent :
        public AbstractSceneItem
{
    Q_OBJECT
    Q_PROPERTY(Material * material MEMBER m_material);
    Q_PROPERTY(QRect textureCoordinates MEMBER m_textureRect);

public:
    explicit SpriteComponent(QObject *parent = 0);
    
    void accept(SceneItemVisitor &visitor) override;

    QRect textureRect() const;
    Material *material() const;
    Mesh mesh() const;

private:
    Material *m_material;
    Mesh m_mesh;
    QRect m_textureRect;

    friend void SceneItemInitVisitor::visit(SpriteComponent &spriteComponent);
};

#endif // SPRITECOMPONENT_H
