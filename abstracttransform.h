#ifndef ABSTRACTTRANSFORM_H
#define ABSTRACTTRANSFORM_H
#include "abstractsceneitem.h"

class AbstractTransform : public AbstractSceneItem
{
public:
    explicit AbstractTransform(QObject *parent = 0);

    virtual QVector2D position() const;
    virtual void setPosition(const Qvector2D &pos);

    virtual float rotation() const;
    virtual void setRotation(const float &pos);
};

#endif // ABSTRACTTRANSFORM_H
