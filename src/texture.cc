#include "texture.h"

namespace Hodhr {


Texture::Texture(std::string name)
{
    this->name = name;

}

Texture::~Texture()
{

}


int Texture::getTextureID()
{
    return textureID;
}

}
