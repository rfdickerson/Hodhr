/**
   The MIT License

   Copyright (c) 2009 Campaign rfdickerson@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be d in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "common.h"
#include "renderer.h"
#include "shader.h"
#include "shaderlibrary.h"
#include "terrainpatch.h"
#include "ui.h"

namespace Hodhr {


  Renderer::Renderer(GLuint targetWidth, GLuint targetHeight) {
    
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;
    
    textureBuffer = new GLfloat[targetWidth * targetHeight * 32];
  }

  Renderer::~Renderer() {

    fprintf(stderr, "Cleaning up render system\n");

    glDeleteFramebuffers(2, frameBufferID);
    glDeleteRenderbuffers(2, renderBufferID);

    glDeleteTextures(2, textureIDs);
    glDeleteBuffers(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    
    printOglError("Clean up render system");
  }

  /*
   * Draw the Scene
   */
  void Renderer::drawScene()
  {
    if (!mCamera) {
      fprintf(stderr, "No camera attached\n");
      return;
    }

    // update the transformation matrices
    mRootSceneNode->updateAll(*mCamera);
    
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(0);
    
    if (mRootSceneNode != NULL) {
      mRootSceneNode->draw();
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
  }

  void Renderer::drawOffscreenSurface()
  {
    // draw the deferred texture rendering
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    glUseProgram(mScreenShader->getProgramID());
    
    
    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    int texLoc = glGetUniformLocation(mScreenShader->getProgramID(), "tex");
    glUniform1i(texLoc, 0);
    // fprintf(stderr, "Location of texture for deferred surface is %d\n", texLoc);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
    texLoc = glGetUniformLocation(mScreenShader->getProgramID(), "depthTex");
    glUniform1i(texLoc, 1);
    
    //  glReadBuffer(GL_COLOR_ATTACHMENT0);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
  }
  

  void Renderer::drawUI()
  {
    // draw the UI on top of this
    if (mUI) {
      // mUI->draw();
      
    }
  }
  
  void Renderer::draw() {
    
    drawScene();
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, targetWidth, targetHeight);
    
    drawOffscreenSurface();
    
    // drawUI();
    
    
  }

  void Renderer::init() {
    printOglError("Begin Render System init");
    /* Create the render buffers */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    
    // culling stuff

    /*
      glFrontFace(GL_CCW);
      glCullFace(GL_BACK);
      glEnable(GL_CULL_FACE);
    */
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthFunc(GL_LESS);
    
    glGenTextures(2, textureIDs);
    
    fprintf(stderr, "Texture ID for color channel is %d\n", textureIDs[0]);

    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    glTexImage2D(GL_TEXTURE_2D,
		 0,
		 GL_RGBA,
		 targetWidth,
		 targetHeight,
		 0,
		 GL_RGBA,
		 GL_UNSIGNED_BYTE,
		 textureBuffer);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // enable anisotropic filtering
    GLfloat fLargest;

    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
    fprintf(stdout, "Setting anisotropic filtering to %f\n", fLargest);

    fprintf(stderr, "Texture ID for depth channel is %d\n", textureIDs[1]);

    printOglError("Create deferred rendering color texture");

    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);

    glTexImage2D(GL_TEXTURE_2D,
		 0,
		 GL_DEPTH_COMPONENT32,
		 targetWidth,
		 targetHeight,
		 0,
		 GL_DEPTH_COMPONENT,
		 GL_FLOAT,
		 textureBuffer);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
    printOglError("Create deferred rendering depth texture");

    glGenRenderbuffers(2, renderBufferID);

    /*
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID[0]);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, targetWidth, targetHeight);

    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID[1]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, targetWidth, targetHeight);

    glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_RENDERBUFFER,
            renderBufferID[0]
            );


    glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER,
            renderBufferID[1]
            );

    glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindRenderbuffer(GL_FRAMEBUFFER, 0);
    */

    glGenFramebuffers(2, frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID[0]);

    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            textureIDs[0],
            0);

    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
    glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            textureIDs[1],
            0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  printOglError("Create Framebuffer");


    // create the render quad surface

    static const GLfloat quadData[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*20, quadData, GL_STATIC_DRAW);
    // cout << "Screen vertex buffer is " << vboID << endl;
    fprintf(stderr, "Screen vertex buffer is %d\n", vboID);
    
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 20,
                          reinterpret_cast<void*>(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 20,
                          reinterpret_cast<void*>(12));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    printOglError("Create deferred rendering surface");
  }

  void Renderer::setScreenShader(Shader* s) {
    this->mScreenShader = s;
  }

  void Renderer::setCamera(Camera* c) {
    this->mCamera = c;
  }

  void Renderer::setRootSceneNode(SceneNode* sceneNode) {
    this->mRootSceneNode = sceneNode;
  }

  void Renderer::setUserInterface(UI* ui) {
    this->mUI = ui;
  }

}  // namespace Hodhr
