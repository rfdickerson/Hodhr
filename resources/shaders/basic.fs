#version 430 core

in vec4 color;
in vec4 normal;

layout(location = 0) out vec4 vcolor;

void main() {
    
    vcolor = normal;

}
