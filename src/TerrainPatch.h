#ifndef TERRAIN_PATCH_H
#define TERRAIN_PATCH_H

#include <GL/glew.h>

class TerrainPatch 
{

private:
    GLuint vboId, vaoId, vboiId;

public:

    TerrainPatch();

    void init( void );

    void draw( void );
    
    ~TerrainPatch();


};

#endif
