#ifndef UPDATEVISITOR_H
#define UPDATEVISITOR_H

#include <QMatrix4x4>

#include "visitor.h"

class Visitee;

class UpdateVisitor : public Visitor
{
public:
    UpdateVisitor();

    void visit(QVector<Visitee *> visitables);
    void visit(TileMap &tilemap) override;
    void visit(Actor &actor) override;
    void visit(SpriteComponent &spriteComponent) override;

    QMatrix4x4 viewMatrix() const;
    void setViewMatrix(const QMatrix4x4 &viewMatrix);

    QMatrix4x4 projectionMatrix() const;
    void setProjectionMatrix(const QMatrix4x4 &projectionMatrix);

private:
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projectionMatrix;
};

#endif // UPDATEVISITOR_H
