#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include "shaderasset.h"
#include "assetvisitor.h"
#include "assetcreatedevent.h"

ShaderAsset::ShaderAsset(QObject *parent) :
    AbstractAsset(parent),
    m_shader(nullptr)
{
}

ShaderAsset::~ShaderAsset()
{
    delete(m_shader);
}

void ShaderAsset::accept(AssetVisitor &visitor)
{
    visitor.visit(*this);
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
