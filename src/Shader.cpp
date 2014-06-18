#include <iostream>

#include "Shader.h"

Shader::Shader(GLuint pId)
{
    programID = pId;
}

Shader::~Shader()
{

}

GLuint Shader::getProgramID()
{
    return programID;
}


