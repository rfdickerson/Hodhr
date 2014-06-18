#version 430 core

in vec4 color;

layout(location = 0) out vec4 vcolor;

void main() {
    
    vcolor = color;

}
