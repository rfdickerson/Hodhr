#version 430 core

uniform sampler2D tex;
uniform sampler2D depthTex;

in vec2 vs_tex_coord;

layout (location = 0) out vec4 color;

void main(void) 
{
    vec4 dcolor = texture(depthTex, vs_tex_coord);
    vec4 rcolor = texture(tex, vs_tex_coord);

    color = rcolor;
//color = vec4(1.0,0.0,0.0,1.0);

}
