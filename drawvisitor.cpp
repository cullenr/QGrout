#include "drawvisitor.h"

DrawVisitor::DrawVisitor()
{
}

QMatrix4x4 DrawVisitor::projectionViewMatrix() const
{
    return m_projectionViewMatrix;
}

void DrawVisitor::setProjectionViewMatrix(const QMatrix4x4 &projectionViewMatrix)
{
    m_projectionViewMatrix = projectionViewMatrix;
}
