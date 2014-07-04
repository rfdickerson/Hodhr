#ifndef TERRAIN_PATCH_H
#define TERRAIN_PATCH_H

#include <memory>

#include <GL/glew.h>

#include "SceneNode.h"
#include "Model.h"

class TerrainPatch : public Model
{

private:
    GLuint vboId, vaoId, vboiId;

    unsigned short subdivisions;
    
    unsigned short numIndices;
    
    GLint MVPMatrixLocation, MVMatrixLocation;

    // bool initialized;


public:

    TerrainPatch();

    TerrainPatch(const TerrainPatch&) = delete;
    TerrainPatch& operator=(const TerrainPatch&) = delete;

    virtual ~TerrainPatch();

    virtual void init( void );

    virtual void draw(const SceneNode& node );

    virtual void setShader(Shader* shader);

};

#endif
