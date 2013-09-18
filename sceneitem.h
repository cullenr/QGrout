#ifndef SCENEELEMENT_H
#define SCENEELEMENT_H

#include <QObject>

#include "sceneelementinterface.h"

class SceneItem : public QObject, public SceneElementInterface
{
    Q_OBJECT
public:
    explicit SceneItem(QObject *parent = 0);
};

#endif // SCENEELEMENT_H
