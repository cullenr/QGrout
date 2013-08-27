#ifndef ACTOR_H
#define ACTOR_H

#include <QMatrix4x4>
#include <QObject>
#include "visitee.h"

class Actor : public QObject, public Visitee
{
    Q_OBJECT
    Q_PROPERTY(QList<Visitee *> components MEMBER m_components)

public:
    explicit Actor(QObject *parent = 0);
    void accept(Visitor &visitor) override;

    QList<Visitee *> components() const;
private:
    QList<Visitee *> m_components;
    QMatrix4x4 m_transform;
};

#endif // ACTOR_H
