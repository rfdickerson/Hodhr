#ifndef TERRAIN_PATCH_H
#define TERRAIN_PATCH_H

#include <memory>

#include <GL/glew.h>

#include "common.h"
#include "scenenode.h"
#include "model.h"

namespace Hodhr {

class Texture;

class TerrainPatch : public Model
{

private:
    GLuint vboId, vao_id_, vboiId;

    unsigned short subdivisions;
    
    unsigned short numIndices;
    
    GLint MVPMatrixLocation,
      MVMatrixLocation,
      normal_matrix_loc_,
      light_position_loc_,
      eye_direction_loc_,
      constant_attenuation_loc_,
      linear_attenuation_loc_,
      quadratic_attenuation_loc_,
      shininess_loc_,
      strength_loc_,
      light_color_loc_,
      ambient_loc_
      ;

    bool initialized;

    Texture* texture_;


public:

    TerrainPatch();

    TerrainPatch(const TerrainPatch&) = delete;
    TerrainPatch& operator=(const TerrainPatch&) = delete;

    virtual ~TerrainPatch();

    virtual void init( void );

    virtual void draw(const SceneNode& node );

    virtual void setShader(Shader* shader);

    void setTexture(Texture* texture);

};

}

#endif
