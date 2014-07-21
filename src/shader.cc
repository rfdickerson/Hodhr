
#include "include/shader.h"

namespace Hodhr {

Shader::Shader(std::string name, GLuint pId) {
  this->name = name;
  programID = pId;
}

Shader::~Shader() {
  // std::cout << "Deleted shader " << this->name << std::endl;
  fprintf(stderr, "Deleted shader %s\n", this->name.c_str());
}

GLuint Shader::getProgramID() {
  return programID;
}

std::string Shader::getName() {
  return this->name;
}

}  // namespace Hodhr
