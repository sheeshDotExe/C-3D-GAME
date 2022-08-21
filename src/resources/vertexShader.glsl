#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aLightValue;

out vec2 TexCoord;
out float LightValue;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);//vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    LightValue = aLightValue / 5.0f;
}