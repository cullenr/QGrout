#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QQuickWindow>
#include <QHash>
#include <QtCore/QList>
#include <QString>

//namespace QG
//{
class TextureAssetManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QString> texturePaths MEMBER texturePaths NOTIFY texturePathsUpdated);

public:
    explicit TextureAssetManager(QObject *parent = 0);

    void loadTextures(QQuickWindow *window);

    QList<QString> texturePaths;
private:
    QHash<QString, GLuint> m_textures;


signals:
    void ready();
    void texturePathsUpdated(QList<QString>);
public slots:

};
//}

#endif // RESOURCEMANAGER_H
