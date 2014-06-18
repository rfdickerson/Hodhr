#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{

    private:

        GLuint programID;

    public:

        Shader(GLuint pId);

        ~Shader();

        GLuint getProgramID();

};


#endif
