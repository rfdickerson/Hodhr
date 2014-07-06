#include <iostream>

#include "Shader.h"
#include "CubeMesh.h"

using namespace std;

namespace Hodhr {


CubeMesh::CubeMesh ()
{
  cout << "Created a cube mesh asset" << endl;
}

/**
 * Destroy the cube mesh buffers
 **/
CubeMesh::~CubeMesh ()
{

  cout << "Destroying the cube mesh" << endl;
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboiId);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vaoId);


}

void CubeMesh::init( void )
{
  float vertices[] = {
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f
  };

  int numVertices = 21;

  unsigned short indices[] = {
      0, 1, 2,
      0, 2, 3,
      0, 3, 4,
      4, 3, 5,
      0, 4, 6,
      0, 6, 1
            
    };

  numIndices = 18;
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
 
  glBindVertexArray(0);

  glGenBuffers(1, &vboiId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  initialized = true;


}

void CubeMesh::draw(const SceneNode& node)
{

  if (!initialized)
    {
      cerr << "Cube is not initialized yet" << endl;
      return;
    }

  glUseProgram(shader->getProgramID());

  glm::mat4 mvpMatrix = node.getMVPMatrix();

  glUniformMatrix4fv( MVPMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
  glBindAttribLocation(shader->getProgramID(), 0, "in_Position");

  glBindVertexArray(vaoId);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

  glUseProgram(shader->getProgramID());
  
  //std::cout << "draw cube with indices " << numIndices << std::endl;

  //glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_SHORT, NULL);

  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void CubeMesh::setShader(Shader* shader)
{
  Model::setShader(shader);
  MVPMatrixLocation = glGetUniformLocation(shader->getProgramID(), "MVPMatrix");
  cout << "Set cube shader " << shader->getName() 
       << " with pID " << shader->getProgramID() 
       << " location for mvp matrix is " << MVPMatrixLocation << endl;
  
}

}
