#ifndef CUBEMESH_H
#define CUBEMESH_H

#include <GL/glew.h>

#include "Model.h"

namespace Hodhr {

class CubeMesh : public Model
{

 public:

  CubeMesh();
  ~CubeMesh();

  virtual void init( void );

  virtual void draw(const SceneNode& node);

  virtual void setShader(Shader* shader);

 private:

  GLuint vboId, vaoId, vboiId;

  unsigned short numIndices;

  GLint MVPMatrixLocation, MVMatrixLocation;


};
}

#endif
