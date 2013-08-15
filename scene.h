#ifndef SCENE_H
#define SCENE_H

#include "resourcemanager.h"
#include <QQuickItem>

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(AssetManager* resources MEMBER m_resources)

public:
    explicit Scene(QQuickItem *parent = 0);

private slots:
    void m_handleWindowChanged(QQuickWindow *window);
    virtual void m_initialiseOpenGl();

private:
    AssetManager *m_resources;
};

#endif // SCENE_H
