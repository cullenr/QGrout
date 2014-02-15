#ifndef ABSTRACTTRANSFORM_H
#define ABSTRACTTRANSFORM_H
#include "abstractsceneitem.h"

class AbstractTransform : public AbstractSceneItem
{
public:
    explicit AbstractTransform(QObject *parent = 0);

    virtual QVector2D position() const = 0;
    virtual void setPosition(const QVector2D &pos) = 0;

    virtual float rotation() const = 0;
    virtual void setRotation(const float &pos) = 0;
};

#endif // ABSTRACTTRANSFORM_H
