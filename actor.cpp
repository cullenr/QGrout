#include "actor.h"
#include "sceneitemupdatevisitor.h"

Actor::Actor(QObject *parent) :
    AbstractGameObject(parent)
{
}

void Actor::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
}

QList<SceneElementInterface *> Actor::components() const
{
    return m_components;
}

void Actor::addComponent(SceneItem *component)
{
    if(!m_components.contains(component))
        m_components.append(component);
    else
        qWarning("Attempt to add a component twice.");
}

void Actor::removeComponent(SceneItem *component)
{
    if(m_components.contains(component))
        m_components.removeOne(component);
    else
        qWarning("Component is not contained in component list, it cannot be removed.");
}

