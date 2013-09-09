#include "materialmanager.h"

MaterialManager::MaterialManager(QObject *parent) :
    QObject(parent)
{
}

void MaterialManager::setTextureManager(TextureAssetManager *textureAssetManager)
{
    m_textureManager = textureAssetManager;
}

void MaterialManager::setShaderManager(ShaderAssetManager *shaderAssetManager)
{
    m_shaderManager = shaderAssetManager;
}

QQmlListProperty<Material> MaterialManager::sourcesQmlList()
{
    return QQmlListProperty<Material>(this, m_sources);
}
