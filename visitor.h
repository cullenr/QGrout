#ifndef VISITOR_H
#define VISITOR_H

class Tilemap;

struct Visitor
{
    virtual void visit(Tilemap &) = 0;
};

#endif // VISITOR_H
