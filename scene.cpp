#include "scene.h"
#include <QtDebug>
#include "shaderassetmanager.h"
#include "textureassetmanager.h"

Scene::Scene(QQuickItem *parent) :
    QQuickItem(parent)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(m_handleWindowChanged(QQuickWindow*)));
}

void Scene::m_handleWindowChanged(QQuickWindow *window)
{
    if(window)
    {
        connect(window, SIGNAL(sceneGraphInitialized()), this, SLOT(m_initialiseOpenGl()), Qt::DirectConnection);
    }
}
void Scene::m_initialiseOpenGl()
{
    if(m_resources->shaderManager() != NULL)
    {
        m_resources->textureManager()->loadTextures(window());
        m_resources->shaderManager()->initialiseShaders();
    }
}
