#ifndef SCENE_H
#define SCENE_H

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlListProperty>

#include "tilemap.h"
#include "sceneiteminitvisitor.h"
#include "sceneitemupdatevisitor.h"
#include "abstractasset.h"
#include "assetinitialisationvisitor.h"

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(TileMap * tilemap MEMBER m_tilemap NOTIFY tileMapUpdated)
    Q_PROPERTY(QVector2D cameraPosition MEMBER m_cameraPosition NOTIFY cameraPositionUpdated)
    Q_PROPERTY(QQmlListProperty<Actor> actors READ actorsQmlList NOTIFY actorsUpdated)

public:
    explicit Scene(QQuickItem *parent = 0);
    bool event(QEvent *event) override;

signals:
    void cameraPositionUpdated(QVector2D position);
    void tileMapUpdated(TileMap *tileMap);
    void actorsUpdated(QList<Actor *> actors);

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void initialiseOpenGl();
    void draw();

private:
    QQmlListProperty<Actor> actorsQmlList();

    TileMap *m_tilemap;
    QList<Actor *> m_actors;
    QVector<AbstractAsset *> m_assets;
    QVector2D m_cameraPosition;

    //visitors
    SceneItemInitVisitor m_initialisationVisitor;
    AssetInitialisationVisitor m_assetInitialisationVisitor;
    SceneItemUpdateVisitor m_updateVsisitor;
};

#endif // SCENE_H
