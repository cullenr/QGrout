#ifndef SCENE_H
#define SCENE_H

#include "resourcemanager.h"
#include <QQuickItem>

class Scene : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(AssetManager* resources MEMBER resources)

public:
    explicit Scene(QQuickItem *parent = 0);

    AssetManager *resources;
signals:

public slots:

protected:
    virtual void componentComplete();

private:
};

#endif // SCENE_H
