#ifndef SCENE_ELEMENT_H
#define SCENE_ELEMENT_H

class SceneElementVisitor;

class SceneElement
{
public:
    virtual void accept(SceneElementVisitor &visitor) = 0;
};

#endif // SCENE_ELEMENT_H
