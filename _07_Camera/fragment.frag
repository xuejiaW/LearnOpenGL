#version 330 core

uniform vec4 uniColor;

in vec2 tex;
uniform sampler2D outTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(outTexture, tex);
}