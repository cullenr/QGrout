#include "tilemap.h"
#include "tilesheet.h"
#include "material.h"
#include "shaderasset.h"
#include "textureasset.h"
#include "vertexdata.h"
#include "visitor.h"
#include "initialisationvisitor.h"
#include "updatevisitor.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QSGTexture>
#include <QDebug>

TileMap::TileMap(QQuickItem *parent) :
    GQuickItem(parent),
    m_tileSheet(NULL)
{
}

void TileMap::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

QVector<Mesh> TileMap::rows() const
{
    return m_rows;
}

void TileMap::setRows(const QVector<Mesh> &rows)
{
    m_rows = rows;
}

TileSheet *TileMap::tileSheet() const
{
    return m_tileSheet;
}
QList<int> TileMap::map() const
{   
    return m_map;
}

int TileMap::mapWidth() const
{
    return m_mapWidth;
}

int TileMap::tileSize() const
{
    return m_tileSize;
}

void InitialisationVisitor::visit(TileMap &tilemap)
{
    const QList<int> map = tilemap.map();
    const int mapWidth = tilemap.mapWidth();
    const int mapHeight = map.size() / mapWidth;
    const int tilesize = tilemap.tileSheet()->tileSize();
    const int tilesheetWidthInTiles = tilemap.tileSheet()->tilesAcross();
    const float tileWidthReciprocal = 1.0f / tilesheetWidthInTiles;
    QVector<Mesh> strips(mapHeight);

    for(int i = 0; i < mapHeight; i++)
    {
        const int vertexY = i * tilesize;

        VertexData verticies[mapWidth * 4];
        GLushort indicies[mapWidth * 6 - 2];

        int indiciesIndex = 0;
        int verticiesIndex = 0;

        //calculate verticies
        for(int j = 0; j < mapWidth; ++j)
        {
            //find st coordinates for the tilesheet
            const int tileId = map[i * mapWidth + j];
            const int x = tileId % tilesheetWidthInTiles;
            const int y = tileId / tilesheetWidthInTiles;
            const float s = x * tileWidthReciprocal;
            const float t = y * tileWidthReciprocal;

            const int vertexX = j * tilesize;
            const int baseIndex = j * 4;

            verticies[verticiesIndex++] = { QVector2D(vertexX, vertexY),
                                            QVector2D(s, t)};
            verticies[verticiesIndex++] = { QVector2D(vertexX + tilesize, vertexY),
                                            QVector2D(s + tileWidthReciprocal, t)};
            verticies[verticiesIndex++] = { QVector2D(vertexX, vertexY + tilesize),
                                            QVector2D(s, t + tileWidthReciprocal)};
            verticies[verticiesIndex++] = { QVector2D(vertexX + tilesize, vertexY + tilesize),
                                            QVector2D(s + tileWidthReciprocal, t + tileWidthReciprocal)};

            indicies[indiciesIndex++] = baseIndex;
            //add degenerate triangle if necessary
            if(j != 0)
                indicies[indiciesIndex++] = baseIndex;
            indicies[indiciesIndex++] = baseIndex + 1;
            indicies[indiciesIndex++] = baseIndex + 2;
            indicies[indiciesIndex++] = baseIndex + 3;
            //add degenerate triangle if necessary
            if(j != mapWidth - 1)
                indicies[indiciesIndex++] = baseIndex + 3;
        }

        QOpenGLFunctions gl(QOpenGLContext::currentContext());

        GLuint buffers[2];
        quintptr bufferSizes[2] {verticiesIndex * sizeof(VertexData), indiciesIndex * sizeof(GLushort)};

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


void UpdateVisitor::visit(TileMap &tilemap)
{
    QOpenGLFunctions gl(QOpenGLContext::currentContext());
    int start = 0;//TODO : THESE NEED TO BE CALCULATED BASED UPON THE VIEW MATRIX
    int span = tilemap.mapWidth() * 6 - 2;

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

    for(Mesh row : tilemap.rows())
    {
        gl.glBindBuffer(GL_ARRAY_BUFFER, row.buffers()[0]);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, row.buffers()[1]);

        QMatrix4x4 modelMatrix;
        modelMatrix.setToIdentity();
        modelMatrix.translate(0, 0, 0);
        modelMatrix.scale(1);

        QMatrix4x4 mvp = m_projectionMatrix * m_viewMatrix * modelMatrix;

        tilemap.tileSheet()->material()->bind(mvp);

        glDrawElements(GL_TRIANGLE_STRIP, span, GL_UNSIGNED_SHORT, (GLvoid *)(start * 4 * sizeof(GLushort)));

        tilemap.tileSheet()->material()->release();

        gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
        gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

