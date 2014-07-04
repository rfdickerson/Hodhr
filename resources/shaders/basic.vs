#version 430 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat3 NormalMatrix;

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec2 in_tex_coord;

out vec4 color;
out vec2 vs_tex_coord;

void main() {
    gl_Position = MVPMatrix * in_Position;
    //gl_Position = in_Position;
    color = vec4(.5, .85, 0.15, 1);
    
}
