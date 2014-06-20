#ifndef TERRAIN_PATCH_H
#define TERRAIN_PATCH_H

#include <GL/glew.h>

#include "SceneNode.h"
#include "Model.h"

class TerrainPatch : public Model
{

private:
    GLuint vboId, vaoId, vboiId;

public:

    TerrainPatch();

    virtual void init( void );

    virtual void draw(const SceneNode& node );
    
    virtual ~TerrainPatch();


};

#endif
