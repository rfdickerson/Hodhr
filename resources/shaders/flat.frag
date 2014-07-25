#version 430 core

uniform sampler2D tex;
uniform float Opacity;

in vec2 TextureCoord;

layout(location = 0) out vec4 FragColor;

void main(void) {

  // vec4 simplecolor = vec4(.5, .55, 0.45, Opacity);
  vec4 texColor = texture2D(tex, TextureCoord);
  vec4 simplecolor = vec4(1, 1, 1, 0);
    
  //FragColor = vec4(texColor.r,texColor.g, texColor.b, Opacity);
  // FragColor = texColor;
  FragColor = mix( simplecolor, texColor, Opacity);
}
