#ifndef SHADERASSET_H
#define SHADERASSET_H

#include "gobject.h"
#include "abstractasset.h"

class QOpenGLShaderProgram;
class AssetVisitor;

class ShaderAsset : public GObject, public AbstractAsset
{
    Q_OBJECT
    Q_PROPERTY(QString fragmentShaderPath MEMBER m_fragmentShaderPath);
    Q_PROPERTY(QString vertexShaderPath MEMBER m_vertexShaderPath);

public:
    explicit ShaderAsset(QObject *parent = 0);
    ~ShaderAsset();

    QOpenGLShaderProgram* shader() const;

    bool compile();

    //AbstractAsset
    void accept(AssetVisitor &visitor) override;
    void classBegin() override;
    void componentComplete() override;

private:
    QOpenGLShaderProgram *m_shader;
    QString m_fragmentShaderPath;
    QString m_vertexShaderPath;

};


#endif // SHADERASSET_H
