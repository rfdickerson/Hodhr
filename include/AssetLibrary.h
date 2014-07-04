#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Model.h"

using namespace std;


class strless {
   public:
      bool operator() (const string & first, const string & second ) const  {
         return first < second;
      }
};


typedef map<std::string, unique_ptr<Model>> ModelMap;
//typedef map<const char*, unique_ptr<Model>, strless> ModelMap;
//typedef map<const char*, unique_ptr<Model>> ModelMap;

class AssetLibrary
{

private:

    ModelMap models;

public:

    AssetLibrary();
    ~AssetLibrary();

    void addTerrainPatch(std::string name);

    void addAsset(std::string, unique_ptr<Model> model);

    Model* getModel(std::string name);

};
#endif
