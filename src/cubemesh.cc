#include <iostream>

#include "common.h"
#include "shader.h"
#include "cubemesh.h"

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

  HodhrVertex vertices[30];

  /*
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
  */

  /*
  short b[][2] = {
    {0,0},
    {0,1},
    {1,0},
    {1,1}
  };
  */

  float nx, ny, nz;

      // bottom face

  nx = 0;
  ny = 1;
  nz = 0;

        vertices[0].x = -1.0;
        vertices[0].y = -1.0;
        vertices[0].z = -1.0;
        vertices[0].nx = nx;
        vertices[0].ny = ny;
        vertices[0].nz = nz;

        vertices[1].x = -1.0;
        vertices[1].y = -1.0;
        vertices[1].z = 1.0;
        vertices[1].nx = nx;
        vertices[1].ny = ny;
        vertices[1].nz = nz;

        vertices[2].x = 1.0;
        vertices[2].y = -1.0;
        vertices[2].z = 1.0;
        vertices[2].nx = nx;
        vertices[2].ny = ny;
        vertices[2].nz = nz;

        vertices[3].x = 1.0;
        vertices[3].y = -1.0;
        vertices[3].z = -1.0;
        vertices[3].nx = nx;
        vertices[3].ny = ny;
        vertices[3].nz = nz;


        // top face
        nx = 0;
        ny = -1;
        nz = 0;

        vertices[4].x = -1.0;
        vertices[4].y = 1.0;
        vertices[4].z = -1.0;
        vertices[4].nx = nx;
        vertices[4].ny = ny;
        vertices[4].nz = nz;

        vertices[5].x = -1.0;
        vertices[5].y = 1.0;
        vertices[5].z = 1.0;
        vertices[5].nx = nx;
        vertices[5].ny = ny;
        vertices[5].nz = nz;

        vertices[6].x = 1.0;
        vertices[6].y = 1.0;
        vertices[6].z = 1.0;
        vertices[6].nx = nx;
        vertices[6].ny = ny;
        vertices[6].nz = nz;

        vertices[7].x = 1.0;
        vertices[7].y = 1.0;
        vertices[7].z = -1.0;
        vertices[7].nx = nx;
        vertices[7].ny = ny;
        vertices[7].nz = nz;



        // front face

        nx = -1;
        ny = 0;
        nz = 0;

        vertices[8].x = -1.0;
        vertices[8].y = -1.0;
        vertices[8].z = -1.0;
        vertices[8].nx = nx;
        vertices[8].ny = ny;
        vertices[8].nz = nz;

        vertices[9].x = -1.0;
        vertices[9].y = 1.0;
        vertices[9].z = -1.0;
        vertices[9].nx = nx;
        vertices[9].ny = ny;
        vertices[9].nz = nz;

        vertices[10].x = 1.0;
        vertices[10].y = 1.0;
        vertices[10].z = -1.0;
        vertices[10].nx = nx;
        vertices[10].ny = ny;
        vertices[10].nz = nz;

        vertices[11].x = 1.0;
        vertices[11].y = -1.0;
        vertices[11].z = -1.0;
        vertices[11].nx = nx;
        vertices[11].ny = ny;
        vertices[11].nz = nz;

        // back face
        nx = 1;
        ny = 0;
        nz = 0;

        vertices[12].x = -1.0;
        vertices[12].y = -1.0;
        vertices[12].z = 1.0;
        vertices[12].nx = nx;
        vertices[12].ny = ny;
        vertices[12].nz = nz;

        vertices[13].x = -1.0;
        vertices[13].y = 1.0;
        vertices[13].z = 1.0;
        vertices[13].nx = nx;
        vertices[13].ny = ny;
        vertices[13].nz = nz;

        vertices[14].x = 1.0;
        vertices[14].y = 1.0;
        vertices[14].z = 1.0;
        vertices[14].nx = nx;
        vertices[14].ny = ny;
        vertices[14].nz = nz;

        vertices[15].x = 1.0;
        vertices[15].y = -1.0;
        vertices[15].z = 1.0;
        vertices[15].nx = nx;
        vertices[15].ny = ny;
        vertices[15].nz = nz;

        // right face
        nx = 0;
        ny = 0;
        nz = -1;


        vertices[16].x = 1.0;
        vertices[16].y = -1.0;
        vertices[16].z = -1.0;
        vertices[16].nx = nx;
        vertices[16].ny = ny;
        vertices[16].nz = nz;

        vertices[17].x = 1.0;
        vertices[17].y = 1.0;
        vertices[17].z = -1.0;
        vertices[17].nx = nx;
        vertices[17].ny = ny;
        vertices[17].nz = nz;

        vertices[18].x = 1.0;
        vertices[18].y = 1.0;
        vertices[18].z = 1.0;
        vertices[18].nx = nx;
        vertices[18].ny = ny;
        vertices[18].nz = nz;

        vertices[19].x = 1.0;
        vertices[19].y = -1.0;
        vertices[19].z = 1.0;
        vertices[19].nx = nx;
        vertices[19].ny = ny;
        vertices[19].nz = nz;




  unsigned short indices[] = {
      0, 1, 2,
      0, 2, 3,
      4, 5, 6,
      4, 6, 7,
      8, 9, 10,
      8, 10, 11,
      12, 13, 14,
      12, 14, 15,
      16, 17, 18,
      16, 18, 19
            
    };

  numIndices = 39;
  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(0));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(12));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(24));
 
  glBindVertexArray(0);

  glGenBuffers(1, &vboiId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  initialized = true;


}

