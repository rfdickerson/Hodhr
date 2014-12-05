#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "model.h"

using namespace std;

/*
class strless {
   public:
      bool operator() (const string & first, const string & second ) const  {
         return first < second;
      }
};
*/

namespace Hodhr {
  typedef map<std::string, Model*> ModelMap;

  
  class AssetLibrary
  {

  private:

    ModelMap models;

  public:

    AssetLibrary();
    ~AssetLibrary();

    void addTerrainPatch(std::string name);

    void addAsset(std::string, Model* model);

    Model* getModel(std::string name);

  };
}

#endif
