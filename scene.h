#ifndef SCENE_H
#define SCENE_H

#include <QQuickItem>

#include "tilemap.h"
#include "initialisationvisitor.h"
#include "updatevisitor.h"
#include "abstractasset.h"
#include "assetinitialisationvisitor.h"

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(TileMap* tilemap MEMBER m_tilemap)
    Q_PROPERTY(QVector2D cameraPosition MEMBER m_cameraPosition NOTIFY cameraPositionUpdated)
    Q_PROPERTY(QVector<Actor *> actors MEMBER m_actors)

public:
    explicit Scene(QQuickItem *parent = 0);
    bool event(QEvent *event) override;

signals:
    void cameraPositionUpdated(QVector2D position);

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void initialiseOpenGl();
    void draw();

private:
    TileMap *m_tilemap;
    QVector<Actor *> m_actors;
    QVector<AbstractAsset *> m_assets;
    QVector2D m_cameraPosition;

    //visitors
    InitialisationVisitor m_initialisationVisitor;
    AssetInitialisationVisitor m_assetInitialisationVisitor;
    UpdateVisitor m_updateVsisitor;
};

#endif // SCENE_H
