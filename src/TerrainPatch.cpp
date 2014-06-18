#include <GL/glew.h>

#include "TerrainPatch.h"

/**
 * Terrain Patch is a section of terrain that can be swapped in and out of memory
 **/

void TerrainPatch::init () 
{
    float vertices[] = {
        0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //vaoId = glGenVertexArrays();
}

