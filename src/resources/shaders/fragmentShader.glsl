#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float LightValue;

uniform sampler2D texture1;
uniform bool showLight;

void main()
{
    if (showLight){
        FragColor = texture(texture1, TexCoord) * LightValue;
    } else {
        FragColor = texture(texture1, TexCoord);
    }
    
    if (FragColor.a == 0) {
        discard;
    }
}