#version 430 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec3 in_normals;
layout (location = 2) in vec2 in_tex_coord;

out vec2 TextureCoord;


void main(void) {
    
    gl_Position = in_position;
    TextureCoord = in_tex_coord;
}
