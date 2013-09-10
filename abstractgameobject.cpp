#include "abstractgameobject.h"

AbstractGameObject::AbstractGameObject(QObject *parent) :
    QObject(parent)
{
}

QVector2D AbstractGameObject::position() const
{
    return m_position;
}

void AbstractGameObject::setPosition(const QVector2D &position)
{
    m_position = position;
}

