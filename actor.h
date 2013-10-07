#ifndef ACTOR_H
#define ACTOR_H

#include <QtGui/QMatrix4x4>
#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>
#include "abstractsceneitem.h"

class Actor : public AbstractSceneItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<AbstractSceneItem> components READ componentsQmlList NOTIFY componentsUpdated);

public:
    explicit Actor(QObject *parent = 0);

    void accept(SceneItemVisitor &visitor) override;

    QList<AbstractSceneItem *> components() const;
    QQmlListProperty<AbstractSceneItem> componentsQmlList();
signals:
    void init();
    void componentsUpdated(QList<AbstractSceneItem *> components);

private:
    QList<AbstractSceneItem *> m_components;
};

#endif // ACTOR_H
