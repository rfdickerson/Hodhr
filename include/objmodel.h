#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <GL/glew.h>

#include "common.h"
#include "model.h"
#include "texture.h"

class Shader;

namespace Hodhr {

class ObjModel : public Model {

public:

  ObjModel();
  virtual ~ObjModel();

  void LoadFile(std::string filename);

  virtual void init( void );

  virtual void draw(const SceneNode &n);

  virtual void setShader(Shader* shader);

  void setTexture(Texture *texture);

private:

  void initData(const std::vector<HodhrVertex>& vertices,
                const std::vector<unsigned short>& indices);

  GLuint vao_id_, vbo_id_, vboi_id_;

  GLint mTextureLocation;

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

  unsigned short num_indices_;

  bool initialized;

    Texture* mTexture;

};

} // namespace

#endif // OBJMODEL_H
