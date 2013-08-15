#ifndef SHADERASSET_H
#define SHADERASSET_H

#include <QObject>

class QOpenGLShaderProgram;

class ShaderAsset : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fragmentShaderPath MEMBER m_fragmentShaderPath);
    Q_PROPERTY(QString vertexShaderPath MEMBER m_vertexShaderPath);

public:
    explicit ShaderAsset(QObject *parent = 0);
    ~ShaderAsset();

    QOpenGLShaderProgram* shader() const;

    bool compile();

private:
    QOpenGLShaderProgram *m_shader;
    QString m_fragmentShaderPath;
    QString m_vertexShaderPath;

};


#endif // SHADERASSET_H
