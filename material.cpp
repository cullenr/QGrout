#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"
#include "vertexdata.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QSGTexture>

Material::Material(QObject *parent) :
    QObject(parent),
    m_shader(0),
    m_texture(0)
{
}

ShaderAsset * Material::shader() const
{
    return m_shader;
}

TextureAsset * Material::texture() const
{
    return m_texture;
}

void Material::bind(QMatrix4x4 &mvpMatrix)//TODO : CONSIDER MSKING THIS A FREE FUNCTION
{
    QOpenGLFunctions gl(QOpenGLContext::currentContext());
    QOpenGLShaderProgram *shader = m_shader->shader();
    QSGTexture *texture = m_texture->texture();

    shader->bind();

    gl.glActiveTexture(GL_TEXTURE0);
    texture->bind();
    GLuint textureId = texture->textureId();// does not bloody work!
    textureId--;//XXX: HACK! ^^^
    shader->setUniformValue("texture", textureId);

    shader->setUniformValue("mvp", mvpMatrix);//Could use double dispatch to set these values if we want a nice type safe extensible solution

    quintptr offset = 0;

    int vertexLocation = shader->attributeLocation("position");
    shader->enableAttributeArray(vertexLocation);
    gl.glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    offset +=sizeof(QVector2D);

    int texcoordLocation = shader->attributeLocation("texturePosition");
    shader->enableAttributeArray(texcoordLocation);
    gl.glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

}

void Material::release()
{
    QOpenGLShaderProgram *shader = m_shader->shader();

    QOpenGLContext::currentContext()->functions()->glActiveTexture(0);

    shader->disableAttributeArray("position");
    shader->disableAttributeArray("texturePosition");
    shader->release();
}
