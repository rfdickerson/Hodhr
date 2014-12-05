// Copyright Robert Dickerson

#include <GL/glew.h>
#include "common.h"

namespace Hodhr {

  int
  printOglError(std::string instruction) {
    int retCode = 0;
    GLenum glErr = glGetError();
    if (glErr != GL_NO_ERROR) {
      fprintf(stderr,
	      "OpenGL error after %s, error was %s\n",
	      instruction.c_str(), gluErrorString(glErr));
      retCode = 1;
    }
    return retCode;
  }
  
}  // namespace Hodhr
