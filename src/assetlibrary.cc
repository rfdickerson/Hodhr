// Copyright Robert Dickerson 2014

// #include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "include/assetlibrary.h"
#include "include/terrainpatch.h"


namespace Hodhr {



AssetLibrary::AssetLibrary()
{
    
}

AssetLibrary::~AssetLibrary() {
  //  cout << "Cleaning up the asset Library" << endl;
  fprintf(stderr, "Cleaning up the asset library");
  // models.erase();

  /*
    for (auto iter = models.begin(); iter != models.end(); ++iter)
    {
    iter->second.release();
    
    }
    
    models.clear();
  */
}

void AssetLibrary::addTerrainPatch(std::string name) {
  auto terrain = make_unique<TerrainPatch>();
  models[name] = move(terrain);
}


Model* AssetLibrary::getModel(std::string assetName) {
  return models[assetName].get();
}

void AssetLibrary::addAsset(std::string name, unique_ptr<Model> model) {
  models[name] = std::move(model);
}

}  // namespace Hodhr
