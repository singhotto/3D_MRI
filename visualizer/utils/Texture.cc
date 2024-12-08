#include "Texture.hh"
#include <cstring>

Texture::~Texture()
{
    delete[] data;
}

void Texture::reset(Mat3d *mat, int unit, int w, int h, int z)
{
    this->matrix = mat;
    int size = w * h;
    this->w = w;
    this->h = h;
    this->data = new float[size]; 
    // Assigns the type of the texture ot the texture object
    type = GL_TEXTURE_2D;
    this->unit = unit;
    glActiveTexture(GL_TEXTURE0 + unit);
    // Flip the image vertically to match OpenGL's coordinate system

    // Generate OpenGL texture object
    glGenTextures(1, &Id);
    
    glBindTexture(GL_TEXTURE_2D, Id);

    // Configure texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // for (int i = h-1; i >= 0; i--)
    for (int i = 0; i < h*w; i++)
    {
        data[i] = mat->at(i);
        // data[i] = 1.0f;
    }
    // Assign the image data to the OpenGL Texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_FLOAT, data);
    // Generate MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void Texture::update(int z)
{
    int offset = z * h * w;
    for (int i = 0 * z * h * w; i < (h * w); i++)
    {
        data[i] = matrix->at(offset+i);
    }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RED, GL_FLOAT, data);
}

void Texture::texUnit(Shader &shader, const char *uniform)
{
    // Shader needs to be activated before changing the value of a uniform
    shader.activate();
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.Id, uniform);
    // Sets the value of the uniform
    glUniform1i(texUni, this->unit);
}

void Texture::Bind()
{
    glBindTexture(type, Id);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &Id);
}