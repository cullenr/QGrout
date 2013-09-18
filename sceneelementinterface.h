#ifndef SCENE_ELEMENT_H
#define SCENE_ELEMENT_H

class SceneItemVisitor;

struct SceneElementInterface
{
    virtual void accept(SceneItemVisitor &visitor) = 0;
};

#endif // SCENE_ELEMENT_H
