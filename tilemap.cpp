#include "tilemap.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QSGTexture>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Tilemap::Tilemap(QQuickItem *parent) :
    QQuickItem(parent),
    m_material(NULL)
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

        VertexData verticies[] = {
            {QVector3D(0, 0, 0.0f), QVector2D(u, v)},
            {QVector3D(size, 0, 0.0f), QVector2D(u + sixteenth, v)},
            {QVector3D(0, size, 0.0f), QVector2D(u, v + sixteenth)},
            {QVector3D(size, size, 0.0f), QVector2D(u + sixteenth, v + sixteenth)},

            {QVector3D(size + 0, 0, 0.0f), QVector2D(u + sixteenth, v)},
            {QVector3D(size + size, 0, 0.0f), QVector2D(u + sixteenth + sixteenth, v)},
            {QVector3D(size + 0, size, 0.0f), QVector2D(u + sixteenth, v + sixteenth)},
            {QVector3D(size + size, size, 0.0f), QVector2D(u + sixteenth + sixteenth, v + sixteenth)},

            {QVector3D(size * 2 + 0, 0, 0.0f), QVector2D(u + sixteenth * 2, v)},
            {QVector3D(size * 2 + size, 0, 0.0f), QVector2D(u + sixteenth * 2 + sixteenth, v)},
            {QVector3D(size * 2 + 0, size, 0.0f), QVector2D(u + sixteenth * 2, v + sixteenth)},
            {QVector3D(size * 2 + size, size, 0.0f), QVector2D(u + sixteenth * 2 + sixteenth, v + sixteenth)},
        };

        GLushort indicies[] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
        };

        initializeGLFunctions();

        glGenBuffers (2, m_vboIds);

        glBindBuffer (GL_ARRAY_BUFFER, m_vboIds[0]);
        glBufferData (GL_ARRAY_BUFFER, 12 * sizeof(VertexData), verticies, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(GLushort), indicies, GL_STATIC_DRAW);

        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    }
    QOpenGLShaderProgram *shader = m_material->shader()->shader();
    shader->bind();

    QSGTexture *texture = m_material->texture()->texture();
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    GLuint textureId = texture->textureId();// does not bloody work!
    textureId--;//XXX: HACK! ^^^

    shader->setUniformValue("texture", textureId);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(64, 64, 0);
    modelMatrix.scale(4);
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
    //TODO : SET SIZE TO 2 SO WE CAN REMOVE THE 3D ELEMENT
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    offset +=sizeof(QVector3D);

    int texcoordLocation = shader->attributeLocation("texturePosition");
    shader->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    glClearColor(1, 0, 0, 1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (GLvoid *)(4 * sizeof(GLushort)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);// QQuick gets bitchy if we dont do this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);// QQuick gets bitchy if we dont do this.
    glActiveTexture(0);
    shader->disableAttributeArray(vertexLocation);
    shader->disableAttributeArray(texcoordLocation);
    shader->release();
}

void Tilemap::componentComplete()
{

}
