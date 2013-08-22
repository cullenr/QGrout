#ifndef MATERIALSOURCE_H
#define MATERIALSOURCE_H

#include <QObject>
#include <QStringList>
#include <QString>

class TextureAsset;
class ShaderAsset;

class Material : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ShaderAsset *shader MEMBER m_shader);
    Q_PROPERTY(TextureAsset *texture MEMBER m_texture);
public:
    explicit Material(QObject *parent = 0);

    ShaderAsset *shader() const;
    TextureAsset *texture() const;

    virtual void bind(QMatrix4x4 &mvpMatrix);
    virtual void release();

private:
    ShaderAsset *m_shader;
    TextureAsset *m_texture;
};

#endif // MATERIALSOURCE_H
