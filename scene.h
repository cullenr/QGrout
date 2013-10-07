#ifndef SCENE_H
#define SCENE_H

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlListProperty>

#include "tilemap.h"
#include "layer.h"
#include "sceneiteminitvisitor.h"
#include "sceneitemupdatevisitor.h"
#include "abstractasset.h"
#include "assetinitialisationvisitor.h"

class Scene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QVector2D cameraPosition MEMBER m_cameraPosition NOTIFY cameraPositionUpdated)
    Q_PROPERTY(QQmlListProperty<Layer> layers READ layersQmlList NOTIFY layersUpdated)
    Q_PROPERTY(QQmlListProperty<AbstractSceneItem> components READ componentsQmlList NOTIFY componentsUpdated)

public:
    explicit Scene(QQuickItem *parent = 0);
    bool event(QEvent *event) override;

signals:
    void cameraPositionUpdated(QVector2D position);
    void layersUpdated(QList<Layer *> layers);
    void componentsUpdated(QList<AbstractSceneItem*> components);

private slots:
    void handleWindowChanged(QQuickWindow *window);
    void initialiseOpenGl();
    void draw();

private:
    QQmlListProperty<Layer> layersQmlList();
    QQmlListProperty<AbstractSceneItem> componentsQmlList();

    QList<Layer *> m_layers;
    QList<AbstractSceneItem *> m_components;
    QVector<AbstractAsset *> m_assets;
    QVector2D m_cameraPosition;

    //visitors
    SceneItemInitVisitor m_initialisationVisitor;
    AssetInitialisationVisitor m_assetInitialisationVisitor;
    SceneItemUpdateVisitor m_updateVsisitor;
};

#endif // SCENE_H
