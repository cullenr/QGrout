#include <QtCore/QtGlobal>
#include "textureasset.h"
#include "assetvisitor.h"

TextureAsset::TextureAsset(QObject *parent) :
    AbstractAsset(parent),
    m_glTextureId(-1),
    m_textureWidth(-1),
    m_textureHeight(-1)
{
}

void TextureAsset::accept(AssetVisitor &visitor)
{
    visitor.visit(*this);
}

GLuint TextureAsset::glTextureId() const
{
    return m_glTextureId;
}

void TextureAsset::setGlTextureId(const GLuint &glTextureId)
{
    m_glTextureId = glTextureId;
}

int TextureAsset::textureWidth() const
{
    return m_textureWidth;
}

void TextureAsset::setTextureWidth(int textureWidth)
{
    m_textureWidth = textureWidth;
}
int TextureAsset::textureHeight() const
{
    return m_textureHeight;
}

void TextureAsset::setTextureHeight(int textureHeight)
{
    m_textureHeight = textureHeight;
}

const QString TextureAsset::texturePath() const
{
    return m_texturePath;
}
