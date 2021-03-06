// copyright Robert Dickerson 2014

#include "texturemanager.h"

#include <algorithm>
#include <memory>
#include <utility>

#include <SDL2/SDL_image.h>

namespace Hodhr {

  TextureManager::TextureManager() {
  }

  Texture*
  TextureManager::LoadTexture(std::string texture_name, std::string filename, 
			      bool generate = false) {
    
    // bool generate = true;
  
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface==NULL) {
      fprintf(stderr, "Could find file %s\n", filename.c_str());
      return NULL;
    }

  GLuint texture_id;
  int width = surface->w;
  int height = surface->h;
  
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  
  if (generate) { 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
  } else {
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  }
  
  printOglError("generate texture");
  
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  
  if (generate) {
        glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  }
  
  
  if (generate) {
      /*
      gluBuild2DMipmaps(
        GL_TEXTURE_2D,
        GL_RGBA,
        surface->w, surface->h,
        GL_RGBA,
               GL_UNSIGNED_BYTE,
               surface->pixels);
               */

      glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 surface->w, surface->h,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 surface->pixels);

        glGenerateMipmap(GL_TEXTURE_2D);

  } else {
    glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               surface->w, surface->h,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               surface->pixels);
  }
  
  printOglError("generate texture");
  
  //glTexParameteri(GL_TEXTURE_2D,GL_TE);

  SDL_FreeSurface(surface);

  glBindTexture(GL_TEXTURE_2D, 0);

  Texture* texture = new Texture(texture_name, texture_id, width, height);

  textures_[texture_name] = texture;
  
  fprintf(stdout, "Successfully created %s texture\n", texture_name.c_str());

  return textures_[texture_name];
}

}   // namespace Hodhr
