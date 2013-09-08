#include "spritecomponent.h"
#include "visitor.h"
#include "updatevisitor.h"
#include "initialisationvisitor.h"

SpriteComponent::SpriteComponent(QObject *parent) :
    GObject(parent)
{
}

void SpriteComponent::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void InitialisationVisitor::visit(SpriteComponent &spriteComponent)
{

}

void UpdateVisitor::visit(SpriteComponent &spriteComponent)
{

}
