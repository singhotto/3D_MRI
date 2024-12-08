#include "VBO.hh"

#include <glad/gl.h>

VBO::VBO(){
    creator(0, nullptr, GL_DYNAMIC_DRAW);
}

VBO::VBO(int size)
{
    creator(size, nullptr, GL_DYNAMIC_DRAW);
}

VBO::VBO(float* vertices, int size){
    creator(size, vertices, GL_STATIC_DRAW);
}

void VBO::creator(int size, float* pointer, GLenum type){
    this->size = size;
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ARRAY_BUFFER, Id);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), pointer, type);
}

void VBO::reset(int size){
    this->Delete();

    creator(size, nullptr, GL_DYNAMIC_DRAW);
}

void VBO::reset(int size, float* pointer, GLenum type){
    this->Delete();

    creator(size, pointer, type);
}

void VBO::update(int size, float* data){
    this->Bind();
    this->size = size;
    glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), data);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &Id);
}

int VBO::getSize()
{
    return this->size;
}
