#ifndef ACTOR_H
#define ACTOR_H

#include <QtGui/QMatrix4x4>
#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>
#include "sceneelementinterface.h"
#include "abstractgameobject.h"
#include "abstractsceneitem.h"

class Actor : public AbstractGameObject
{
    Q_OBJECT
public:
    explicit Actor(QObject *parent = 0);

    void accept(SceneItemVisitor &visitor) override;
    Q_INVOKABLE void addComponent(AbstractSceneItem * component);
    Q_INVOKABLE void removeComponent(AbstractSceneItem * component);

    QList<SceneElementInterface *> components() const;

signals:
    void init();

private:
    QList<SceneElementInterface *> m_components;
};

#endif // ACTOR_H
