#include "common.h"

#include <iostream>

#include <GL/glew.h>

int printOglError(std::string instruction)
{
  int retCode = 0;
  GLenum glErr = glGetError();
  if (glErr != GL_NO_ERROR)
  {
      std::cerr << "glError after " << instruction << " error: " << gluErrorString(glErr) << std::endl;
      retCode = 1;
  }

  return retCode;

}
