#ifndef SCENE_H
#define SCENE_H

#include "resourcemanager.h"
#include "tilemap.h"
#include "initialisationvisitor.h"
#include "updatevisitor.h"

#include <QQuickItem>

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(AssetManager* resources MEMBER m_resources)
    Q_PROPERTY(TileMap* tilemap MEMBER m_tilemap)
    Q_PROPERTY(QVector2D cameraPosition MEMBER m_cameraPosition NOTIFY cameraPositionUpdated)
    Q_PROPERTY(QVector<Actor *> actors MEMBER m_actors)

public:
    explicit Scene(QQuickItem *parent = 0);

signals:
    void cameraPositionUpdated(QVector2D position);

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void initialiseOpenGl();
    void draw();

private:
    AssetManager *m_resources;
    TileMap *m_tilemap;

    InitialisationVisitor m_initialisationVisitor;
    UpdateVisitor m_updateVsisitor;
    QVector<Actor *> m_actors;
    QVector2D m_cameraPosition;
};

#endif // SCENE_H
