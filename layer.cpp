#include "layer.h"
#include "sceneitemvisitor.h"

Layer::Layer(QObject *parent) :
    AbstractSceneItem(parent)
{
}

void Layer::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
}

QQmlListProperty<Actor> Layer::actorsQmlList()
{
    return QQmlListProperty<Actor>(this, m_actors);
}

AbstractSceneItem *Layer::visualLayer() const
{
    return m_visualLayer;
}

QList<Actor *> Layer::actors() const
{
    return m_actors;
}
