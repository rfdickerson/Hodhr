#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "SceneNode.h"

class Shader;

class Renderer
{

    public:
    Renderer(GLuint targetWidth, GLuint targetHeight);
    ~Renderer();

    void init ();
    void draw ();

    void setScreenShader( Shader* s);

    private:

    GLuint targetWidth;
    GLuint targetHeight;

    GLuint textureIDs[2];
    GLuint vboID;
    GLuint vaoID;
    GLuint renderBufferID[2];
    GLuint frameBufferID[2];

    //GLuint screenShaderProgram;

    GLfloat* textureBuffer;

    SceneNode* rootSceneNode;

    Shader* screenShader;

};


#endif
