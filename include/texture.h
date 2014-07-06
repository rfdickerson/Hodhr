#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace Hodhr {


class Texture {

public:
    Texture(std::string name);

    ~Texture();

    int getTextureID();

protected:

    int textureID;
    std::string name;

};

}

#endif // TEXTURE_H
