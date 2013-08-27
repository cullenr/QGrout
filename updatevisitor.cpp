#include "updatevisitor.h"
#include "visitee.h"

UpdateVisitor::UpdateVisitor()
{
}

QMatrix4x4 UpdateVisitor::viewMatrix() const
{
    return m_viewMatrix;
}

void UpdateVisitor::setViewMatrix(const QMatrix4x4 &viewMatrix)
{
    m_viewMatrix = viewMatrix;
}

QMatrix4x4 UpdateVisitor::projectionMatrix() const
{
    return m_projectionMatrix;
}

void UpdateVisitor::setProjectionMatrix(const QMatrix4x4 &perspectiveMatrix)
{
    m_projectionMatrix = perspectiveMatrix;
}
