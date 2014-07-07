#ifndef CUBEMESH_H
#define CUBEMESH_H

#include <GL/glew.h>

#include "model.h"

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

  GLint MVPMatrixLocation,
  MVMatrixLocation,
  normal_matrix_loc_,
  light_position_loc_,
  eye_direction_loc_,
  constant_attenuation_loc_,
  linear_attenuation_loc_,
  quadratic_attenuation_loc_,
  shininess_loc_,
  strength_loc_,
  light_color_loc_,
  ambient_loc_
  ;


};
}

#endif
