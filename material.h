#ifndef MATERIALSOURCE_H
#define MATERIALSOURCE_H

#include <QtCore/QObject>
#include "abstractsceneitem.h"

class TextureAsset;
class ShaderAsset;

class Material : public AbstractSceneItem
{
    Q_OBJECT
    Q_PROPERTY(ShaderAsset *shader MEMBER m_shader);
    Q_PROPERTY(TextureAsset *texture MEMBER m_texture);
public:
    explicit Material(QObject *parent = 0);

    void accept(SceneItemVisitor &visitor) override;

    ShaderAsset *shader() const;
    TextureAsset *texture() const;

    virtual void bind(QMatrix4x4 &mvpMatrix);
    virtual void release();

private:
    ShaderAsset *m_shader;
    TextureAsset *m_texture;
};

#endif // MATERIALSOURCE_H
