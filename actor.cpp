#include "actor.h"
#include "sceneitemvisitor.h"

Actor::Actor(QObject *parent) :
    AbstractSceneItem(parent)
{
}

void Actor::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
}

QList<AbstractSceneItem *> Actor::components() const
{
    return m_components;
}

QQmlListProperty<AbstractSceneItem> Actor::componentsQmlList()
{
    return QQmlListProperty<AbstractSceneItem>(this, m_components);
}
