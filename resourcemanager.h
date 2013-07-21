#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QObject>

class TextureAssetManager;
class ShaderAssetManager;

class AssetManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TextureAssetManager *textures MEMBER textures);
    Q_PROPERTY(ShaderAssetManager *shaders MEMBER shaders);

public:
    explicit AssetManager(QObject *parent = 0);
    
    TextureAssetManager *textures;
    ShaderAssetManager *shaders;
};

#endif // RESOURCESMANAGER_H
