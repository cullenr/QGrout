#include "tilestrip.h"
#include "vertexdata.h"
#include "material.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QList>
#include <QVector2D>

TileStrip::TileStrip()
{
    qDebug("tilestrip Created");
}

void TileStrip::createBuffers(QList<int> tileIds, int tilesize, int tilesheetWidthInTiles)
{
    const float tileWidthReciprocal = 1.0f / tilesheetWidthInTiles;
    const int numTiles = tileIds.length();

    //arrays to create gl bufers
//    VertexData verticies[numTiles * 4];
//    GLushort indicies[numTiles * 4];

//    int index = 0;

//    //calculate verticies
//    for(int i = 0; i < numTiles; ++i)
//    {
//        //find st coordinates for the tilesheet
//        const int tileId = tileIds[i];
//        const int x = tileId % tilesheetWidthInTiles;
//        const int y = tileId / tilesheetWidthInTiles;
//        const float s = x * tileWidthReciprocal;
//        const float t = y * tileWidthReciprocal;

//        const int vertexX = i * tilesize;

//        verticies[index] = {QVector2D(vertexX, 0), QVector2D(s, t)};
//        indicies[index] = index;
//        index++;

//        verticies[index] = {QVector2D(vertexX + tilesize, 0), QVector2D(s + tileWidthReciprocal, t)};
//        indicies[index] = index;
//        index++;

//        verticies[index] = {QVector2D(vertexX, tilesize), QVector2D(s, t + tileWidthReciprocal)};
//        indicies[index] = index;
//        index++;

//        verticies[index] = {QVector2D(vertexX + tilesize, tilesize), QVector2D(s + tileWidthReciprocal, t + tileWidthReciprocal)};
//        indicies[index] = index;
//        index++;
//    }

    const float size = 32.0f;
    const float sixteenth = 1.0f / 16.0f;
    const float x = 1.0f;
    const float y = 0.0f;
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

    gl.glGenBuffers(2, m_vbos);

    gl.glBindBuffer (GL_ARRAY_BUFFER, m_vbos[0]);
    gl.glBufferData (GL_ARRAY_BUFFER, 12 * sizeof(VertexData), verticies, GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);
    gl.glBufferData (GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(GLushort), indicies, GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//void TileStrip::bind()
//{
//    QOpenGLFunctions gl(QOpenGLContext::currentContext());

//    gl.glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
//    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);
//}

//void TileStrip::draw(Material &material, QMatrix4x4 viewProjectionMatrix)
//{
//    QOpenGLFunctions gl(QOpenGLContext::currentContext());
//    int start = 0;
//    int span = 3;

//    gl.glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
//    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[1]);

//    glDrawElements(GL_TRIANGLE_STRIP, span * 4, GL_UNSIGNED_SHORT, (GLvoid *)(start * 4 * sizeof(GLushort)));

//    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
//    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}

