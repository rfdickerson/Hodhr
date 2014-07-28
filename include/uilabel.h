// Copyright Robert Dickerson 2014

#ifndef INCLUDE_UILABEL_H_
#define INCLUDE_UILABEL_H_

#include <pango/pangocairo.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

#include "include/common.h"
#include "include/uiwidget.h"

namespace Hodhr {

class Shader;

class UILabel : public UIWidget {

 public:
  UILabel(void);
  virtual ~UILabel(void);
  void create_text(std::string);
  // virtual void draw();
  // virtual void update();

  // void setOpacity(float opacity);
  // float getOpacity();

 private:

  unsigned int text_width;
  unsigned int text_height;
  
  GLuint texture_id_;
    
  // void createQuad();

  unsigned int create_texture(
    unsigned int width,
    unsigned int height,
    unsigned char *pixels);

  cairo_t*
  create_cairo_context(int width,
                       int height,
                       int channels,
                       cairo_surface_t** surf,
                       unsigned char** buffer);
  
  cairo_t* create_layout_context(void);

  void get_text_size(PangoLayout *layout,
                       unsigned int *width,
                       unsigned int *height);
    
  unsigned int
  render_text(const char *text,
                GLuint *texture_id,
                unsigned int *text_width,
                unsigned int *text_height);
};  // UILabel

}   // namespace Hodhr

#endif  // INCLUDE_UILABEL_H_
