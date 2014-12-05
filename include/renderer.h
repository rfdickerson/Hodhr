// Copyright Robert Dickerson 2014

#ifndef INCLUDE_RENDERER_H_
#define INCLUDE_RENDERER_H_

#include <GL/glew.h>

#include <memory>

#include "scenenode.h"

namespace Hodhr {

  class Camera;
  class Shader;
  class UI;
  
 class Renderer
 {

 public:
   Renderer(GLuint targetWidth, GLuint targetHeight);
   virtual ~Renderer();
   
   void init();
   void draw();
   
   void drawOffscreenSurface();
   void drawScene();
   void drawUI();
   
   void setCamera(Camera* c);

   void setScreenShader(Shader* s);
   
   void setRootSceneNode(SceneNode* sceneNode);

   void setUserInterface(UI* ui);
   
 private:

   GLuint targetWidth;
   GLuint targetHeight;
   
   GLuint textureIDs[2];
   GLuint vboID;
   GLuint vaoID;
   GLuint renderBufferID[2];
   GLuint frameBufferID[2];
   
   // GLuint screenShaderProgram;
   
   GLfloat* textureBuffer;
   
   SceneNode* mRootSceneNode;
   
   Shader* mScreenShader;
   
   Camera* mCamera;
   
   UI* mUI;

 };

}  // namespace Hodhr

#endif  // INCLUDE_RENDERER_H_
