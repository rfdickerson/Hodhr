#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    subdivisions = 128;
}



void TerrainPatch::init ()
{

    cout << "Building the terrain patch" << endl;

    float step = 2.0f / (subdivisions - 1);
    float uvstep = 1.0f / (subdivisions -1);
    int numPerRow = subdivisions * 5;

    int numVertices = subdivisions * subdivisions * 5;
    float vertices[numVertices];

     for (int i = 0; i < subdivisions; i++) {
            for (int j = 0; j < subdivisions; j++) {
                // put the position down
                vertices[(numPerRow * i) + (5 * j) + 0] = -1.0f + (step * i);
                vertices[(numPerRow * i) + (5 * j) + 1] = 0;
                vertices[(numPerRow * i) + (5 * j) + 2] = -1.0f + (step * j);

                // put the uv coords down
                vertices[(numPerRow * i) + (5 * j) + 3] = (uvstep * i);
                vertices[(numPerRow * i) + (5 * j) + 4] = (uvstep * j);
            }
        }


    numIndices = (subdivisions - 1) * (subdivisions - 1) * 2 * 3;
     int indices[numIndices];

        numPerRow = (subdivisions - 1) * 6;
        for (int i = 0; i < subdivisions - 1; i++) {
            for (int j = 0; j < subdivisions - 1; j++) {
                int baseindex = i * (subdivisions) + j;

                int a = baseindex;
                int b = baseindex + subdivisions;
                int c = b + 1;
                int d = a + 1;

                indices[(numPerRow * i) + (6 * j) + 0] = a;
                indices[(numPerRow * i) + (6 * j) + 1] = b;
                indices[(numPerRow * i) + (6 * j) + 2] = c;

                indices[(numPerRow * i) + (6 * j) + 3] = c;
                indices[(numPerRow * i) + (6 * j) + 4] = d;
                indices[(numPerRow * i) + (6 * j) + 5] = a;
            }
        }
    /*
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
    */

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &vboId);
    glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 20, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 20, (void*)12);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &vboiId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //vaoId = glGenVertexArrays();
}


void TerrainPatch::draw(const SceneNode& node)
{
    //cout << "draw terrain" << endl;
    //ShaderLibrary* library = &ShaderLibrary::getInstance();
    //Shader* basic = library->getShader("basic");
    Shader* basic = shader;

    glUseProgram(basic->getProgramID());
    //cout << "drawing with shader " << basic->getName() << endl;

    //int MVPMatrixLocation = glGetUniformLocation(basic->getProgramID(), "MVPMatrix");
    glm::mat4 mvpMatrix = node.getMVPMatrix();
    glUniformMatrix4fv( MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr( mvpMatrix));

    glBindAttribLocation(basic->getProgramID(), 0, "in_Position");
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

    glDrawElements(GL_TRIANGLE_FAN, numIndices, GL_UNSIGNED_BYTE, 0);

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

void TerrainPatch::setShader(Shader* shader)
{
    Model::setShader(shader);
    MVPMatrixLocation = glGetUniformLocation(shader->getProgramID(), "MVPMatrix");
    cout << "Set terrain shader " << shader->getName() 
        << " with pID " << shader->getProgramID() 
        << " location for mvp matrix is " << MVPMatrixLocation << endl;
    
}

