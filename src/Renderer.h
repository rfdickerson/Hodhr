#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

class Renderer 
{

    public:
    Renderer(GLuint targetWidth, GLuint targetHeight);
    ~Renderer();

    void init ();
    void draw ();

    private:

    GLuint targetWidth;
    GLuint targetHeight;

    GLuint textureIDs[2];
    GLuint vboID;
    GLuint vaoID;
    GLuint renderBufferID[2];
    GLuint frameBufferID[2];

    GLuint screenShaderProgram;

    GLfloat* textureBuffer;

};


#endif
