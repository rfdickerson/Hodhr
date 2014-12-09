// Copyright Robert Dickerson 2014



#include <GL/glew.h>

#include <fstream>
#include <sstream>
//# <iostream>
#include <vector>

#include "objmodel.h"
#include "shader.h"

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

  fprintf(stderr, "Destroying OBJ model\n");
  //std::cout << "Destroying obj model" << std::endl;

}


typedef struct
{
    unsigned int vertexID;
    unsigned int uvID;

} FACE_DESC;

typedef struct
{
    unsigned short u;
    unsigned short v;
} UV_COORD;

/*
 * Extracts the vertex position index and the texture vertex index
 */
int parse_desc(std::string token, FACE_DESC* face )
{
    int i = token.find('/');
    std::string l1 = token.substr(0, i);
    std::string l2 = token.substr(i+1, token.size());
    unsigned a = ::atoi(l1.c_str());
    unsigned b = ::atoi(l2.c_str());

    face->vertexID = a;
    face->uvID = b;

    return 0;
}

int parseFace(
        std::vector<std::string> &tokens,
        std::vector<glm::vec3> &vertices,
        std::vector<UV_COORD> &textureVerts,
        std::vector<HodhrVertex> &h_vertices,
                std::vector<unsigned short> &h_indices,
               int &indice)
{
    FACE_DESC faceDesc[4];
    glm::vec3 v[4];
    UV_COORD tv[4];
    Hodhr::HodhrVertex hv[4];
    glm::vec3 a, b, normal;

    for (int i=0;i<4;i++) {
        parse_desc(tokens[i+1], &faceDesc[i]);
    }

    for (int i=0;i<4;i++) {
        v[i] = vertices[faceDesc[i].vertexID-1];
    }


    for (int i=0;i<4;i++)
    {
       tv[i] = textureVerts[faceDesc[i].uvID-1];
    }

    for (int i=0 ; i<4 ; i++)
    {
       hv[i].x = v[i].x;
       hv[i].y = v[i].y;
       hv[i].z = v[i].z;
       hv[i].s = tv[i].u;
       hv[i].t = tv[i].v;
    }


    a = v[1]-v[0];
    b = v[2]-v[0];

    normal = glm::cross(b, a);

    for (int i=0;i<4;i++) {
      hv[i].nx = normal.x;
      hv[i].ny = normal.y;
      hv[i].nz = normal.z;
    }

    h_vertices.push_back(hv[0]);
    h_indices.push_back(indice);
    indice++;

    h_vertices.push_back(hv[1]);
    h_indices.push_back(indice);
    indice++;

    h_vertices.push_back(hv[2]);
    h_indices.push_back(indice);
    indice++;

    h_vertices.push_back(hv[3]);

    h_indices.push_back(indice-1);
    h_indices.push_back(indice-3);
    h_indices.push_back(indice);
    indice++;

    return 0;
}

  void 
  ObjModel::LoadFile(std::string filename)
  {

    fprintf(stderr, "Loading model from %s\n", filename.c_str());

    std::ifstream infile(filename);

    std::vector<HodhrVertex> h_vertices;

    // store the texture coordinates
    std::vector<UV_COORD> textureVerts;

    std::vector<unsigned short> h_indices;
    std::vector<glm::vec3> vertices;

  std::string line;
  // float a, b, c;

  int indice = 0;
  while (std::getline(infile, line))
    {
       std::vector<std::string> tokens = split(line, ' ' );

      if (line[0] == '#')
        // comment
        continue;
      else if (line[0] == 'o')
      {
        fprintf(stdout, "Loading model %s\n", tokens[1].c_str());
      }
      else if (line[0] == 'v' && line[1] == 't')
      {

        float fu = ::atof(tokens[1].c_str());
        float fv = ::atof(tokens[2].c_str());
        unsigned short u = (short)((fu) * 65535);
        unsigned short v = (short)((fv) * 65535);

        UV_COORD uv;
        uv.u = u;
        uv.v = v;

         fprintf(stdout, "Reading texture coordinate %d, %d\n", u, v);
         textureVerts.push_back( uv );
      }
      else if (line[0] == 'v')
        {


        float x = ::atof(tokens[1].c_str());
        float y = ::atof(tokens[2].c_str());
        float z = ::atof(tokens[3].c_str());

        vertices.push_back(glm::vec3(x,y,z));

        // std::cout << x << "," << y << "," << z << std::endl;

        }
      else if (line[0] == 'f')
        {

          parseFace(tokens, vertices, textureVerts, h_vertices, h_indices, indice);



        }
      else {
          // std::cout << line[0] << std::endl;
        }

    }

  fprintf(stderr, "Model loaded with %d vertices and %d indices\n",
          h_vertices.size(), h_indices.size());

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(HodhrVertex), BUFFER_OFFSET(0));

       // normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(HodhrVertex), BUFFER_OFFSET(16));

    // texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(HodhrVertex), BUFFER_OFFSET(24));

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
//	std::cerr << "Obj has not been initialized yet!" << vbo_id_ << " " << vao_id_ << std::endl;
  fprintf(stderr, "OBJ model has not been initialized yet!");
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

  glUniform1f( constant_attenuation_loc_, .2f);
  glUniform1f( linear_attenuation_loc_, .2f);

  glBindAttribLocation(shader->getProgramID(), 0, "VertexPosition");
  glBindAttribLocation(shader->getProgramID(), 1, "VertexNormal");

  glBindVertexArray(vao_id_);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);

  glUseProgram(shader->getProgramID());

  if (this->mTexture)
  {
      // fprintf(stderr, "Texture id on model is %d\n", mTexture->getTextureID());
      glEnable(GL_TEXTURE_2D);

      glUniform1i(mTextureLocation, 0);

      glActiveTexture(GL_TEXTURE0 + 0);
      glBindTexture(GL_TEXTURE_2D, mTexture->getTextureID());
  }

  //std::cout << "draw cube with indices " << numIndices << std::endl;

  //glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_SHORT, NULL);
  glDrawElements(GL_TRIANGLES, num_indices_, GL_UNSIGNED_SHORT, NULL);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

  void 
  ObjModel::setShader(
		      Shader* shader
		      )
  {
    Model::setShader(shader);

    mTextureLocation = glGetUniformLocation(shader->getProgramID(), "tex");
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

    fprintf(stdout, "Location of texture is at %d\n", mTextureLocation);

    /*
    std::cout << "Set cube shader " << shader->getName()
	      << " with pID " << shader->getProgramID()
	      << " mvp_matrix: " << MVPMatrixLocation
	      << " normal matrix: " << normal_matrix_loc_
	      << ", ambient light: " << ambient_loc_ <<  std::endl;
    */

  }

  void ObjModel::setTexture(Texture* texture) {
      mTexture = texture;
  }

  
} // namespace
