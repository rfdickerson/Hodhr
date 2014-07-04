#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "AssetLibrary.h"
#include "TerrainPatch.h"

using namespace std;

AssetLibrary::AssetLibrary()
{
    
}

AssetLibrary::~AssetLibrary()
{
    cout << "Cleaning up the asset Library" << endl;
    models.clear();
}

void AssetLibrary::addTerrainPatch(std::string name)
{

    auto terrain = make_unique<TerrainPatch>();
    models[name] = move(terrain);
}


Model* AssetLibrary::getModel(std::string assetName)
{

  return models[assetName].get();
}

void AssetLibrary::addAsset(std::string name, unique_ptr<Model> model)
{
  models[name] = std::move(model);

}
