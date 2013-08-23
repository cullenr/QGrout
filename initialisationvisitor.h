#ifndef INITIALISATIONVISITOR_H
#define INITIALISATIONVISITOR_H

#include "visitor.h"

class InitialisationVisitor : public Visitor
{
public:
    InitialisationVisitor();

    void visit(TileMap &) override;
};

#endif // INITIALISATIONVISITOR_H
