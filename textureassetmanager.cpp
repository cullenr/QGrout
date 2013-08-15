#include "textureassetmanager.h"
#include <QSGTexture>
#include <QImage>

TextureAssetManager::TextureAssetManager(QObject *parent) :
    QObject(parent)
{
}

TextureAssetManager::~TextureAssetManager()
{
    //TODO FREE
}

void TextureAssetManager::loadTextures(QQuickWindow *window)
{
    for(int i = 0; i < m_textureSources.length(); i++)
    {
        TextureAsset *textureAsset = m_textureSources[i];
        QSGTexture *texture = window->createTextureFromImage(QImage(m_textureSources[i]->texturePath()));

        textureAsset->setTexture(texture);
    }
}

QQmlListProperty<TextureAsset> TextureAssetManager::m_textureSourcesQmlList()
{
    return QQmlListProperty<TextureAsset>(this, m_textureSources);
}
