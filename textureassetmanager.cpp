#include "textureassetmanager.h"
#include <QSGTexture>
#include <QImage>

TextureAssetManager::TextureAssetManager(QObject *parent) :
    QObject(parent)
{
}


void TextureAssetManager::loadTextures(QQuickWindow *window)
{
    for(int i = 0; i < texturePaths.length(); i++)
    {
        QSGTexture *texture = window->createTextureFromImage(QImage(texturePaths[i]));

        m_textures.insert(texturePaths[i], texture->textureId());
    }
}