void CubeMesh::draw(const SceneNode& node)
{

  glm::vec3 light_position = glm::vec3(0,5,0);
  glm::vec3 light_color = glm::vec3(0.2,0.7,0.2);
  glm::vec3 ambient_light = glm::vec3(0.2,0.2,0.3);

  if (!initialized)
    {
      cerr << "Cube is not initialized yet" << endl;
      return;
    }

  glUseProgram(shader->getProgramID());

  glm::mat4 mvpMatrix = node.getMVPMatrix();
  glm::mat3 normal_matrix = node.getNormalMatrix();

  glUniformMatrix4fv( MVPMatrixLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
  glUniformMatrix3fv( normal_matrix_loc_, 1, GL_FALSE, &normal_matrix[0][0]);
  glUniform3f( ambient_loc_, ambient_light.x, ambient_light.y, ambient_light.z);
  glUniform3f( light_color_loc_, light_color.x, light_color.y, light_color.z);
  glUniform3f( light_position_loc_, light_position.x, light_position.y, light_position.z);

  glUniform1f( constant_attenuation_loc_, .2);
  glUniform1f( linear_attenuation_loc_, .2);

  glBindAttribLocation(shader->getProgramID(), 0, "VertexPosition");
  glBindAttribLocation(shader->getProgramID(), 1, "VertexNormal");

  glBindVertexArray(vaoId);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboiId);

  glUseProgram(shader->getProgramID());
  
  //std::cout << "draw cube with indices " << numIndices << std::endl;

  //glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

void CubeMesh::setShader(Shader* shader)
{
  Model::setShader(shader);
  MVPMatrixLocation = glGetUniformLocation(shader->getProgramID(), "MVPMatrix");
  normal_matrix_loc_ = glGetUniformLocation(shader->getProgramID(), "NormalMatrix");
  light_position_loc_ = glGetUniformLocation(shader->getProgramID(), "LightPosition");
  eye_direction_loc_ = glGetUniformLocation(shader->getProgramID(), "EyeDirection");
  constant_attenuation_loc_ = glGetUniformLocation(shader->getProgramID(), "ConstantAttenuation");
  linear_attenuation_loc_ = glGetUniformLocation(shader->getProgramID(), "LinearAttenuation");
  quadratic_attenuation_loc_ = glGetUniformLocation(shader->getProgramID(), "QuadraticAttenuation");
  shininess_loc_ = glGetUniformLocation(shader->getProgramID(), "Shininess");
  strength_loc_ = glGetUniformLocation(shader->getProgramID(), "Strength");
  light_color_loc_ = glGetUniformLocation(shader->getProgramID(), "LightColor");
  ambient_loc_ = glGetUniformLocation(shader->getProgramID(), "Ambient");

  cout << "Set cube shader " << shader->getName() 
       << " with pID " << shader->getProgramID() 
       << " mvp_matrix: " << MVPMatrixLocation
       << " normal matrix: " << normal_matrix_loc_
       << ", ambient light: " << ambient_loc_ <<  endl;
  
}

}
