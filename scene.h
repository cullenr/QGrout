#ifndef SCENE_H
#define SCENE_H

#include "resourcemanager.h"
#include "tilemap.h"
#include "initialisationvisitor.h"
#include "drawvisitor.h"

#include <QQuickItem>

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(AssetManager* resources MEMBER m_resources)
    Q_PROPERTY(TileMap* tilemap MEMBER m_tilemap)

public:
    explicit Scene(QQuickItem *parent = 0);

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void initialiseOpenGl();
    void draw();

private:
    AssetManager *m_resources;
    TileMap *m_tilemap;

    InitialisationVisitor m_initialisationVisitor;
    DrawVisitor m_drawVisitor;
};

#endif // SCENE_H
