#include"VAO.hh"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, int gap, int offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, gap * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
VAO::~VAO()
{
	glDeleteVertexArrays(1, &ID);
}