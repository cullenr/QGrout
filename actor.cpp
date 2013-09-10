#include "actor.h"

#include "initialisationvisitor.h"
#include "updatevisitor.h"

Actor::Actor(QObject *parent) :
    AbstractGameObject(parent)
{
}

void Actor::accept(SceneElementVisitor &visitor)
{
    visitor.visit(*this);
}

QList<SceneElement *> Actor::components() const
{
    return m_components;
}

void InitialisationVisitor::visit(Actor &actor)
{
    for(SceneElement *SceneElement : actor.components())
    {
        SceneElement->accept(*this);
    }
}

void UpdateVisitor::visit(Actor &actor)
{
    for(SceneElement *SceneElement : actor.components())
    {
        SceneElement->accept(*this);
    }
}


