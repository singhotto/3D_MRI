#ifndef VBO__HH
#define VBO__HH

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texUV;
};


class VBO{
    private:
        void creator(int size, float* pointer, GLenum type);
        int size;
    public:
        GLuint Id;
        VBO();
        VBO(int size);
        VBO(float* vertices, int size);

        void reset(int size);
        void reset(int size, float* pointer, GLenum type);
        void update(int size, float* data);
        void Bind();
        void Unbind();
        void Delete();
        int getSize();
};

#endif