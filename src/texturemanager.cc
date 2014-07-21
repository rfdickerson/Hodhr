// copyright

#include "include/texturemanager.h"

#include <algorithm>
#include <memory>
#include <utility>



namespace Hodhr {

TextureManager::TextureManager() {
}

void
TextureManager::LoadTexture(std::string texture_name, std::string filename) {
  auto texture = std::make_unique<Texture>(texture_name);

  textures_[texture_name] = move(texture);
}

}   // namespace Hodhr
