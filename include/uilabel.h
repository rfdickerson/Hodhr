// Copyright Robert Dickerson 2014

#ifndef INCLUDE_UILABEL_H_
#define INCLUDE_UILABEL_H_

#include <pango/pangocairo.h>
#include <GL/glew.h>

#include <string>

#include "include/common.h"
namespace Hodhr {

class UILabel {
 public:
UILabel(void);
~UILabel(void);
void create_text(std::string);
void draw();

 private:

GLuint texture_id;
unsigned int text_width;
unsigned int text_height;
    

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

void draw_texture(int width,
                  int height,
                  GLuint texture_id);

cairo_t* create_layout_context(void);

void get_text_size(PangoLayout *layout,
                     unsigned int *width,
                     unsigned int *height);
    
unsigned int
render_text(const char *text,
              GLuint *texture_id,
              unsigned int *text_width,
              unsigned int *text_height);
};

}   // namespace Hodhr

#endif  // INCLUDE_UILABEL_H_
