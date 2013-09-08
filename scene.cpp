#include <QCoreApplication>
#include "scene.h"
#include "shaderassetmanager.h"
#include "textureassetmanager.h"
#include "actor.h"
#include "assetcreatedevent.h"

Scene::Scene(QQuickItem *parent) :
    GQuickItem(parent)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

bool Scene::event(QEvent *event)
{
    if(event->type() == AssetCreatedEvent::AssetCreatedType)
    {
        AssetCreatedEvent *assetEvent = static_cast<AssetCreatedEvent *>(event);

        m_assets.append(assetEvent->asset());

        qDebug("Yippee");

        return false;
    }

    return QQuickItem::event(event);
}


void Scene::handleWindowChanged(QQuickWindow *window)
{
    if(window)
    {
        connect(window, SIGNAL(sceneGraphInitialized()), this, SLOT(initialiseOpenGl()), Qt::DirectConnection);
    }
}
void Scene::initialiseOpenGl()
{
    glDisable(GL_DEPTH);
    glEnable(GL_TEXTURE_2D);

    if(m_resources->shaderManager() != nullptr)
        m_resources->shaderManager()->initialiseShaders();

    if(m_resources->textureManager() != nullptr)
        m_resources->textureManager()->loadTextures(window());

    m_tilemap->accept(m_initialisationVisitor);

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
    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f); // put this in the tilemap, we should be able to have several seperate tilemaps with their own projection and viewport

    m_updateVsisitor.setViewMatrix(viewMatrix);
    m_updateVsisitor.setProjectionMatrix(projectionMatrix);

    m_tilemap->accept(m_updateVsisitor);

    for(Actor *actor : m_actors)
        actor->accept(m_updateVsisitor);
}
