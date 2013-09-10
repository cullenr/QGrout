#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <QObject>
#include "sceneelement.h"

class Material;

class SpriteComponent : public QObject, public SceneElement
{
    Q_OBJECT
    Q_PROPERTY(Material *material MEMBER m_material);

public:
    explicit SpriteComponent(QObject *parent = 0);
    
    void accept(SceneElementVisitor &visitor) override;

private:
    Material *m_material;
    
};

#endif // SPRITECOMPONENT_H
