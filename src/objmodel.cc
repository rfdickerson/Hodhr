// Copyright Robert Dickerson 2014

#include <GL/glew.h>

#include <fstream>
#include <sstream>
//# <iostream>
#include <vector>
#include <map>

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
} FaceDesc;

bool operator<(const FaceDesc& l, const FaceDesc& r) {
    return (l.uvID < r.uvID && l.vertexID < r.vertexID);
}
  
typedef struct
{
  unsigned short u;
  unsigned short v;
} UVCoord;
  
typedef struct
{
      unsigned int fboIndex;     // the index we use in the fbo
      HodhrVertex* hVertex;

} GLVertexIndex;

typedef std::map<FaceDesc, GLVertexIndex>::iterator it_glindex;

  /*
   * Extracts the vertex position index and the texture vertex index
   */
  int parse_desc(std::string token, FaceDesc* face )
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

  int averageNormal(glm::vec3& normal, HodhrVertex& hVertex)
  {

      glm::vec3 currentNormal = glm::vec3(hVertex.nx, hVertex.ny, hVertex.nz);
      currentNormal = currentNormal + normal;
      currentNormal = glm::normalize(currentNormal);
      hVertex.nx = currentNormal.x;
      hVertex.ny = currentNormal.y;
      hVertex.nz = currentNormal.z;

      return 0;
  }

  int addVertex(int i, glm::vec3 normal, unsigned short &indice,
                const FaceDesc faceDesc[4],
                const glm::vec3 v[4],
                const UVCoord tv[4],
                std::map<FaceDesc, GLVertexIndex> &vertexMap,
                std::vector<unsigned short> &h_indices,
                bool normalize
                )
  {

      if ( vertexMap.count(faceDesc[i]))
      {
          // faceDesc[i].fboIndex = indice;
          HodhrVertex* hv = vertexMap[faceDesc[i]].hVertex;
          if (normalize) {
            averageNormal(normal, *hv );
          }
          h_indices.push_back(vertexMap[faceDesc[i]].fboIndex);
      } else
      {
          HodhrVertex *hv = new HodhrVertex();
          hv->x = v[i].x;
          hv->y = v[i].y;
          hv->z = v[i].z;
          hv->s = tv[i].u;
          hv->t = tv[i].v;

          if (normalize) {
            averageNormal(normal, *hv );
          }

          GLVertexIndex sVi;
          sVi.hVertex = hv;
          sVi.fboIndex = indice;

          vertexMap[faceDesc[i]] = sVi;
          h_indices.push_back(indice);
          indice++;
          //indice++;
      }

       return 0;
  }
  
  int parseFace(
		std::vector<std::string> &tokens,
        std::vector<glm::vec3> &vertices,     // OBJ position vertices
        std::vector<UVCoord> &textureVerts,  // OBJ texture vertices
        std::map<FaceDesc, GLVertexIndex> &vertexMap,    // maps face descriptor with OpenGL vertex
        std::vector<unsigned short> &h_indices,         // list of OpenGL indices
        unsigned short &indice)
  {


    FaceDesc faceDesc[4];  // FACE tuple of vertex index and texture index
    glm::vec3 v[4];         // FACE obj vertices
    UVCoord tv[4];         // OBJ holds a tuple for the u and v coord
    // Hodhr::HodhrVertex hv[4];
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

    // calculate the normal from the cross product
    a = v[1]-v[0];
    b = v[2]-v[0];

    normal = glm::cross(b, a);
    // normal = glm::normalize(normal);


    addVertex(0, normal, indice, faceDesc, v, tv, vertexMap, h_indices, true);
    addVertex(1, normal, indice, faceDesc, v, tv, vertexMap, h_indices, true);
    addVertex(2, normal, indice, faceDesc, v, tv, vertexMap, h_indices, true);


    addVertex(0, normal, indice, faceDesc, v, tv, vertexMap, h_indices, false);
    addVertex(3, normal, indice, faceDesc, v, tv, vertexMap, h_indices, true);
    addVertex(2, normal, indice, faceDesc, v, tv, vertexMap, h_indices, false);


    /*
    addVertex(1, &indice, &vertexMap);
    addVertex(2, &indice, &vertexMap);
    addVertex(1, &indice, &vertexMap);
    addVertex(2, &indice, &vertexMap);
    addVertex(0, &indice, &vertexMap);
    */


    /*
    for (int i=0 ; i<4 ; i++)
    {
       hv[i].x = v[i].x;
       hv[i].y = v[i].y;
       hv[i].z = v[i].z;
       hv[i].s = tv[i].u;
       hv[i].t = tv[i].v;
    }
    */




    
    /*
    for (int i=0 ; i<4 ; ++i) {
      
      hv[i].nx = normal.x;
      hv[i].ny = normal.y;
      hv[i].nz = normal.z;

    }
    */

    /**
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
    **/

    return 0;
  }

  void 
  ObjModel::LoadFile(std::string filename)
  {

    fprintf(stderr, "Loading model from %s\n", filename.c_str());

    std::ifstream infile(filename);

    // std::vector<HodhrVertex> h_vertices;

    // store the texture coordinates
    std::vector<UVCoord> textureVerts;

    std::vector<HodhrVertex> h_vertices;
    std::vector<unsigned short> h_indices;
    std::vector<glm::vec3> vertices;
    std::map<FaceDesc, GLVertexIndex> vertexMap;
    
    std::string line;
  // float a, b, c;

    unsigned short indice = 0;
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
	    unsigned short u = (short)((fu) * USHRT_MAX);
	    unsigned short v = (short)((1-fv) * USHRT_MAX);
	    
        UVCoord uv;
	    uv.u = u;
	    uv.v = v;

         // fprintf(stdout, "Reading texture coordinate %d, %d\n", u, v);
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

          parseFace(tokens, vertices, textureVerts, vertexMap, h_indices, indice);



        }
      else {
          // std::cout << line[0] << std::endl;
        }

    }


    std::map<unsigned int, HodhrVertex*> tempVertex;

    for (it_glindex iterator = vertexMap.begin(); iterator != vertexMap.end(); iterator++)
    {
        tempVertex[iterator->second.fboIndex] = iterator->second.hVertex;
    }


    for (int i=0;i<indice;i++)
    {
        h_vertices.push_back(*tempVertex[i]);
    }


  fprintf(stderr, "Model loaded with %d vertices and %d indices\n",
          (int)h_vertices.size(), (int)h_indices.size());

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
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(HodhrVertex), 
		 &vertices[0], GL_STATIC_DRAW );

    printOglError("Creating VBO for Obj Model");

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(HodhrVertex), BUFFER_OFFSET(0));

       // normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(HodhrVertex), BUFFER_OFFSET(16));

    // texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_UNSIGNED_SHORT, GL_TRUE, 
			  sizeof(HodhrVertex), BUFFER_OFFSET(24));

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    glGenBuffers(1, &vboi_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned short), 
		 &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    num_indices_ = indices.size();

    mMaterialInfo.ka = glm::vec3(1.0, 1.0, 1.0);
    mMaterialInfo.kd = glm::vec3(1.0, 1.0, 1.0);
    mMaterialInfo.ks = glm::vec3(1.0, 1.0, 1.0);
    
    mMaterialInfo.shininess = 0.5f;
    
    mLightInfo.position = glm::vec4(10.0, 5.0, 0.0, 1.0);
    mLightInfo.la = glm::vec3(1.0, 1.0, 1.0);
    mLightInfo.ld = glm::vec3(1.0, 1.0, 1.0);
    mLightInfo.ls = glm::vec3(1.0, 1.0, 1.0);

    initialized = true;

    shader->getActiveUniforms();

  }

  void ObjModel::init()
  {
    

  }

  void ObjModel::draw(const SceneNode &node)
  {
        
    if (!initialized)
      {
	fprintf(stderr, "OBJ model has not been initialized yet!");
        return;
      }
    
    glUseProgram(shader->getProgramID());

    glm::mat4 mvpMatrix = node.getMVPMatrix();
    glm::mat3 normal_matrix = node.getNormalMatrix();
    
    glUniformMatrix4fv( mMVPLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
    glUniformMatrix3fv( mNormalMatrixLocation, 1, GL_FALSE, &normal_matrix[0][0]);
    glUniformMatrix4fv (mModelViewMatrixLocation, 1, GL_FALSE, 
			&node.getModelViewMatrix()[0][0]);
    
    glUniform4fv( mLightPositionLocation, 4, &mLightInfo.position[0]);
    glUniform4fv( mLightLaLocation, 3, &mLightInfo.la[0]);
    glUniform4fv( mLightLdLocation, 3, &mLightInfo.ld[0]);
    glUniform4fv( mLightLsLocation, 3, &mLightInfo.ls[0]);
    

    glUniform4fv( mMaterialKaLocation, 3, &mMaterialInfo.ka[0]);
    glUniform4fv( mMaterialKdLocation, 3, &mMaterialInfo.kd[0]);
    glUniform4fv( mMaterialKsLocation, 3, &mMaterialInfo.ks[0]);
    glUniform1f( mMaterialShininessLocation, mMaterialInfo.shininess); 
    
    // glUniform3f( ambient_loc_, ambient_light.x, ambient_light.y, ambient_light.z);
    // glUniform3f( light_color_loc_, light_color.x, light_color.y, light_color.z);
    // glUniform3f( light_position_loc_, light_position.x, light_position.y, light_position.z);
    
    // glUniform1f( constant_attenuation_loc_, .2f);
    // glUniform1f( linear_attenuation_loc_, .2f);
    
    glBindAttribLocation(shader->getProgramID(), 0, "VertexPosition");
    glBindAttribLocation(shader->getProgramID(), 1, "VertexNormal");
    
    glBindVertexArray(vao_id_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi_id_);
    
    // glUseProgram(shader->getProgramID());
    
    if (this->mTexture)
      {
	// fprintf(stderr, "Texture id on model is %d\n", mTexture->getTextureID());
	// glEnable(GL_TEXTURE_2D);
	
	glUniform1i(mTextureLocation, 0);
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, mTexture->getTextureID());
      }
    
    //std::cout << "draw cube with indices " << numIndices << std::endl;
    
    // glDrawElements(GL_LINES, num_indices_, GL_UNSIGNED_SHORT, NULL);
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
    
    /*
    mTextureLocation = glGetUniformLocation(shader->getProgramID(), "tex");
    MVPMatrixLocation = glGetUniformLocation(shader->getProgramID(), "MVP");
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

	*/

    mMVPLocation = glGetUniformLocation(shader->getProgramID(), "MVP");
    mNormalMatrixLocation = glGetUniformLocation(shader->getProgramID(), "NormalMatrix");
    
    mLightPositionLocation = glGetUniformLocation(shader->getProgramID(), "Light.Position");
    mLightLaLocation = glGetUniformLocation(shader->getProgramID(), "Light.La");
    mLightLdLocation = glGetUniformLocation(shader->getProgramID(), "Light.Ld");
    mLightLsLocation = glGetUniformLocation(shader->getProgramID(), "Light.Ls");

    mMaterialKaLocation = glGetUniformLocation(shader->getProgramID(), "Material.Ka");
    mMaterialKdLocation = glGetUniformLocation(shader->getProgramID(), "Material.Kd");
    mMaterialKsLocation = glGetUniformLocation(shader->getProgramID(), "Material.Ks");
    mMaterialShininessLocation = glGetUniformLocation(shader->getProgramID(), "Material.Shininess");

    mModelViewMatrixLocation = glGetUniformLocation(shader->getProgramID(), "ModelViewMatrix");
    mProjectionMatrixLocation = glGetUniformLocation(shader->getProgramID(), "ProjectionMatrix");
    
    // output the locations of the uniforms
    fprintf(stdout, "Searching for uniforms in shader\n");
    fprintf(stdout, "MVP: %d, NormalMatrix: %d, ProjectionMatrix: %d, ModelView: %d\n", 
	    mMVPLocation, mNormalMatrixLocation, 
	    mProjectionMatrixLocation, mModelViewMatrixLocation);
    fprintf(stdout, "Light Position: %d, Ambient: %d, Diffuse: %d, Specular: %d\n", 
	    mLightPositionLocation, 
	    mLightLaLocation, mLightLdLocation, mLightLsLocation);

    

  }

  void ObjModel::setTexture(Texture* texture) {
      mTexture = texture;
  }

  
} // namespace
