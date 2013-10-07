#include "sceneitemupdatevisitor.h"
#include "sceneitems.h"
#include "tilesheet.h"
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>

void SceneItemUpdateVisitor::visit(Layer &layer)
{
    layer.visualLayer()->accept(*this);

    for(SceneElementInterface *actor : layer.actors())
    {
        actor->accept(*this);
    }
}

void SceneItemUpdateVisitor::visit(RigidBodyPhysicsController &physicController)
{

}

void SceneItemUpdateVisitor::visit(Actor &actor)
{
    for(SceneElementInterface *item : actor.components())
    {
        item->accept(*this);
    }
}

void SceneItemUpdateVisitor::visit(SpriteComponent &spriteComponent)
{
    QOpenGLFunctions gl(QOpenGLContext::currentContext());

    Mesh mesh = spriteComponent.mesh();

    gl.glBindBuffer(GL_ARRAY_BUFFER, mesh.buffers()[0]);
    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.buffers()[1]);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(32, 32, 0);
    modelMatrix.scale(1);

    QMatrix4x4 mvp = m_projectionMatrix * m_viewMatrix * modelMatrix;

    spriteComponent.material()->bind(mvp);

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

    spriteComponent.material()->release();

    gl.glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SceneItemUpdateVisitor::visit(TileMap &tilemap)
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

void SceneItemUpdateVisitor::visit(Material &material)
{
    Q_UNUSED(material)
}
