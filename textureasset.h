#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include <qopengl.h>
#include <QObject>
#include "abstractasset.h"

class TextureAsset : public AbstractAsset
{
    Q_OBJECT
    Q_PROPERTY(QString texturePath MEMBER m_texturePath)
    Q_CLASSINFO("DefaultProperty", "texturePath")

public:
    explicit TextureAsset(QObject *parent = 0);

    void accept(AssetVisitor &visitor) override;

    const QString texturePath() const;

    GLuint glTextureId() const;
    void setGlTextureId(const GLuint &glTextureId);

    int textureWidth() const;
    void setTextureWidth(int textureWidth);

    int textureHeight() const;
    void setTextureHeight(int textureHeight);

private:
    GLuint m_glTextureId;
    QString m_texturePath;
    int m_textureWidth;
    int m_textureHeight;
};

#endif // TEXTUREASSET_H
