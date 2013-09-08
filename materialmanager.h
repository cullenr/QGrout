#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <QQmlListProperty>
#include "gobject.h"
#include "material.h"

class TextureAssetManager;
class ShaderAssetManager;

class MaterialManager : public GObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Material> sources READ sourcesQmlList() NOTIFY sourcesUpdated);
    Q_CLASSINFO("DefaultProperty", "sources")
public:
    explicit MaterialManager(QObject *parent = 0);

    void setTextureManager(TextureAssetManager *textureAssetManager);
    void setShaderManager(ShaderAssetManager *shaderAssetManager);

signals:
    void sourcesUpdated(QList<Material *> sources);

protected:
    QQmlListProperty<Material> sourcesQmlList();

    QList<Material *> m_sources;

private:
    TextureAssetManager *m_textureManager;
    ShaderAssetManager *m_shaderManager;
};

#endif // MATERIALMANAGER_H
