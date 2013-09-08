#ifndef ASSETVISITOR_H
#define ASSETVISITOR_H

class ShaderAsset;
class TextureAsset;
class SoundAsset;
class MusicAsset;

class AssetVisitor
{
public:
    virtual void visit(ShaderAsset &shader) = 0;
    virtual void visit(TextureAsset &texture) = 0;
    //virtual void visit(SoundAsset &sound) = 0;
    //virtual void visit(MusicAsset &music) = 0;
};

#endif // ASSETVISITOR_H
