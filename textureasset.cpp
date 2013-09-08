#include <QCoreApplication>
#include "textureasset.h"
#include "assetcreatedevent.h"
#include "assetvisitor.h"

TextureAsset::TextureAsset(QObject *parent) :
    AbstractAsset(parent),
    m_glTextureId(-1)
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


const QString TextureAsset::texturePath() const
{
    return m_texturePath;
}
