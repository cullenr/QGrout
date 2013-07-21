#ifndef SHADERASSETMANAGER_H
#define SHADERASSETMANAGER_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QList>
#include <QQmlListProperty>

#include "shaderasset.h"

class QOpenGLShaderProgram;
//class ShaderAsset;
class QQuickWindow;

class ShaderAssetManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ShaderAsset> shaderSources READ m_shaderSourcesQmlList NOTIFY shaderSourceUpdated);
    Q_CLASSINFO("DefaultProperty", "shaderSources")

public:
    explicit ShaderAssetManager(QObject *parent = 0);
    ~ShaderAssetManager();

    /**
     * @brief addShader add a shader to the manager
     * @param shaders a list of shaderAssets to be added.
     * @param window the window to add the shaders to, the window is required to generate the openGl textures in the correct context
     */
    void addShader(QList<ShaderAsset *> shaders, QQuickWindow *window);
    void addShader(ShaderAsset *shader, QQuickWindow *window);
    void addShader(QQuickWindow *wondow);


    /**
     * @brief getShader by the shader name
     * @param name this is the equal to the objectName specified in the ShaderAsset used to create the shader.
     * @return QGLShaderProgram
     */
    QOpenGLShaderProgram* getShader(QString name);

signals:
    void shaderSourceUpdated(QList<ShaderAsset *> shaders);

private:

    /**
     * @brief m_shaders Dictionary of shader programs, the key is the ShaderAsset objectName
     */
    QHash<QString, QOpenGLShaderProgram *> m_shaders;

    /**
     * @brief m_shaderSources list of shader sources used by QML classes. Cannot be bound.
     */
    QList<ShaderAsset *> m_shaderSources;
    QQmlListProperty<ShaderAsset> m_shaderSourcesQmlList();

};


#endif // SHADERASSETMANAGER_H
