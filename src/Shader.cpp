#include <iostream>

#include "Shader.h"

Shader::Shader(std::string name, GLuint pId)
{
    this->name = name;
    programID = pId;
}

Shader::~Shader()
{

}

GLuint Shader::getProgramID()
{
    return programID;
}

std::string Shader::getName()
{
    return this->name;
}
