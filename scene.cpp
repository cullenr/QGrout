#include <QCoreApplication>
#include <QQuickWindow>
#include "scene.h"
#include "actor.h"
#include "assetcreatedevent.h"

Scene::Scene(QQuickItem *parent) :
    QQuickItem(parent)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this,
            SLOT(handleWindowChanged(QQuickWindow*)));
}

bool Scene::event(QEvent *event)
{
    if(event->type() == AssetCreatedEvent::AssetCreatedType)
    {
        AssetCreatedEvent *assetEvent = static_cast<AssetCreatedEvent *>(event);
        AbstractAsset *asset = assetEvent->asset();

        // TODO : CREATE A SETTER FOR THIS FUNCTION AND APPLY THE INIT VISITOR
        if(!m_assets.contains(asset))
            m_assets.append(asset);

        return true;
    }

    return QQuickItem::event(event);
}


void Scene::handleWindowChanged(QQuickWindow *window)
{
    if(window)
    {
        connect(window, SIGNAL(sceneGraphInitialized()), this, SLOT(initialiseOpenGl()),
                Qt::DirectConnection);
    }
}

void Scene::initialiseOpenGl()
{
    glDisable(GL_DEPTH);
    glEnable(GL_TEXTURE_2D);

    QList<AbstractAsset *> assets = findChildren<AbstractAsset *>();

    for(int i = 0; i < assets.length(); ++i)
        assets[i]->accept(m_assetInitialisationVisitor);

    for(Layer *layer : m_layers)
        layer->accept(m_initialisationVisitor);

    window()->setClearBeforeRendering(false);
    connect(window(), SIGNAL(beforeRendering()), this, SLOT(draw()), Qt::DirectConnection);
}

void Scene::draw()
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(m_cameraPosition.x(), m_cameraPosition.y());

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    // put this in the tilemap, we should be able to have several seperate tilemaps with their own
    //projection and viewport
    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);

    m_updateVsisitor.setViewMatrix(viewMatrix);
    m_updateVsisitor.setProjectionMatrix(projectionMatrix);

    for(Layer *layer : m_layers)
        layer->accept(m_updateVsisitor);
}

QQmlListProperty<Layer> Scene::layersQmlList()
{
    return QQmlListProperty<Layer>(this, m_layers);
}

QQmlListProperty<AbstractSceneItem> Scene::componentsQmlList()
{
    return QQmlListProperty<AbstractSceneItem>(this, m_components);
}
