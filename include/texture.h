#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>


#include "include/common.h"

namespace Hodhr {


class Texture {

public:
    Texture(std::string name, GLuint texture_id, unsigned int width, unsigned int height);

    ~Texture();

    GLuint getTextureID();
    std::string getName();
    GLuint getWidth();
    GLuint getHeight();
    


protected:

    
    std::string name_;
    
    GLuint width_;
    GLuint height_;
    GLuint texture_id_;

};

}

#endif // TEXTURE_H
