#ifndef EBO__HH
#define EBO__HH

#include <glad/gl.h>
#include <vector>

class EBO{
    private:
    public:
        GLuint Id;
        EBO();
        void reset(std::vector<GLuint>& indices);

        void Bind();
        void Unbind();
        void Delete();
};

#endif