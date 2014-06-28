#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

class Shader
{

    private:

        std::string name;
        
        GLuint programID;

    public:

        Shader(std::string name, GLuint pId);

        ~Shader();

        GLuint getProgramID();

        std::string getName();
        
        
};


#endif
