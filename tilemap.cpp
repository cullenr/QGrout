#include "tilemap.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include <QSGTexture>
#include <QGLFunctions>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Tilemap::Tilemap(QQuickItem *parent) :
    QQuickItem(parent),
    m_material(NULL),
    m_GlFuncs(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}


void Tilemap::handleWindowChanged(QQuickWindow *window)
{
    if(window)
    {
        // Connect the beforeRendering signal to our paint function.
        // Since this call is executed on the rendering thread it must be
        // a Qt::DirectConnection
        connect(window, SIGNAL(beforeRendering()), this, SLOT(draw()), Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        window->setClearBeforeRendering(false);
    }
}

void Tilemap::draw()
{
    static bool initialised = false;
    if(!initialised)
    {
        initialised = true;

        const float size = 32.0f;
        const float sixteenth = 1.0f / 16.0f;
        const float x = 1;
        const float y = 0;
        const float u = x * sixteenth;
        const float v = y * sixteenth;

//        VertexData verticies[] = {
//            {QVector3D(-size, -size, 0.0f), QVector2D(u, v)},
//            {QVector3D( size, -size, 0.0f), QVector2D(u + sixteenth, v)},
//            {QVector3D(-size,  size, 0.0f), QVector2D(u, v + sixteenth)},
//            {QVector3D( size,  size, 0.0f), QVector2D(u + sixteenth, v + sixteenth)},
//        };

        VertexData verticies[] = {
            {QVector3D(0, 0, 0.0f), QVector2D(u, v)},
            {QVector3D(size, 0, 0.0f), QVector2D(u + sixteenth, v)},
            {QVector3D(0, size, 0.0f), QVector2D(u, v + sixteenth)},
            {QVector3D(size, size, 0.0f), QVector2D(u + sixteenth, v + sixteenth)},
        };

        GLushort indicies[] = {
            0, 1, 2, 3, 3
        };

        m_GlFuncs = window()->openglContext()->versionFunctions<QOpenGLFunctions_2_0>();
        if (!m_GlFuncs)
        {
            qWarning() << "Could not obtain required OpenGL context version";
            exit(1);
        }
        m_GlFuncs->initializeOpenGLFunctions();

        m_GlFuncs->glGenBuffers (2, m_vboIds);

        m_GlFuncs->glBindBuffer (GL_ARRAY_BUFFER, m_vboIds[0]);
        m_GlFuncs->glBufferData (GL_ARRAY_BUFFER, 4 * sizeof(VertexData), verticies, GL_STATIC_DRAW);

        m_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
        m_GlFuncs->glBufferData (GL_ELEMENT_ARRAY_BUFFER, 5 * sizeof(GLushort), indicies, GL_STATIC_DRAW);

        m_GlFuncs->glEnable(GL_TEXTURE_2D);
    }
    else
    {
        m_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
        m_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    }
    QOpenGLShaderProgram *shader = m_material->shader()->shader();
    shader->bind();

    QSGTexture *texture = m_material->texture()->texture();
    m_GlFuncs->glActiveTexture(GL_TEXTURE0);
    texture->bind();
    GLuint textureId = texture->textureId();// does not bloody work!
    textureId--;//XXX: HACK! ^^^

    shader->setUniformValue("texture", textureId);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(0, 0, 0);
    shader->setUniformValue("modelMatrix", modelMatrix);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    shader->setUniformValue("viewMatrix", viewMatrix);

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);
    shader->setUniformValue("projectionMatrix", projectionMatrix);

    quintptr offset = 0;

    int vertexLocation = shader->attributeLocation("position");
    shader->enableAttributeArray(vertexLocation);
    m_GlFuncs->glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    offset +=sizeof(QVector3D);

    int texcoordLocation = shader->attributeLocation("texturePosition");
    shader->enableAttributeArray(texcoordLocation);
    m_GlFuncs->glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    m_GlFuncs->glClearColor(1, 0, 0, 1);
    m_GlFuncs->glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_GlFuncs->glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_SHORT, 0);

    m_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);// QQuick gets bitchy if we dont do this.
    m_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);// QQuick gets bitchy if we dont do this.
    m_GlFuncs->glActiveTexture(0);
    shader->release();
}

void Tilemap::componentComplete()
{

}
