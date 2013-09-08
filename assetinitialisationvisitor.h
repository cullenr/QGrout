#ifndef ASSETINITIALISATIONVISITOR_H
#define ASSETINITIALISATIONVISITOR_H

#include "assetvisitor.h"

class AssetInitialisationVisitor : public AssetVisitor
{
public:
    AssetInitialisationVisitor();

    void visit(ShaderAsset &shader) override;
    void visit(TextureAsset &texture) override;
    //void visit(MusicAsset &music) override;
    //void visit(SoundAsset &sound) override;
};

#endif // ASSETINITIALISATIONVISITOR_H
