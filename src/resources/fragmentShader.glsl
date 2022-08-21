#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float LightValue;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord) * LightValue;
    if (FragColor.a == 0) {
        discard;
    }
}