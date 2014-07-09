#version 430 core

uniform sampler2D tex;
uniform sampler2D depthTex;
uniform mat4 projectionMatrix;

in vec2 texCoord0;

const float LOG2 = 1.442695;
const float density = 0.04;
const float zNear = 0.1;
const float zFar = 100.0;

uniform vec2 inverseFilterTextureSize = vec2(1.0/1280.0,1.0/768.0);
uniform float FXAA_SPAN_MAX = 8.0;
uniform float FXAA_REDUCE_MIN = (1.0/128.0);
uniform float FXAA_REDUCE_MUL = 1.0/8.0;

layout (location = 0) out vec4 color;


void main(void) {

    // fog
    vec4 dcolor = texture2D(depthTex, texCoord0);
    vec4 rcolor = texture2D(tex, texCoord0);

    vec4 fogcolor = vec4(195.0/255.0, 228.0/255.0, 243.0/255.0, 0.01);

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

    // FXAA
    //vec2 texCoordOffset = inverseFilterTextureSize.xy;
    vec2 texCoordOffset = inverseFilterTextureSize;

    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaTL = dot(luma, texture2D(tex, texCoord0.xy + (vec2(-1.0, -1.0) * texCoordOffset)).xyz );
    float lumaTR = dot(luma, texture2D(tex, texCoord0.xy + (vec2(1.0, -1.0) * texCoordOffset)).xyz );
    float lumaBL = dot(luma, texture2D(tex, texCoord0.xy + (vec2(-1.0, 1.0) * texCoordOffset)).xyz );
    float lumaBR = dot(luma, texture2D(tex, texCoord0.xy + (vec2(1.0, 1.0) * texCoordOffset)).xyz );
    float lumaM = dot(luma, texture2D(tex, texCoord0.xy).xyz);
    
    vec2 dir;
    dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
    dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));
    
    float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (FXAA_REDUCE_MUL * 0.25), FXAA_REDUCE_MIN);
    float inverseDirAdjustment = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);

    dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX),
        max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
        dir * inverseDirAdjustment)) * texCoordOffset;


    vec3 result1 = (1.0/2.0) * (
            texture2D(tex, texCoord0.xy + (dir * vec2(1.0/3.0 - 0.5))).xyz +
            texture2D(tex, texCoord0.xy + (dir * vec2(3.0/3.0 - 0.5))).xyz);

    vec3 result2 = result1 * (1.0/2.0) + (1.0/4.0) * (
            texture2D(tex, texCoord0.xy + (dir * vec2(0.0/3.0 - 0.5))).xyz +
            texture2D(tex, texCoord0.xy + (dir * vec2(3.0/3.0 - 0.5))).xyz);

    float lumaMin = min(lumaM, min(min(lumaTL, lumaTR), min(lumaBL, lumaBR)));
    float lumaMax = max(lumaM, max(max(lumaTL, lumaTR), max(lumaBL, lumaBR)));
    float lumaResult2 = dot(luma, result2);

    if (lumaResult2 < lumaMin || lumaResult2 > lumaMax)
        color = vec4(result1, 1.0);
    else
        color = vec4(result2, 1.0);

    color = mix(fogcolor, color, fogFactor);
    //color = rcolor;
}
