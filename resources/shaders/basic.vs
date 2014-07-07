#version 430 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat3 NormalMatrix;

uniform vec3 LightPosition;
uniform vec3 EyeDirection;
uniform float ConstantAttenuation;
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;

layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 1) in vec2 VertexTexCoord;

out vec4 Color;
out vec3 Normal;
out vec2 TexCoord;

out vec3 LightDirection;
out vec3 HalfVector;
out float Attenuation;

void main() {


    Color = vec4(.5, .85, 0.15, 1);


    Normal = normalize(NormalMatrix * VertexNormal);
    
    LightDirection = LightPosition - vec3(VertexPosition);
    float lightDistance = length(LightDirection);
    
    LightDirection = LightDirection / lightDistance;
    
    Attenuation = 1.0 /
        (ConstantAttenuation +
            LinearAttenuation * lightDistance +
            QuadraticAttenuation * lightDistance * lightDistance);
            
    HalfVector = normalize(LightDirection + EyeDirection);
    
    
    gl_Position = MVPMatrix * VertexPosition;
    
    
    
}
