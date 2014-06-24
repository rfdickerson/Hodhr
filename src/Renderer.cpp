/*
   The MIT License

   Copyright (c) 2009 Campaign rfdickerson@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "Renderer.h"
#include "Shader.h"
#include "ShaderLibrary.h"
#include "TerrainPatch.h"

Renderer::Renderer (GLuint targetWidth, GLuint targetHeight)
{

    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;

    textureBuffer = new GLfloat[targetWidth * targetHeight * 32];

/*
    ShaderLibrary* library = &ShaderLibrary::getInstance();
    library->addShader("screen", "resources/shaders/screen.vs", "resources/shaders/screen.fs");
    Shader* screenShader = library->getShader("screen");
    screenShaderProgram = screenShader->getProgramID();
    std::cout << "Screen shader program ID: " << screenShaderProgram << std::endl;
    */

    // initialize the root scene node
    rootSceneNode = new SceneNode();

    std::shared_ptr<TerrainPatch> terrain ( new TerrainPatch());
    terrain->init();

    std::shared_ptr<SceneNode> terrainNode (new SceneNode());
    terrainNode->setAsset(terrain);
    rootSceneNode->addChild(terrainNode);
}

Renderer::~Renderer ()
{
    std::cout << "Cleaning up render system" << std::endl;
    //delete terrain;


    glDeleteFramebuffers(2, frameBufferID);
    glDeleteRenderbuffers(2, renderBufferID);

    glDeleteTextures(2, textureIDs);
    glDeleteBuffers(1,&vaoID);
    glDeleteBuffers(1,&vboID);

}

void Renderer::draw ()
{

// draw the scene first
    glClearColor(0.2f, 0.2f, 0.2f, 1);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

    if (rootSceneNode != NULL) {
        rootSceneNode->draw();
    }

// draw the deferred texture rendering
    //glUseProgram(screenShaderProgram);
    glUseProgram(screenShader->getProgramID());

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0,0, targetWidth, targetHeight);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glUseProgram(screenShaderProgram);

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);

    glReadBuffer(GL_COLOR_ATTACHMENT0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

}

void Renderer::init ()
{



    /* Create the render buffers */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(2, textureIDs);

    std::cout << "Texture ID for Color Channel is " << textureIDs[0] << std::endl;

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

    std::cout << "Texture ID for Depth Channel is " << textureIDs[1] << std::endl;

    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);

    glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_DEPTH_COMPONENT,
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

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(2, renderBufferID);
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

    glGenFramebuffers(2,frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID[0]);

    glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            textureIDs[0],
            0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

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

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 20, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 20, (void*)12);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Renderer::setScreenShader(Shader* s)
{
    this->screenShader = s;
}
