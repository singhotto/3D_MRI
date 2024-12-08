#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/gl.h>
#include"VBO.hh"
#include<iostream>

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();
	~VAO();

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, int gap, int offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
};

#endif