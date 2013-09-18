#include "sceneitemupdatevisitor.h"
#include "sceneelementinterface.h"

SceneItemUpdateVisitor::SceneItemUpdateVisitor()
{
}

QMatrix4x4 SceneItemUpdateVisitor::viewMatrix() const
{
    return m_viewMatrix;
}

void SceneItemUpdateVisitor::setViewMatrix(const QMatrix4x4 &viewMatrix)
{
    m_viewMatrix = viewMatrix;
}

QMatrix4x4 SceneItemUpdateVisitor::projectionMatrix() const
{
    return m_projectionMatrix;
}

void SceneItemUpdateVisitor::setProjectionMatrix(const QMatrix4x4 &perspectiveMatrix)
{
    m_projectionMatrix = perspectiveMatrix;
}
