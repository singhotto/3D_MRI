#version 330 core

out vec4 FragColor;

in vec3 geomColor;

void main()
{
    FragColor = vec4(geomColor, 1.0);
}
