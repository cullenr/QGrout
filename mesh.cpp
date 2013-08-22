#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(GLuint buffers[2], quintptr bufferLengths[2]) :
    m_buffers({buffers[0], buffers[1]}),
    m_bufferLengths({bufferLengths[0], bufferLengths[1]})
{
}

GLuint* Mesh::buffers()
{
    return m_buffers;
}

quintptr* Mesh::bufferLengths()
{
    return m_bufferLengths;
}
