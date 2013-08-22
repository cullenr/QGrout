#include "scene.h"
#include <QtDebug>
#include "shaderassetmanager.h"
#include "textureassetmanager.h"

Scene::Scene(QQuickItem *parent) :
    QQuickItem(parent)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
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
    m_tilemap->accept(m_drawVisitor);
}
