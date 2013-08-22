#include "textureassetmanager.h"
#include <QSGTexture>
#include <QImage>

TextureAssetManager::TextureAssetManager(QObject *parent) :
    QObject(parent)
{
}

TextureAssetManager::~TextureAssetManager()
{
    for(TextureAsset *textureAsset : m_textureSources)
    {
        //TODO: CLEANUP!
    }
}

void TextureAssetManager::loadTextures(QQuickWindow *window)
{
    for(int i = 0; i < m_textureSources.length(); i++)
    {
        TextureAsset *textureAsset = m_textureSources[i];
        QSGTexture *texture = window->createTextureFromImage(QImage(m_textureSources[i]->texturePath()));// TODO profile this, is this a leak or an r-value?

        textureAsset->setTexture(texture);
    }
}

QQmlListProperty<TextureAsset> TextureAssetManager::m_textureSourcesQmlList()
{
    return QQmlListProperty<TextureAsset>(this, m_textureSources);
}
