#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>


#include "include/common.h"

namespace Hodhr {


class Texture {

public:
    Texture(std::string name, GLuint texture_id);

    ~Texture();

    GLuint getTextureID();

    std::string getName();


protected:

    GLuint texture_id_;
    std::string name_;

};

}

#endif // TEXTURE_H
