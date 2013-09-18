#include "spritecomponent.h"
#include "sceneitemvisitor.h"

SpriteComponent::SpriteComponent(QObject *parent) :
    SceneItem(parent)
{
}

void SpriteComponent::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
}

QRect SpriteComponent::textureRect() const
{
    return m_textureRect;
}

Material *SpriteComponent::material() const
{
    return m_material;
}

Mesh SpriteComponent::mesh() const
{
    return m_mesh;
}
