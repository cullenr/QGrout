#ifndef INITIALISATIONVISITOR_H
#define INITIALISATIONVISITOR_H

#include "visitor.h"

class InitialisationVisitor : public Visitor
{
public:
    InitialisationVisitor();

    void visit(TileMap &tilemap) override;
    void visit(Actor &actor) override;
    void visit(SpriteComponent &spriteComponent) override;
};

#endif // INITIALISATIONVISITOR_H
