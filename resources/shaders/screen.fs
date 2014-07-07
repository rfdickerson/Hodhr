#version 430 core

uniform sampler2D tex;
uniform sampler2D depthTex;
uniform mat4 projectionMatrix;

in vec2 vs_tex_coord;
const float LOG2 = 1.442695;
const float density = 0.04;
const float zNear = 0.1;
const float zFar = 100.0;

layout (location = 0) out vec4 color;

void main(void) {

vec4 dcolor = texture(depthTex, vs_tex_coord);
vec4 rcolor = texture(tex, vs_tex_coord);

vec4 fogcolor = vec4(195/255, 228/255, 233/255, 0.0);

float z_b = dcolor.x;
float z_n = 2.0 * z_b - 1.0;
float z_e = 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));
float z = z_e;

float fogFactor = exp2( -density *
density *
z *
z *
LOG2 );

fogFactor = clamp(fogFactor, 0.0, 1.0);

color = mix(fogcolor, rcolor, fogFactor);
//color = rcolor;
}
