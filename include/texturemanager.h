#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <memory>
#include <string>
#include <map>
#include <utility>

#include "texture.h"

namespace Hodhr {

class TextureManager
{

public:
TextureManager();

void LoadTexture(std::string texture_name, std::string filename);

protected:

std::map<std::string, std::unique_ptr<Texture>> textures_;
};

}


#endif // TEXTUREMANAGER_H
