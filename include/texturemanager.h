// Copyright Robert Dickerson 2014

#ifndef INCLUDE_TEXTUREMANAGER_H_
#define INCLUDE_TEXTUREMANAGER_H_


#include <memory>
#include <string>
#include <map>
#include <utility>

#include "texture.h"

namespace Hodhr {

  /*
   * Texture Manager contains a library of all the loaded textures on the GPU
   */
  class TextureManager {
  public:
    TextureManager();
    Texture* LoadTexture(std::string texture_name, std::string filename, bool generate);
    
   protected:
    std::map<std::string, Texture*> textures_;
  };
}  // namespace Hodhr


#endif  // INCLUDE_TEXTUREMANAGER_H_
