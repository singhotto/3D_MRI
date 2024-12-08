#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTex;
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(position.x, -position.y, position.z, 1.0); // Set the position of the vertex in clip space

    texCoord = aTex;
}
