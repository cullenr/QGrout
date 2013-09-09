#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QQuickWindow>
#include <QList>
#include <QQmlListProperty>
#include <QString>
#include <QObject>
#include "textureasset.h"

class TextureAssetManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<TextureAsset> textureSources READ m_textureSourcesQmlList NOTIFY textureSourceUpdated);
    Q_CLASSINFO("DefaultProperty", "textureSources")

public:
    explicit TextureAssetManager(QObject *parent = 0);
    ~TextureAssetManager();

    void loadTextures(QQuickWindow *window);

private:
    QQmlListProperty<TextureAsset> m_textureSourcesQmlList();
    QList<TextureAsset *> m_textureSources;

signals:
    void textureSourceUpdated(QList<QSGTexture *>);
public slots:

};

#endif // RESOURCEMANAGER_H
