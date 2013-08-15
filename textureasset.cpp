#include "textureasset.h"

TextureAsset::TextureAsset(QObject *parent) :
    QObject(parent)
{
}

const QString TextureAsset::texturePath() const
{
    return m_texturePath;
}

QSGTexture *TextureAsset::texture() const
{
    return m_texture;
}

void TextureAsset::setTexture(QSGTexture *texture)
{
    m_texture = texture;
}
