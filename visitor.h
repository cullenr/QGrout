#ifndef VISITOR_H
#define VISITOR_H

class TileMap;

struct Visitor
{
    virtual void visit(TileMap &) = 0;
};

#endif // VISITOR_H
