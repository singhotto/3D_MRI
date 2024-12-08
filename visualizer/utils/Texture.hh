#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/gl.h>
#include "Shader.hh"
#include "../../utils/Mat3d.hh"

class Texture
{
private:
    Mat3d* matrix;
	float* data;
	int unit;
	int w, h;
public:
	GLuint Id;
	GLenum type;
	~Texture();
	// Assigns a texture unit to a texture
	void reset(Mat3d *mat, int unit, int w, int h, int z);
	void texUnit(Shader& shader, const char* uniform);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();

	void update(int z);
};
#endif