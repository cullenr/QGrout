#ifndef TILESTRIP_H
#define TILESTRIP_H

#include <QGLFunctions>
#include <QList>

class Material;
class QMatrix4x4;

class TileStrip
{
public:
    TileStrip();

    //must be called from render thread
    void createBuffers(QList<int> tileIds, int tilesize, int tilesheetWidthInTiles);
    //must be called from render thread
    void draw(Material &material, QMatrix4x4 viewProjectionMatrix);
    void bind();

private:
    GLuint m_vbos[2];
};

#endif // TILESTRIP_H
