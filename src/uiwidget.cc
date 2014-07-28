// Copyright Robert Dickerson 2014

#include <GL/glew.h>

#include "include/uiwidget.h"
#include "include/shader.h"
#include "include/texture.h"

namespace Hodhr {

UIWidget::UIWidget()
{

}

UIWidget::~UIWidget()
{

}

void UIWidget::draw()
{
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

    if (active_texture_) {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, active_texture_->getTextureID());
    } else {
      fprintf(stderr, "No texture bound\n");
	return;
    }
    
    GLint texLoc = glGetUniformLocation(active_shader_->getProgramID(), "tex");
    glUniform1i(texLoc, 0);
    // fprintf(stderr, "Coord for texture is %d\n", texLoc);

    GLint opacityLoc = glGetUniformLocation(active_shader_->getProgramID(),
                                            "Opacity");
    glUniform1f(opacityLoc, opacity_);
    // fprintf(stderr, "Coord for opacity is %d\n", opacityLoc);
    printOglError("set uniforms");

    GLint mv_matrix_loc = glGetUniformLocation(active_shader_->getProgramID(),
                          "MVMatrix");
    //glUniform4(mv_matrix_loc, mv_matrix_);
    glUniformMatrix4fv( mv_matrix_loc, 1, GL_FALSE, &mv_matrix_[0][0]);

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

void UIWidget::createQuad() {
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

void UIWidget::update()
{
  opacity_ = sin(time_);
  time_ += .005f;
  opacity_ = 1.0f;
}

// getters and setters

void UIWidget::setShader(Shader *shader) {
  fprintf(stderr, "Setting the shader for the text label to %s\n", shader->getName().c_str());
  // shader_id_ = shader->getProgramID();
  active_shader_ = shader;

}

void UIWidget::setOpacity(float opacity)
{
  if (opacity > 0 && opacity < 1) {
    opacity_ = opacity;
   }
}

float UIWidget::getOpacity() {
  return opacity_;
}

}
