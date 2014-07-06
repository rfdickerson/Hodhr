#include <utility>
#include <algorithm>
#include <memory>

#include "texturemanager.h"

using namespace Hodhr;

TextureManager::TextureManager()
{
}

void TextureManager::loadTexture(std::string name, std::string filename)
{

    auto texture = std::make_unique<Texture>(name);

    textures[name] = move(texture);

}
