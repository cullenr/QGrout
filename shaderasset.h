#ifndef SHADERASSET_H
#define SHADERASSET_H

#include <QObject>
#include "abstractasset.h"

class QOpenGLShaderProgram;
class AssetVisitor;

class ShaderAsset : public AbstractAsset
{
    Q_OBJECT
    Q_PROPERTY(QString fragmentShaderPath MEMBER m_fragmentShaderPath);
    Q_PROPERTY(QString vertexShaderPath MEMBER m_vertexShaderPath);

public:
    explicit ShaderAsset(QObject *parent = 0);
    ~ShaderAsset();

    void accept(AssetVisitor &visitor) override;
    bool compile();

    QOpenGLShaderProgram* shader() const;

private:
    QOpenGLShaderProgram *m_shader;
    QString m_fragmentShaderPath;
    QString m_vertexShaderPath;

};


#endif // SHADERASSET_H
