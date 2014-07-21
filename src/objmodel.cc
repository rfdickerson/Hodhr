// Copyright Robert Dickerson 2014



#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "include/objmodel.h"
#include "include/shader.h"

namespace Hodhr {

  std::vector<std::string>& 
  split(
	const std::string &s, 
	char delim, 
	std::vector<std::string> &elems
	) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }


  std::vector<std::string> split(const std::string &s, char delim) {
      std::vector<std::string> elems;
      split(s, delim, elems);
      return elems;
  }

ObjModel::ObjModel () {
  vbo_id_ = 0;
  vao_id_ = 0;
  vboi_id_ = 0;
}

ObjModel::~ObjModel ()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vbo_id_);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &vboi_id_);

  glBindVertexArray(0);
  //glDeleteVertexArrays(1, &vaoId);


  std::cout << "Destroying obj model" << std::endl;

}



  void 
  ObjModel::LoadFile(std::string filename)
  {

    std::cout << "Loading model from " << filename << std::endl;

    std::ifstream infile(filename);

    std::vector<Hodhr::HodhrVertex> h_vertices;
    std::vector<unsigned short> h_indices;
    std::vector<glm::vec3> vertices;

  std::string line;
  float a, b, c;

  int indice = 0;
  while (std::getline(infile, line))
    {
       std::vector<std::string> tokens = split(line, ' ' );

      if (line[0] == '#')
        // comment
        continue;
      else if (line[0] == 'v')
        {


        float x = ::atof(tokens[1].c_str());
        float y = ::atof(tokens[2].c_str());
        float z = ::atof(tokens[3].c_str());

        vertices.push_back(glm::vec3(x,y,z));

        //std::cout << x << "," << y << "," << z << std::endl;

        }
      else if (line[0] == 'f')
        {
          unsigned short i1 = ::atoi(tokens[1].c_str());
          unsigned short i2 = ::atoi(tokens[2].c_str());
          unsigned short i3 = ::atoi(tokens[3].c_str());
          unsigned short i4 = ::atoi(tokens[4].c_str());

          std::cout << i1 << "," << i2 << "," << i3 << "," << i4 << std::endl;


          glm::vec3 v1 = vertices[i1-1];
          glm::vec3 v2 = vertices[i2-1];
          glm::vec3 v3 = vertices[i3-1];
          glm::vec3 v4 = vertices[i4-1];

          Hodhr::HodhrVertex hv1;
          hv1.x = v1.x;
          hv1.y = v1.y;
          hv1.z = v1.z;

          Hodhr::HodhrVertex hv2;
          hv2.x = v2.x;
          hv2.y = v2.y;
          hv2.z = v2.z;

          Hodhr::HodhrVertex hv3;
          hv3.x = v3.x;
          hv3.y = v3.y;
          hv3.z = v3.z;

          Hodhr::HodhrVertex hv4;
          hv4.x = v4.x;
          hv4.y = v4.y;
          hv4.z = v4.z;

          glm::vec3 a = v2-v1;
          glm::vec3 b = v3-v1;

          glm::vec3 normal = glm::cross(b, a);
          hv1.nx = normal.x;
          hv1.ny = normal.y;
          hv1.nz = normal.z;
          hv2.nx = normal.x;
          hv2.ny = normal.y;
          hv2.nz = normal.z;
          hv3.nx = normal.x;
          hv3.ny = normal.y;
          hv3.nz = normal.z;
          hv4.nx = normal.x;
          hv4.ny = normal.y;
          hv4.nz = normal.z;

          h_vertices.push_back(hv1);
          h_indices.push_back(indice);
          indice++;

          h_vertices.push_back(hv2);
          h_indices.push_back(indice);
          indice++;

          h_vertices.push_back(hv3);
          h_indices.push_back(indice);
          indice++;

          h_vertices.push_back(hv4);
          //h_indices.push_back(indice);
          //indice++;

          h_indices.push_back(indice-1);
          h_indices.push_back(indice-3);
          h_indices.push_back(indice);
	  indice++;


        }
      else {
          //std::cout << line[0] << std::endl;
        }

    }

  std::cout << "Read " 
	    << h_vertices.size() 
	    << " vertices and " 
	    << h_indices.size() 
	    << " indices."<< std::endl;

  initData(h_vertices, h_indices);


}

  void 
  ObjModel::initData(
		     const std::vector<HodhrVertex>& vertices, 
		     const std::vector<unsigned short>& indices)
  {
  
    glGenVertexArrays(1, &vao_id_);
    glBindVertexArray(vao_id_);

    glGenBuffers(1, &vbo_id_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(HodhrVertex), &vertices[0], GL_STATIC_DRAW );

    printOglError("Creating VBO for Obj Model");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(12));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(HodhrVertex), BUFFER_OFFSET(24));

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    glGenBuffers(1, &vboi_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    num_indices_ = indices.size();

    initialized = true;

  }

  void ObjModel::init()
  {
    

  }

  void ObjModel::draw(const SceneNode &node)
  {
    glm::vec3 light_position = glm::vec3(-5, 5,5);
    glm::vec3 light_color = glm::vec3(249.0/256.0,240.0/256.0,182.0/256.0);
    glm::vec3 ambient_light = glm::vec3(0.2,0.2,0.3);

    if (!initialized)
      {
	std::cerr << "Obj has not been initialized yet!" << vbo_id_ << " " << vao_id_ << std::endl;
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

  glBindVertexArray(vao_id_);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);

  glUseProgram(shader->getProgramID());

  //std::cout << "draw cube with indices " << numIndices << std::endl;

  //glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_SHORT, NULL);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

  void 
  ObjModel::setShader(
		      Shader* shader
		      )
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

    std::cout << "Set cube shader " << shader->getName()
	      << " with pID " << shader->getProgramID()
	      << " mvp_matrix: " << MVPMatrixLocation
	      << " normal matrix: " << normal_matrix_loc_
	      << ", ambient light: " << ambient_loc_ <<  std::endl;

  }

  
} // namespace
