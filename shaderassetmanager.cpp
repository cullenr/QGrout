#include "shaderassetmanager.h"
#include "shaderasset.h"
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QtDebug>
#include <locale.h>

ShaderAssetManager::ShaderAssetManager(QObject *parent) :
    QObject(parent)
{
}

ShaderAssetManager::~ShaderAssetManager()
{
    //delete all QOpenGLShaderProgram
}

QQmlListProperty<ShaderAsset> ShaderAssetManager::m_shaderSourcesQmlList()
{
    return QQmlListProperty<ShaderAsset>(this, m_shaderSources);
}

void ShaderAssetManager::addShader(QList<ShaderAsset *> shaders, QQuickWindow *window)
{
    for (int i = 0; i < shaders.length(); ++i)
    {
        addShader(shaders[i], window);
    }
}

void ShaderAssetManager::addShader(ShaderAsset *shader, QQuickWindow *window)
{
    QOpenGLShaderProgram* program = new QOpenGLShaderProgram();

    setlocale(LC_NUMERIC, "C");

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, shader->vertexShaderPath) &&
        !program->addShaderFromSourceFile(QOpenGLShader::Fragment, shader->fragmentShaderPath) &&
        !program->link())
    {
        qWarning() << program->log();
    }

    setlocale(LC_ALL, "");

    m_shaders.insert(shader->objectName(), program);
}
