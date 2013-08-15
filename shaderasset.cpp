#include <QOpenGLShaderProgram>
#include "shaderasset.h"

ShaderAsset::ShaderAsset(QObject *parent) :
    QObject(parent),
    m_shader(0)
{
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
