#ifndef ASSETELEMENTINTERFACE_H
#define ASSETELEMENTINTERFACE_H
class AssetVisitor;

class AssetElementInterface
{
public:
    virtual void accept(AssetVisitor &visitor) = 0;
};

#endif // ASSETELEMENTINTERFACE_H
