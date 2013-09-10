#include "spritecomponent.h"
#include "sceneelementvisitor.h"
#include "updatevisitor.h"
#include "initialisationvisitor.h"

SpriteComponent::SpriteComponent(QObject *parent) :
    QObject(parent)
{
}

void SpriteComponent::accept(SceneElementVisitor &visitor)
{
    visitor.visit(*this);
}

void InitialisationVisitor::visit(SpriteComponent &spriteComponent)
{

}

void UpdateVisitor::visit(SpriteComponent &spriteComponent)
{

}
