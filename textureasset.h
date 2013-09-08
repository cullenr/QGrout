#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include <qopengl.h>
#include "gobject.h"
#include "abstractasset.h"

class TextureAsset : public GObject, public AbstractAsset
{
    Q_OBJECT
    Q_PROPERTY(QString texturePath MEMBER m_texturePath)
    Q_CLASSINFO("DefaultProperty", "texturePath")

public:
    explicit TextureAsset(QObject *parent = 0);

    const QString texturePath() const;
    const GLuint glTextureId() const;
    void setGlTextureId(const GLuint &glTextureId);

    //AbstractAsset
    void accept(AssetVisitor &visitor) override;
    void classBegin() override;
    void componentComplete() override;

private:
    GLuint m_glTextureId;
    QString m_texturePath;
};

#endif // TEXTUREASSET_H
