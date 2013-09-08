#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include "shaderasset.h"
#include "assetvisitor.h"
#include "assetcreatedevent.h"

ShaderAsset::ShaderAsset(QObject *parent) :
    GObject(parent),
    m_shader(0)
{
}

void ShaderAsset::accept(AssetVisitor &visitor)
{
    visitor.visit(*this);
}

void ShaderAsset::classBegin()
{
    //not used
}

void ShaderAsset::componentComplete()
{
    //new asset gets deleted by the even system
    QCoreApplication::postEvent(parent(), new AssetCreatedEvent());
}

ShaderAsset::~ShaderAsset()
{
    delete(m_shader);
}

QOpenGLShaderProgram *ShaderAsset::shader() const
{
    return m_shader;
}

bool ShaderAsset::compile()
{
    m_shader = new QOpenGLShaderProgram();

    if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexShaderPath) ||
        !m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentShaderPath) ||
        !m_shader->link())
    {
        qWarning() << m_shader->log();

        return 0;
    }

    return 1;
}
