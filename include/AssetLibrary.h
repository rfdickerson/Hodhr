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


typedef map<const char*, unique_ptr<Model>, strless> ModelMap;
//typedef map<const char*, unique_ptr<Model>> ModelMap;

class AssetLibrary
{

private:

    ModelMap models;

public:

    AssetLibrary();
    ~AssetLibrary();

    void addTerrainPatch(const char* name);

    Model* getModel(const char* name);

};
#endif
