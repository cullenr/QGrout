#include "actor.h"

#include "initialisationvisitor.h"
#include "updatevisitor.h"

Actor::Actor(QObject *parent) :
    GObject(parent)
{
}

void Actor::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

QList<Visitee *> Actor::components() const
{
    return m_components;
}

void InitialisationVisitor::visit(Actor &actor)
{
    for(Visitee *visitee : actor.components())
    {
        visitee->accept(*this);
    }
}

void UpdateVisitor::visit(Actor &actor)
{
    for(Visitee *visitee : actor.components())
    {
        visitee->accept(*this);
    }
}


