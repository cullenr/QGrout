#ifndef UPDATEVISITOR_H
#define UPDATEVISITOR_H

#include <QMatrix4x4>

#include "sceneitemvisitor.h"

class SceneElementInterface;

class SceneItemUpdateVisitor : public SceneItemVisitor
{
public:
    SceneItemUpdateVisitor();

    void visit(TileMap &tilemap) override;
    void visit(Actor &actor) override;
    void visit(SpriteComponent &spriteComponent) override;
    void visit(Material &material) override;
    void visit(Layer &layer) override;

    QMatrix4x4 viewMatrix() const;
    void setViewMatrix(const QMatrix4x4 &viewMatrix);

    QMatrix4x4 projectionMatrix() const;
    void setProjectionMatrix(const QMatrix4x4 &projectionMatrix);

private:
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
};

#endif // UPDATEVISITOR_H
