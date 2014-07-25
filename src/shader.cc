
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

GLuint Shader::getProgramID() const {
  return programID;
}

std::string Shader::getName() {
  return this->name;
}

std::vector<std::string> Shader::getActiveUniforms() const
{

  std::vector<std::string> activeUniforms;

  GLint numUniforms = 0;
  // check the active uniforms
  glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);
  //fprintf(stderr, "%s shader has %d active uniforms", shaderName.c_str(), numUniforms);

  GLsizei maxStringSize = 80;
  char uniformName[maxStringSize];
  for (int i=0;i<numUniforms;++i)
    {
      glGetActiveUniformName(programID, i, maxStringSize, NULL, uniformName);
      fprintf(stderr, "%s, ", uniformName);
    }
  fprintf(stderr, "\nAdded %s to library with program ID %d\n", name.c_str(), programID);

  return activeUniforms;
}

}  // namespace Hodhr
