#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <QObject>

#include "visitee.h"

class Material;

class SpriteComponent : public QObject, public Visitee
{
    Q_OBJECT
    Q_PROPERTY(Material *material MEMBER m_material);

public:
    explicit SpriteComponent(QObject *parent = 0);
    
    void accept(Visitor &visitor) override;

private:
    Material *m_material;
    
};

#endif // SPRITECOMPONENT_H
