#ifndef ACTOR_H
#define ACTOR_H

#include <QtGui/QMatrix4x4>
#include <QtCore/QObject>
#include "sceneelement.h"
#include "abstractgameobject.h"

class Actor : public AbstractGameObject
{
    Q_OBJECT
    Q_PROPERTY(QList<SceneElement *> components MEMBER m_components)

public:
    explicit Actor(QObject *parent = 0);
    void accept(SceneElementVisitor &visitor) override;

    QList<SceneElement *> components() const;
private:
    QList<SceneElement *> m_components;
    QMatrix4x4 m_transform;
};

#endif // ACTOR_H
