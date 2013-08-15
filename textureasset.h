#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include <QObject>

class QSGTexture;

class TextureAsset : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString texturePath MEMBER m_texturePath)
    Q_CLASSINFO("DefaultProperty", "texturePath")

public:
    explicit TextureAsset(QObject *parent = 0);
    
    const QString texturePath() const;
    QSGTexture *texture() const;
    void setTexture(QSGTexture *texture);

private:
    QString m_texturePath;
    QSGTexture *m_texture;
};

#endif // TEXTUREASSET_H
