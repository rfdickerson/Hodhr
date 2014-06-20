#include <GL/glew.h>
#include <iostream>

#include "TerrainPatch.h"
#include "ShaderLibrary.h"
#include "SceneNode.h"

/**
 * Terrain Patch is a section of terrain that can be swapped in and out of memory
 **/

using namespace std;

TerrainPatch::TerrainPatch()
{
    vboId = 0;
    vaoId = 0;
    vboiId = 0;
}

void TerrainPatch::init ()
{

    cout << "Building the terrain patch" << endl;

    static const float vertices[] = {
        0.5f, 1.0f, -0.5f,
        -0.5f, 0.0f, 0.5f,
        0.5f, 1.0f, 0.5f,
        0.5f, 0.0f, -0.5f
    };

    const int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &vboId);
    glBufferData(GL_ARRAY_BUFFER, 12, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &vboiId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //vaoId = glGenVertexArrays();
}


void TerrainPatch::draw(const SceneNode& node)
{

    ShaderLibrary* library = &ShaderLibrary::getInstance();
    Shader* basic = library->getShader("basic");

    glUseProgram(basic->getProgramID());

    glBindAttribLocation(basic->getProgramID(), 0, "in_Position");
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

    glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

}


TerrainPatch::~TerrainPatch()
{
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vaoId);
    cout << "Destroying terrain patch" << endl;
}

