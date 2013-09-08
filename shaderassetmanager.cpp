#include "shaderassetmanager.h"
#include "shaderasset.h"
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QtDebug>
#include <locale.h>

ShaderAssetManager::ShaderAssetManager(QObject *parent) :
    GObject(parent)
{
}

ShaderAssetManager::~ShaderAssetManager()
{
}

QQmlListProperty<ShaderAsset> ShaderAssetManager::m_shaderSourcesQmlList()
{
    return QQmlListProperty<ShaderAsset>(this, m_shaderSources);
}

void ShaderAssetManager::initialiseShaders()
{
    //aparently not setting the locale this way can mess up shader compilation.
    setlocale(LC_NUMERIC, "C");

    for (int i = 0; i < m_shaderSources.length(); ++i)
    {
        ShaderAsset *shader = m_shaderSources[i];

        if (!shader->compile())
            qWarning() << shader->shader()->log();
    }

    setlocale(LC_ALL, "");
}
