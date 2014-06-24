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
    cout << "Destroyed the Asset Library" << endl;
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

