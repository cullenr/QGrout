#include <QCoreApplication>
#include "textureasset.h"
#include "assetcreatedevent.h"
#include "assetvisitor.h"

TextureAsset::TextureAsset(QObject *parent) :
    GObject(parent)
{
}

void TextureAsset::accept(AssetVisitor &visitor)
{
    visitor.visit(*this);
}

void TextureAsset::classBegin()
{
    //not used
}

void TextureAsset::componentComplete()
{
    //new asset gets deleted by the even system

    QObject *p = parent();

    QCoreApplication::postEvent(parent(), new AssetCreatedEvent());
}

const GLuint TextureAsset::glTextureId() const
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
