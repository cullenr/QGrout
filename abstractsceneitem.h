#ifndef SCENEELEMENT_H
#define SCENEELEMENT_H

#include <QObject>

#include "sceneelementinterface.h"

class AbstractSceneItem : public QObject, public SceneElementInterface
{
    Q_OBJECT
public:
    explicit AbstractSceneItem(QObject *parent = 0);
};

#endif // SCENEELEMENT_H
