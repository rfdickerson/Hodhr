#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <memory>
#include <vector>

#include "Model.h"

typedef std::vector<std::shared_ptr<Model>> ModelVector;

class AssetLibrary
{

private:

    ModelVector assets;

public:

    AssetLibrary();
    ~AssetLibrary();
    void addAsset( std::shared_ptr<Model> m );

};
#endif
