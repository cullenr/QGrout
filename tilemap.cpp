#include "tilemap.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"
#include "vertexdata.h"
#include "visitor.h"
#include "initialisationvisitor.h"
#include "drawvisitor.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QSGTexture>

Tilemap::Tilemap(QQuickItem *parent) :
    QQuickItem(parent),
    m_material(NULL)
{
    //connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void Tilemap::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

//void Tilemap::handleWindowChanged(QQuickWindow *window)
//{
//    if(window)
//    {
//        // Connect the beforeRendering signal to our paint function.
//        // Since this call is executed on the rendering thread it must be
//        // a Qt::DirectConnection
//        connect(window, SIGNAL(beforeRendering()), this, SLOT(draw()), Qt::DirectConnection);
//        // If we allow QML to do the clearing, they would clear what we paint
//        // and nothing would show.
//        window->setClearBeforeRendering(false);
//    }
//}

//void Tilemap::draw()
//{
//    static bool initialised = false;
//    if(!initialised)
//    {
//        initialised = true;
//        initializeGLFunctions();

//        createTileStips();

//        glEnable(GL_TEXTURE_2D);
//    }

//    m_tilemap[0].bind(*this);

//    QOpenGLShaderProgram *shader = m_material->shader()->shader();
//    shader->bind();

//    QSGTexture *texture = m_material->texture()->texture();
//    glActiveTexture(GL_TEXTURE0);
//    texture->bind();
//    GLuint textureId = texture->textureId();// does not bloody work!
//    textureId--;//XXX: HACK! ^^^

//    shader->setUniformValue("texture", textureId);

//    QMatrix4x4 modelMatrix;
//    modelMatrix.setToIdentity();
//    modelMatrix.translate(64, 64, 0);
//    modelMatrix.scale(4);
//    shader->setUniformValue("modelMatrix", modelMatrix);

//    QMatrix4x4 viewMatrix;
//    viewMatrix.setToIdentity();
//    shader->setUniformValue("viewMatrix", viewMatrix);

//    QMatrix4x4 projectionMatrix;
//    projectionMatrix.setToIdentity();
//    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);
//    shader->setUniformValue("projectionMatrix", projectionMatrix);

//    quintptr offset = 0;

//    int vertexLocation = shader->attributeLocation("position");
//    shader->enableAttributeArray(vertexLocation);
//    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

//    offset +=sizeof(QVector2D);

//    int texcoordLocation = shader->attributeLocation("texturePosition");
//    shader->enableAttributeArray(texcoordLocation);
//    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

//    glClearColor(1, 0, 0, 1);
//    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    //glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (GLvoid *)(4 * sizeof(GLushort)));
//    m_tilemap[0].draw(1, 2, *this);

//    glActiveTexture(0);
//    shader->disableAttributeArray(vertexLocation);
//    shader->disableAttributeArray(texcoordLocation);
//    shader->release();
//}

QVector<Mesh> Tilemap::rows() const
{
    return m_rows;
}

void Tilemap::setRows(const QVector<Mesh> &rows)
{
    m_rows = rows;
}

Material* Tilemap::material() const
{
    return m_material;
}
QList<int> Tilemap::map() const
{   
    return m_map;
}

int Tilemap::mapWidth() const
{
    return m_mapWidth;
}

void Tilemap::componentComplete()
{
    qDebug("bolliks");
}

void InitialisationVisitor::visit(Tilemap &tilemap)
{
    QList<int> map = tilemap.map();
    int mapWidth = tilemap.mapWidth();
    int mapHeight = map.size() / mapWidth;
    QVector<Mesh> strips(mapHeight);

    for(int i = 0; i < mapHeight; i++)
    {
        const float size = 32.0f;
        const float sixteenth = 1.0f / 16.0f;
        const float x = 1.0f;
        const float y = 1.0f;
        const float u = x * sixteenth;
        const float v = y * sixteenth;

        VertexData verticies[] = {
            {QVector2D(0, 0), QVector2D(u, v)},
            {QVector2D(size, 0), QVector2D(u + sixteenth, v)},
            {QVector2D(0, size), QVector2D(u, v + sixteenth)},
            {QVector2D(size, size), QVector2D(u + sixteenth, v + sixteenth)},

            {QVector2D(size + 0, 0), QVector2D(u + sixteenth, v)},
            {QVector2D(size + size, 0), QVector2D(u + sixteenth + sixteenth, v)},
            {QVector2D(size + 0, size), QVector2D(u + sixteenth, v + sixteenth)},
            {QVector2D(size + size, size), QVector2D(u + sixteenth + sixteenth, v + sixteenth)},

            {QVector2D(size * 2 + 0, 0), QVector2D(u + sixteenth * 2, v)},
            {QVector2D(size * 2 + size, 0), QVector2D(u + sixteenth * 2 + sixteenth, v)},
            {QVector2D(size * 2 + 0, size), QVector2D(u + sixteenth * 2, v + sixteenth)},
            {QVector2D(size * 2 + size, size), QVector2D(u + sixteenth * 2 + sixteenth, v + sixteenth)},
        };

        GLushort indicies[] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
        };

        QOpenGLFunctions gl(QOpenGLContext::currentContext());

        GLuint buffers[2];
        quintptr bufferSizes[2] {12 * sizeof(VertexData), 12 * sizeof(GLushort)};

        gl.glGenBuffers(2, buffers);

        gl.glBindBuffer (GL_ARRAY_BUFFER, buffers[0]);
        gl.glBufferData (GL_ARRAY_BUFFER, bufferSizes[0], verticies, GL_STATIC_DRAW);

        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        gl.glBufferData (GL_ELEMENT_ARRAY_BUFFER, bufferSizes[1], indicies, GL_STATIC_DRAW);

        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        strips[i] = Mesh(buffers, bufferSizes);
    }

    tilemap.setRows(strips);
}


void DrawVisitor::visit(Tilemap &tilemap)
{
    QOpenGLFunctions gl(QOpenGLContext::currentContext());
    int start = 0;//TODO : THESE NEED TO BE CALCULATED BASED UPON THE VIEW MATRIX
    int span = 3;
    int i = 0;

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    for(Mesh row : tilemap.rows())
    {
        gl.glBindBuffer(GL_ARRAY_BUFFER, row.buffers()[0]);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, row.buffers()[1]);

        QMatrix4x4 modelMatrix;
        modelMatrix.setToIdentity();
        modelMatrix.translate(0, i++ * 32, 0);
        modelMatrix.scale(1);

//        QMatrix4x4 mvp = m_projectionViewMatrix * modelMatrix;

                    QMatrix4x4 viewMatrix;
                    viewMatrix.setToIdentity();

                    QMatrix4x4 projectionMatrix;
                    projectionMatrix.setToIdentity();
                    projectionMatrix.ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f);

                    QMatrix4x4 mvp = projectionMatrix * viewMatrix * modelMatrix;

        tilemap.material()->bind(mvp);

        glDrawElements(GL_TRIANGLE_STRIP, span * 4, GL_UNSIGNED_SHORT, (GLvoid *)(start * 4 * sizeof(GLushort)));

        tilemap.material()->release();

        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

