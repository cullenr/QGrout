#ifndef VISITOR_H
#define VISITOR_H

class TileMap;
class Actor;
class SpriteComponent;

struct Visitor
{
    virtual void visit(TileMap &tilemap) = 0;
    virtual void visit(Actor &actor) = 0;
    virtual void visit(SpriteComponent &spriteComponent) = 0;
};

#endif // VISITOR_H
