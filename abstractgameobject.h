#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QtCore/QObject>
#include <QtGui/QVector2D>
#include "sceneelementinterface.h"

class AbstractGameObject :
        public QObject,
        public SceneElementInterface
{
    Q_OBJECT
    Q_PROPERTY(QVector2D position MEMBER m_position NOTIFY positionChanged)
public:
    explicit AbstractGameObject(QObject *parent = 0);

    QVector2D position() const;
    void setPosition(const QVector2D &position);

signals:
    void positionChanged(QVector2D position);

private:
    QVector2D m_position;
};

#endif // GAMEOBJECT_H
