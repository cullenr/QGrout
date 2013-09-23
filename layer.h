#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include "abstractsceneitem.h"
#include "actor.h"

class Layer : public AbstractSceneItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Actor> actors READ actorsQmlList NOTIFY actorsUpdated)
    Q_PROPERTY(AbstractSceneItem *visualElement MEMBER m_visualLayer)
    Q_PROPERTY(AbstractSceneItem *physicsElement MEMBER m_physicsLayer)

public:
    explicit Layer(QObject *parent = 0);

    void accept(SceneItemVisitor &visitor);

    QQmlListProperty<Actor> actorsQmlList();
    QList<Actor *> actors() const;
    AbstractSceneItem *physicsLayer() const;
    AbstractSceneItem *visualLayer() const;

signals:
    void actorsUpdated(QList<Actor *> actors);

private:
    AbstractSceneItem *m_physicsLayer;
    AbstractSceneItem *m_visualLayer;
    QList<Actor *> m_actors;
};

#endif // LAYER_H
