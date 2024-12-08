#ifndef SHADER_HH
#define SHADER_HH

#include <glad/gl.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <filesystem>
#include <vector>

std::string getFileContent(const std::string& fileName);
GLuint createShader(const std::string& shaderFile, unsigned int shaderType);

class Shader{
private:
    const std::string shaderDirPath = std::filesystem::path(__FILE__).parent_path().parent_path().string()+"/shaders/";
public:
    GLuint Id;
    Shader();
    Shader(const Shader& other);
    Shader(Shader&& other) noexcept;
    Shader(const char* vertexFileName = nullptr, const char* fragmentFileName = nullptr, const char* geometryFileName = nullptr);

    void activate();
    void Delete();
};

#endif