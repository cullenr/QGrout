#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <QMatrix4x4>

#include "visitor.h"

class DrawVisitor : public Visitor
{
public:
    DrawVisitor();

    void visit(TileMap &tilemap);

    QMatrix4x4 projectionViewMatrix() const;
    void setProjectionViewMatrix(const QMatrix4x4 &projectionViewMatrix);

private:
    QMatrix4x4 m_projectionViewMatrix;

};

#endif // DRAWVISITOR_H
