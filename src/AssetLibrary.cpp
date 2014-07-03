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

void AssetLibrary::addTerrainPatch(const char* name)
{

    auto terrain = make_unique<TerrainPatch>();
    models[name] = move(terrain);
}


Model* AssetLibrary::getModel(const char* name)
{

    std::map<const char*, unique_ptr<Model>>::iterator it;
    it = models.find(name);
    return it->second.get();
}

void AssetLibrary::addAsset(std::string name, unique_ptr<Model> model)
{
  models[name.c_str()] = std::move(model);

}
