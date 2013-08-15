#include "resourcemanager.h"
#include "materialmanager.h"

AssetManager::AssetManager(QObject *parent) :
    QObject(parent)
{
}

void AssetManager::setMaterialManager(MaterialManager *materialManager)
{
    m_materialManager = materialManager;
    m_materialManager->setShaderManager(m_shaderManager);
    m_materialManager->setTextureManager(m_textureManager);
}

ShaderAssetManager * AssetManager::shaderManager()
{
    return m_shaderManager;
}

TextureAssetManager * AssetManager::textureManager()
{
    return m_textureManager;
}

MaterialManager * AssetManager::materialManager()
{
    return m_materialManager;
}
