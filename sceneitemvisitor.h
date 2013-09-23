#ifndef SCENE_ELEMENT_VISITOR_H
#define SCENE_ELEMENT_VISITOR_H

class TileMap;
class Actor;
class SpriteComponent;
class Material;
class Layer;

struct SceneItemVisitor
{
    virtual void visit(TileMap &tilemap) = 0;
    virtual void visit(Actor &actor) = 0;
    virtual void visit(SpriteComponent &spriteComponent) = 0;
    virtual void visit(Material &spriteComponent) = 0;
    virtual void visit(Layer &layer) = 0;
};

#endif // SCENE_ELEMENT_VISITOR_H
