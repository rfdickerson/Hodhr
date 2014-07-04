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
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;

typedef struct _vertexStruct
{
  GLfloat position[3];
  GLfloat uv[2];
} vertexStruct;

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
  GLfloat vertices[numVertices];

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

  cout << "Vertex data:" << endl;
  for (int i=0;i<12;i++)
    {
      cout << vertices[i] << ", ";
    }

  this->numIndices = (subdivisions - 1) * (subdivisions - 1) * 2 * 3;
  cout << "Built terrain with " << numIndices << " indices" << endl;
  
  GLushort indices[numIndices];

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

  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(12));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenBuffers(1, &vboiId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLushort), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  initialized = true;

  cout << "Terrain has been initialized" << endl;
  cout << "VBO: " << vboId << "VAO: " << vaoId << endl;

  //vaoId = glGenVertexArrays();
}

/**
 * Drawing the Terrain patch
 **/
void TerrainPatch::draw(const SceneNode& node)
{
  //cout << "Drawing patch " << endl;

  //Shader* basic = shader;

  if (!initialized)
    {
      cerr << "Patch has not been initialized yet!" << vboId << " " << vaoId << endl;
      return;
    }

  glUseProgram(shader->getProgramID());

  glm::mat4 mvpMatrix = node.getMVPMatrix();

  glUniformMatrix4fv( MVPMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

  glBindAttribLocation(shader->getProgramID(), 0, "in_Position");

  glBindVertexArray(vaoId);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

  // cout << "drawing " << numIndices << " indices, " << vaoId << " VAO" << endl;
  //glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
  glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glBindVertexArray(0);

}

/**
 * Destroy the TerrainPatch
 **/
TerrainPatch::~TerrainPatch()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vboId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vaoId);


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

