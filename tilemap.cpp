#include "tilemap.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QMatrix4x4>
#include <QSGTexture>
#include <QGLFunctions>

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
    if(!m_GlFuncs)
    {
        const float size = 4.0f;

        float points[] = {
             -size, -size,  0.0f,
              size, -size,  0.0f,
             -size,  size,  0.0f,
              size,  size,  0.0f
        };

//        float points[] = {
//                 size,     size,  0.0f,
//             2 * size,     size,  0.0f,
//                 size, 2 * size,  0.0f,
//             2 * size, 2 * size,  0.0f
//        };

        GLuint vbo = 0;
        m_GlFuncs = window()->openglContext()->versionFunctions<QOpenGLFunctions_3_0>();
        if (!m_GlFuncs)
        {
            qWarning() << "Could not obtain required OpenGL context version";
            exit(1);
        }
        m_GlFuncs->initializeOpenGLFunctions();

        m_GlFuncs->glGenBuffers (1, &vbo);
        m_GlFuncs->glBindBuffer (GL_ARRAY_BUFFER, vbo);
        m_GlFuncs->glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (float), &points[0], GL_STATIC_DRAW);

        m_GlFuncs->glGenVertexArrays(1, &m_tileVao);
        m_GlFuncs->glBindVertexArray(m_tileVao);
        m_GlFuncs->glEnableVertexAttribArray(0);
        m_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vbo);
        m_GlFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

        m_GlFuncs->glBindBuffer (GL_ARRAY_BUFFER, 0);// QQuick gets bitchy if we dont do this.
    }
    QOpenGLShaderProgram *shader = m_material->shader()->shader();
    shader->bind();

    QSGTexture *texture = m_material->texture()->texture();
    m_GlFuncs->glActiveTexture(GL_TEXTURE0);
    texture->bind();
    shader->setUniformValue("texture", texture->textureId());

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(64, 64, 0);
    shader->setUniformValue("modelMatrix", modelMatrix);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    shader->setUniformValue("viewMatrix", viewMatrix);

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);
    shader->setUniformValue("projectionMatrix", projectionMatrix);

    m_GlFuncs->glClearColor(1, 0, 0, 1);
    m_GlFuncs->glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_GlFuncs->glBindVertexArray (m_tileVao);
    m_GlFuncs->glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

    m_GlFuncs->glBindVertexArray (0);
    m_GlFuncs->glActiveTexture(0);
    shader->release();

}

void Tilemap::componentComplete()
{

}
