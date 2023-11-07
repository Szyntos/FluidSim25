#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform float colorOffr;
uniform float colorOffg;
uniform float colorOffb;

void main()
{
    FragColor = vec4(ourColor.r + colorOffr, ourColor.g + colorOffg,
    ourColor.b + colorOffb, 1.0);
}