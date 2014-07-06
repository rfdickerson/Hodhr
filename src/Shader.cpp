#include <iostream>

#include "Shader.h"

namespace Hodhr {

Shader::Shader(std::string name, GLuint pId)
{
    this->name = name;
    programID = pId;
}

Shader::~Shader()
{
    std::cout << "Deleted shader " << this->name << std::endl;
}

GLuint Shader::getProgramID()
{
    return programID;
}

std::string Shader::getName()
{
    return this->name;
}

}
