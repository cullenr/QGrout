#ifndef INITIALISATIONVISITOR_H
#define INITIALISATIONVISITOR_H

#include "sceneitemvisitor.h"

class SceneItemInitVisitor : public SceneItemVisitor
{
public:
    SceneItemInitVisitor();

    void visit(TileMap &tilemap) override;
    void visit(Actor &actor) override;
    void visit(SpriteComponent &spriteComponent) override;
    void visit(Material &material) override;
    void visit(Layer &layer) override;
};

#endif // INITIALISATIONVISITOR_H
