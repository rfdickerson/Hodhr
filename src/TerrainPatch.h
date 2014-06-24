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


public:

    TerrainPatch();


    virtual ~TerrainPatch();

    virtual void init( void );

    virtual void draw(const SceneNode& node );


};

#endif
