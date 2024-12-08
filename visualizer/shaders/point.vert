#version 330 core

layout (location = 0) in vec3 position; 
layout (location = 1) in float pixelColor;
layout (location = 2) in vec3 pointColor;

out vec3 vertexColor;

uniform mat4 camMatrix;
uniform bool isPoint;
uniform bool diffrentColor;
uniform vec3 shapeColor;

void main()
{
    gl_Position = camMatrix * vec4(position.x, -position.y, position.z, 1.0); 

    if (isPoint) {
        vertexColor = shapeColor;
    }else if (diffrentColor){
        vertexColor = pointColor;
    }else{
        vertexColor = shapeColor * pixelColor;
    }
}
