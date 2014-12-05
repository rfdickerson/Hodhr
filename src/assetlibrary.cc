// Copyright Robert Dickerson 2014

// # <iostream>
#include <memory>
#include <string>
#include <utility>

#include "assetlibrary.h"
#include "terrainpatch.h"


namespace Hodhr {



AssetLibrary::AssetLibrary()
{
    
}

AssetLibrary::~AssetLibrary() {
  //  cout << "Cleaning up the asset Library" << endl;
  fprintf(stderr, "Cleaning up the asset library\n");
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
    TerrainPatch* terrain = new TerrainPatch();
    models[name] = terrain;
  }


  Model* AssetLibrary::getModel(std::string assetName) {
    return models[assetName];
  }

  void AssetLibrary::addAsset(std::string name, Model* model) {
    models[name] = model;
  }

}  // namespace Hodhr
