#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"
#include "vertexdata.h"
#include "sceneitemvisitor.h"
#include "sceneitemupdatevisitor.h"
#include "sceneiteminitvisitor.h"

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

Material::Material(QObject *parent) :
    AbstractGameObject(parent),
    m_shader(0),
    m_texture(0)
{
}

void Material::accept(SceneItemVisitor &visitor)
{
    visitor.visit(*this);
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
    GLuint textId = m_texture->glTextureId();

    shader->bind();

    gl.glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textId);

    //GLuint textureId = texture->textureId();// does not bloody work!
    //textureId--;//XXX: HACK! ^^^
    //shader->setUniformValue("texture", textureId);
    shader->setUniformValue("texture", 0);

    //Could use double dispatch to set these values if we want a nice type safe extensible solution
    shader->setUniformValue("mvp", mvpMatrix);

    quintptr offset = 0;

    int vertexLocation = shader->attributeLocation("position");
    shader->enableAttributeArray(vertexLocation);
    gl.glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
            (const void *)offset);

    offset +=sizeof(QVector2D);

    int texcoordLocation = shader->attributeLocation("texturePosition");
    shader->enableAttributeArray(texcoordLocation);
    gl.glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData),
            (const void *)offset);
}

void Material::release()//TODO : CONSIDER MSKING THIS A FREE FUNCTION
{
    QOpenGLShaderProgram *shader = m_shader->shader();

    QOpenGLContext::currentContext()->functions()->glActiveTexture(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    shader->disableAttributeArray("position");
    shader->disableAttributeArray("texturePosition");
    shader->release();
}
