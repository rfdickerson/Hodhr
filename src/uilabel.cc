// Copyright Robert Dickerson 2014

#include "include/common.h"
#include "include/uilabel.h"
#include "include/shader.h"

#include <pango/pangocairo.h>

#include <stdlib.h>
#include <vector>

#define FONT "Sans Bold 18"
#define TEXT "The quick brown fox is so かわいい!"

namespace Hodhr {

UILabel::UILabel() {
  // createQuad();
  vbo_id_ = 0;
  vao_id_ = 0;
  vboi_id_ = 0;
}

UILabel::~UILabel() {

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo_id_);

  glDeleteTextures(1, &texture_id_);
  glDeleteBuffers(1, &vao_id_);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboi_id_);


  fprintf(stderr, "Destroyed the label\n");
}

void UILabel::setShader(Shader *shader) {
  fprintf(stderr, "Setting the shader for the text label to %s\n", shader->getName().c_str());
  // shader_id_ = shader->getProgramID();
  active_shader_ = shader;

}

void
UILabel::create_text(std::string text_string) {
  render_text(text_string.c_str(),
              &this->texture_id_,
              &this->text_width,
              &this->text_height);

  createQuad();
}

/* Draw the UI Label onto a surface */
void UILabel::draw() {
  // fprintf(stderr, "Drawing texture id: %d", texture_id);

  draw_texture(
      this->text_width,
      this->text_height,
      this->texture_id_);
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

void UILabel::createQuad() {
  // create the render quad surface

  /*
    static const GLfloat quadData[] = {
           -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
           1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
          -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
     };
*/

  std::vector<HodhrVertex> quadData(4);
  HodhrVertex v1, v2, v3, v4;
  v1.x = -1.0f; v1.y = -1.0f; v1.z = 0.0f; v1.s = 0.0f; v1.t = 1.0f; v1.nx = 0; v1.ny = 0; v1.nz = 0;
  v2.x = 1.0f; v2.y = -1.0f; v2.z = 0.0f; v2.s = 1.0f; v2.t = 1.0f; v2.nx = 0; v2.ny = 0; v2.nz = 0;
  v3.x = 1.0f; v3.y = 1.0f;  v3.z = 0.0f; v3.s = 1.0f; v3.t = 0.0f; v3.nx = 0; v3.ny = 0; v3.nz = 0;
  v4.x = -1.0f; v4.y = 1.0f;  v4.z = 0.0f; v4.s = 0.0f; v4.t = 0.0f; v4.nx = 0; v4.ny = 0; v4.nz = 0;

  quadData[0] = v1;
  quadData[1] = v2;
  quadData[2] = v3;
  quadData[3] = v4;

  std::vector<GLushort> pindices(6);
  pindices[0] = 0;
  pindices[1] = 3;
  pindices[2] = 1;
  pindices[3] = 1;
  pindices[4] = 3;
  pindices[5] = 2;

  glGenVertexArrays(1, &vao_id_);
  glBindVertexArray(vao_id_);

  glGenBuffers(1, &vbo_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
  glBufferData(GL_ARRAY_BUFFER, quadData.size()*sizeof(HodhrVertex),
               &quadData[0].x, GL_STATIC_DRAW);


  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex),
                         BUFFER_OFFSET(0));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex),
                         BUFFER_OFFSET(12));

  glEnableVertexAttribArray(2);
   
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex),
                        BUFFER_OFFSET(24));


  glGenBuffers(1, &vboi_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, pindices.size()*sizeof(GLushort),
               &pindices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  fprintf(stderr, "Created quad for label, VBO id %d\n", vbo_id_);
}

void UILabel::draw_texture(int width,
                           int height,
                           unsigned int texture_id) {

  // glClear (GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  //glClear(GL_DEPTH_BUFFER_BIT);

  // glViewport (0, 0, 1280, 720);
  
  glUseProgram(active_shader_->getProgramID());

  glBindVertexArray(vao_id_);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  GLint texLoc = glGetUniformLocation(active_shader_->getProgramID(), "tex");
  glUniform1i(texLoc, 0);
  fprintf(stderr, "Coord for texture is %d\n", texLoc);

  GLint opacityLoc = glGetUniformLocation(active_shader_->getProgramID(),
                                          "Opacity");
  glUniform1f(opacityLoc, 0.8f);
  fprintf(stderr, "Coord for opacity is %d\n", opacityLoc);
  printOglError("set uniforms");

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);
  printOglError("bind buffer");

  // glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  glBindTexture(GL_TEXTURE_2D, 0);

  glUseProgram(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  printOglError("draw UILabel");

  glEnable(GL_DEPTH_TEST);

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

cairo_t* UILabel::create_layout_context() {
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
