#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>

namespace Hodhr {

class Shader
{

    private:

        std::string name;
        
        GLuint programID;

    public:

        Shader(std::string name, GLuint pId);

        ~Shader();

        GLuint getProgramID() const;

        std::string getName();

        std::vector<std::string> getActiveUniforms() const;
        
        
};

}

#endif
