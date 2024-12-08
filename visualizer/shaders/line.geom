#version 330 core

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 vertexColor[];
in float lineWidth[];
out vec3 geomColor;

uniform mat4 camMatrix;

void main()
{
    vec3 lineDir = normalize(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz);
    vec3 upDir = vec3(0.0, 0.0, 1.0); 
    vec3 rightDir = cross(lineDir, upDir) * lineWidth[0] / 2.0;

    vec4 offset = vec4(rightDir, 0.0);

    geomColor = vertexColor[0];
    gl_Position = (gl_in[0].gl_Position + offset);
    EmitVertex();

    geomColor = vertexColor[0];
    gl_Position = (gl_in[0].gl_Position - offset);
    EmitVertex();

    geomColor = vertexColor[1];
    gl_Position = (gl_in[1].gl_Position + offset);
    EmitVertex();

    geomColor = vertexColor[1];
    gl_Position = (gl_in[1].gl_Position - offset);
    EmitVertex();

    EndPrimitive();
}
