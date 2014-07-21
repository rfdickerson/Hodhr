// copyright Robert Dickerson 2014

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <iostream>

#include "include/common.h"
#include "include/terrainpatch.h"
#include "include/shaderlibrary.h"
#include "include/scenenode.h"

/**
 * Terrain Patch is a section of terrain that can be swapped in and out of memory
 **/


namespace Hodhr {

TerrainPatch::TerrainPatch() {
  vboId = 0;
  vaoId = 0;
  vboiId = 0;
  subdivisions = 64;
}

void TerrainPatch::init() {
  fprintf(stderr, "Creating a terrain patch\n");
  
  float step = 2.0f / static_cast<float>(subdivisions - 1);
  float uvstep = 1.0f / static_cast<float>(subdivisions -1);
  //  int numPerRow = subdivisions * 5;
  
  int numVertices = subdivisions * subdivisions;
  // HodhrVertex vertices[numVertices];
  vector<HodhrVertex> vertices(numVertices);
  
  for (int i = 0; i < subdivisions; i++) {
    for (int j = 0; j < subdivisions; j++) {
      // put the position down
      int e = i*subdivisions+j;
      vertices[e].x = -1.0f + (step * static_cast<float>(i));
      vertices[e].y = 0;
      vertices[e].z = -1.0f + (step * static_cast<float>(j));

      vertices[e].nx = 0.0f;
      vertices[e].ny = 1.0f;
      vertices[e].nz = 0.0f;

      // put the uv coords down
      vertices[e].s0 = (uvstep * i);
      vertices[e].t0 = (uvstep * j);

    }
  }

  
  numIndices = (subdivisions - 1) * (subdivisions - 1) * 2 * 3;
  // cout << "Built terrain with " << numIndices << " indices" << endl;
  fprintf(stderr, "Built terrain with %d indices\n", numIndices);
  
  std::vector<GLuint> indices(numIndices);

  int numPerRow = (subdivisions-1)*6;
  // numPerRow = (subdivisions - 1) * 6;
  for (int i = 0; i < subdivisions - 1; i++) {
    for (int j = 0; j < subdivisions - 1; j++) {
      int baseindex = i * (subdivisions) + j;

      GLuint a = baseindex;
      GLuint b = baseindex + subdivisions;
      GLuint c = b + 1;
      GLuint d = a + 1;

      /*
      indices[(numPerRow * i) + (6 * j) + 0] = a;
      indices[(numPerRow * i) + (6 * j) + 1] = b;
      indices[(numPerRow * i) + (6 * j) + 2] = c;

      indices[(numPerRow * i) + (6 * j) + 3] = c;
      indices[(numPerRow * i) + (6 * j) + 4] = d;
      indices[(numPerRow * i) + (6 * j) + 5] = a;
      */

      indices.push_back(a);
      indices.push_back(b);
      indices.push_back(c);

      indices.push_back(c);
      indices.push_back(d);
      indices.push_back(a);
    }
  }

  for (int i = 0; i < 12; ++i) {
    // cout << indices[i] << ", ";
    fprintf(stderr, "%d", indices[i]);
  }


  // glGenVertexArrays(1, &vaoId);
  // glBindVertexArray(vaoId);
  // printOglError("vertex array");

  glGenBuffers(1, &vboId);
  printOglError("Gen Buffers");
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER,
               numVertices*sizeof(HodhrVertex),
               &vertices[0].x,
               GL_STATIC_DRAW);
  printOglError("Creating VBO");

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(HodhrVertex), BUFFER_OFFSET(0));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        sizeof(HodhrVertex), BUFFER_OFFSET(12));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                        sizeof(HodhrVertex), BUFFER_OFFSET(24));

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);

  glGenBuffers(1, &vboiId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices,
               &indices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  initialized = true;

  printOglError("Creating terrain");
  
  //  cout << "Terrain has been initialized" << endl;
  // cout << "VBO: " << vboId << "VAO: " << vaoId << endl;
  
  // vaoId = glGenVertexArrays();
}

/**
 * Drawing the Terrain patch
 **/
void TerrainPatch::draw(const SceneNode& node) {
  
  if (!initialized) {
    fprintf(stderr, "Patch has not been initialized yet\n");
    return;
  }
  
  glUseProgram(shader->getProgramID());
  // cout << "using shader " << shader->getProgramID() << endl;

  glm::mat4 mvpMatrix = node.getMVPMatrix();

  glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
  glBindAttribLocation(shader->getProgramID(), 0, "in_Position");

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  //  cout << mvpMatrix[0][0] << endl;
  //  glBindAttribLocation(shader->getProgramID(), 0, "in_Position");
  //  glBindAttribLocation(shader->getProgramID(), 1, "in_tex_coord");
  
  //  glBindVertexArray(vaoId);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  //  glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  
  glBindVertexArray(0);

  printOglError("Draw terrain patch");
}

/**
 * Destroy the TerrainPatch
 **/
TerrainPatch::~TerrainPatch() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboiId);
  glBindVertexArray(0);
  // glDeleteVertexArrays(1, &vaoId);
  fprintf(stderr, "Destroying terrain patch\n");
}

void TerrainPatch::setShader(Shader* shader) {
  Model::setShader(shader);
  MVPMatrixLocation = glGetUniformLocation(shader->getProgramID(), "MVPMatrix");
}

}  // namespace Hodhr

