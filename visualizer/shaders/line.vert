#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aRGB;
layout (location = 2) in float width;
out vec3 vertexColor;
out float lineWidth;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(position.x, -position.y, position.z, 1.0); 

    vertexColor = aRGB;
    lineWidth = width;
}
