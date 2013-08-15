#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QObject>

class TextureAssetManager;
class ShaderAssetManager;
class MaterialManager;

class AssetManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextureAssetManager * textures MEMBER m_textureManager);
    Q_PROPERTY(ShaderAssetManager * shaders MEMBER m_shaderManager);
    Q_PROPERTY(MaterialManager * materials MEMBER m_materialManager WRITE setMaterialManager);

public:
    explicit AssetManager(QObject *parent = 0);

    ShaderAssetManager *shaderManager();
    TextureAssetManager *textureManager();
    MaterialManager *materialManager();
    void setMaterialManager(MaterialManager *materialManager);

private:
    ShaderAssetManager *m_shaderManager;
    TextureAssetManager *m_textureManager;
    MaterialManager *m_materialManager;
};

#endif // RESOURCESMANAGER_H
