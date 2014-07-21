// Copyright Robert Dickerson 2014

#include "include/texture.h"

namespace Hodhr {


Texture::Texture(std::string name) {
    this->name = name;
}

Texture::~Texture() { }


int Texture::getTextureID() {
    return textureID;
}

}  // namespace Hodhr
