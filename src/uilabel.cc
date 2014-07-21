// Copyright Robert Dickerson 2014

#include "include/uilabel.h"

#include <pango/pangocairo.h>

#include <stdlib.h>

#define FONT "Sans Bold 18"
#define TEXT "The quick brown fox is so かわいい!"

namespace Hodhr {

UILabel::UILabel() {}

UILabel::~UILabel() {
  glDeleteTextures(1, &texture_id);
  fprintf(stderr, "Removing label\n");
}


void
UILabel::create_text(std::string text_string) {
  render_text(text_string.c_str(),
              &this->texture_id,
              &this->text_width,
              &this->text_height);
}

/* Draw the UI Label onto a surface */
void UILabel::draw() {
  draw_texture(
      this->text_width,
      this->text_height,
      this->texture_id);
}

/* Create a texture from the pixels for OpenGL */
unsigned int
UILabel::create_texture(
    unsigned int width,
    unsigned int height,
    unsigned char *pixels) {
  unsigned int texture_id;

  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               width,
               height,
               0,
               GL_BGRA,
               GL_UNSIGNED_BYTE,
               pixels);

  return texture_id;
}

void
UILabel::draw_texture(int width,
                      int height,
                      unsigned int texture_id) {
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glBindTexture(GL_TEXTURE_2D, 0);
}

cairo_t*
UILabel::create_cairo_context(
    int width,
    int height,
    int channels,
    cairo_surface_t** surf,
    unsigned char** buffer) {
  *buffer = (unsigned char*) calloc(channels * width * height,
                                    sizeof (unsigned char));

  *surf = cairo_image_surface_create_for_data(*buffer,
                                              CAIRO_FORMAT_ARGB32,
                                              width,
                                              height,
                                              channels * width);
  
  return cairo_create (*surf);
  
}

cairo_t*
UILabel::create_layout_context() {
  cairo_surface_t *temp_surface;
  cairo_t *context;

  temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 0, 0);
  context = cairo_create(temp_surface);
  cairo_surface_destroy(temp_surface);

  return context;
}

void
UILabel::get_text_size(PangoLayout *layout,
                       unsigned int *width,
                       unsigned int *height) {
  
  pango_layout_get_size(layout,
                        reinterpret_cast<int*>(width),
                        reinterpret_cast<int*>(height));
  *width /= PANGO_SCALE;
  *height /= PANGO_SCALE;
}
    
unsigned int
UILabel::render_text(const char *text,
                     GLuint *texture_id,
                     unsigned int *text_width,
                     unsigned int *text_height) {
  cairo_t *layout_context;
  cairo_t *render_context;
  // cairo_surface_t *temp_surface;
  cairo_surface_t *surface;
  unsigned char* surface_data = NULL;
  PangoFontDescription *desc;
  PangoLayout *layout;
  
  layout_context = create_layout_context();
    
  layout = pango_cairo_create_layout(layout_context);
  pango_layout_set_text(layout, text, -1);
    
  /* load the font */
  desc = pango_font_description_from_string(FONT);
  pango_layout_set_font_description(layout, desc);
  pango_font_description_free(desc);
    
  /* Get text dimensions and create a context to render to */
  get_text_size(layout, text_width, text_height);
  render_context = create_cairo_context(
      *text_width,
      *text_height,
      4,
      &surface,
      &surface_data);
    
  /* Render */
  cairo_set_source_rgba(render_context, 1, 1, 1, 1);
  pango_cairo_show_layout(render_context, layout);
  *texture_id = create_texture(*text_width, *text_height, surface_data);
    
  /* Clean up */
  free(surface_data);
  g_object_unref(layout);
  cairo_destroy(layout_context);
  cairo_destroy(render_context);
  
  return 0;
}    

}   // namespace Hodhr
