#ifndef INCLUDE_UIWIDGET_H
#define INCLUDE_UIWIDGET_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

#include "include/common.h"

namespace Hodhr {

  //forward defines
class Shader;  
class Texture;

class UIWidget {
  
public:
  
  UIWidget();
  virtual ~UIWidget();
  
  virtual void draw();
  virtual void update();
  
  void setShader(Shader* shader);
  void setOpacity(float opacity);
  float getOpacity();
  
protected:
  
  void createQuad();
  
  GLuint width_, height_;
  
  // GLuint texture_id_;
  
  GLuint vbo_id_, vboi_id_, vao_id_;
  // GLint shader_id_;
  glm::mat4 mv_matrix_;

  float time_;
  float opacity_;

  Shader* active_shader_;
  Texture* active_texture_;
  
};
  
}  // namespace Hodhr

#endif // INCLUDE_UIWIDGET_H