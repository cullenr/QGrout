#ifndef MESH_H
#define MESH_H

#include <QtOpenGL>

class Mesh
{
public:
    Mesh();
    Mesh(GLuint buffers[2], quintptr bufferLengths[2]);

    GLuint* buffers();
    quintptr* bufferLengths();

private:
    GLuint m_buffers[2];
    quintptr m_bufferLengths[2];
};

#endif // MESH_H
