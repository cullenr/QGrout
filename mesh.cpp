#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(GLuint buffers[2], quintptr bufferLengths[2])
{
    memcpy(m_buffers, buffers, sizeof(buffers[0]) * 2);
    memcpy(m_bufferLengths, bufferLengths, sizeof(bufferLengths[0]) * 2);
}

GLuint* Mesh::buffers()
{
    return m_buffers;
}

quintptr* Mesh::bufferLengths()
{
    return m_bufferLengths;
}
