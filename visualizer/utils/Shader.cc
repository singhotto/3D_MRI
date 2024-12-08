#include "Shader.hh"
#include <string>
#include <iostream>
#include <cerrno>

std::string getFileContent(const std::string& fileName){
    
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::cout<<"shader File Problem"<<std::endl;
	throw(errno);
}

GLuint createShader(const std::string& shaderFile, unsigned int shaderType){
	// Convert the shader source strings into character arrays
	const std::string shaderData = getFileContent(shaderFile);
	const char* source = shaderData.c_str();
	// Create Shader Object and get its reference
	GLuint shader = glCreateShader(shaderType);
	// Attach Shader source to the Shader Object
	glShaderSource(shader, 1, &source, NULL);
	// Compile the Shader into machine code
	glCompileShader(shader);

	// Check if the shader compiled successfully
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        // Provide the info log in some manner
        std::cerr << "Shader compilation error in file: " << shaderFile << std::endl;
        std::cerr << &errorLog[0] << std::endl;

        // Don't leak the shader
        glDeleteShader(shader);
        return 0;
    }

	return shader;
}

Shader::Shader(){}

Shader::Shader(const Shader &other)
{
	Id = other.Id;
}

Shader::Shader(Shader &&other) noexcept
{
	Id = other.Id;
    other.Id = 0; // Mark the other shader as moved from
}

Shader::Shader(const char* vertexFileName, const char* fragmentFileName, const char* geometryFileName){
	std::vector<GLuint> shaders;

	// Create Shader Program Object and get its reference
	Id = glCreateProgram();

	if(vertexFileName){
		std::string vertexFile = shaderDirPath + vertexFileName;

		// Create Vertex Shader Object and store its reference
		shaders.push_back(createShader(vertexFile, GL_VERTEX_SHADER));
	}

	if(geometryFileName){
		std::string geometryFile = shaderDirPath + geometryFileName;

		// Create Geometry Shader Object and store its reference
		shaders.push_back(createShader(geometryFile, GL_GEOMETRY_SHADER));
	}

	if(fragmentFileName){
		std::string fragmentFile = shaderDirPath + fragmentFileName;

		// Create Fragment Shader Object and store its reference
		shaders.push_back(createShader(fragmentFile, GL_FRAGMENT_SHADER));
	}

	for(GLuint shaderId : shaders)
		glAttachShader(Id, shaderId);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(Id);

	GLint success;
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Failed: " << infoLog << std::endl;
    }

	for(GLuint shaderId : shaders)
		glDeleteShader(shaderId);
}

void Shader::activate(){
    glUseProgram(Id);
}

void Shader::Delete(){
    glDeleteProgram(Id);
}