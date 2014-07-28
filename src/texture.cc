// Copyright Robert Dickerson 2014

#include <iostream>
#include <cstdio>


#include "include/texture.h"



namespace Hodhr {


Texture::Texture(std::string name, GLuint texture_id, GLuint width, GLuint height) {
  this->name_ = name;
  this->texture_id_ = texture_id;
  this->width_ = width;
  this->height_ = height;
}

Texture::~Texture() {
  glDeleteTextures(1, &texture_id_);
  fprintf(stderr, "Deleted %s texture\n", name_.c_str());
}


GLuint Texture::getTextureID() {
    return texture_id_;
}

std::string Texture::getName() {
  return name_;
}

GLuint Texture::getWidth() {
  return width_;
}
  
GLuint Texture::getHeight() {
  return height_;
}

}  // namespace Hodhr
