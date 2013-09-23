#include "sceneiteminitvisitor.h"
#include "sceneelementinterface.h"
#include "sceneitems.h"
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>

#include "vertexdata.h"
#include "material.h"
#include "textureasset.h"
#include "tilesheet.h"

void SceneItemInitVisitor::visit(Layer &layer)
{
    //get all physics items and intialise them using this layers physics controller.

    layer.visualLayer()->accept(*this);

    for(SceneElementInterface *actor : layer.actors())
    {
        actor->accept(*this);
    }
}

void SceneItemInitVisitor::visit(SpriteComponent &spriteComponent)
{
    GLushort indicies[4] = {0, 1, 2, 3};
    Material *material = spriteComponent.material();
    float textureWidthReciprocal = 1.0f / material->texture()->textureWidth();
    float textureHeightReciprocal = 1.0f / material->texture()->textureHeight();
    QRect rect = spriteComponent.textureRect();
    int width = rect.width();
    int height = rect.height();
    float s1 = rect.x() * textureWidthReciprocal;
    float s2 = s1 + width * textureWidthReciprocal;
    float t1 = rect.y() * textureHeightReciprocal;
    float t2 = t1 + height * textureHeightReciprocal;
    VertexData verticies[4];
    verticies[0] = {QVector2D(0, 0), QVector2D(s1, t1)};
    verticies[1] = {QVector2D(width, 0), QVector2D(s2, t1)};
    verticies[2] = {QVector2D(0, height), QVector2D(s1, t2)};
    verticies[3] = {QVector2D(width, height), QVector2D(s2, t2)};

    QOpenGLFunctions gl(QOpenGLContext::currentContext());

    GLuint buffers[2];
    quintptr bufferSizes[2] {4 * sizeof(VertexData), 4 * sizeof(GLushort)};

    gl.glGenBuffers(2, buffers);

    gl.glBindBuffer (GL_ARRAY_BUFFER, buffers[0]);
    gl.glBufferData (GL_ARRAY_BUFFER, bufferSizes[0], verticies, GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    gl.glBufferData (GL_ELEMENT_ARRAY_BUFFER, bufferSizes[1], indicies, GL_STATIC_DRAW);

    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    spriteComponent.m_mesh = Mesh(buffers, bufferSizes);
}

void SceneItemInitVisitor::visit(Actor &actor)
{
    emit actor.init();

    for(SceneElementInterface *item : actor.components())
    {
        item->accept(*this);
    }
}

void SceneItemInitVisitor::visit(TileMap &tilemap)
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

void SceneItemInitVisitor::visit(Material &material)
{
    Q_UNUSED(material)
}
