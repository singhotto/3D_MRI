#ifndef MESH_HH
#define MESH_HH

#define GLFW_INCLUDE_GLCOREARB
#include <string>
#include <vector>
#include "VAO.hh"
#include "EBO.hh"
#include "Camera.hh"
#include "Texture.hh"
#include "Shader.hh"
#include "../../utils/Mat3d.hh"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Mesh
{
private:
    Texture texture;
    VAO vaoMatrix;
    VBO vertexVBO;

    VAO vaoPoint;
    VBO pointVBO;

    VAO vaoPathPoint;
    VBO pathPointVBO;
    VBO pathAlphaVBO;

    VAO vaoDiffPathPoint;
    VBO pathDiffPointVBO;
    VBO pathDiffColorVBO;

    VAO vaoLine;
    VBO lineVBO;
    VBO lineColorVBO;
    VBO lineWidthVBO;

    Mat3d *matrix;

    std::vector<Shader>& shaders;
    Camera &camera;

    float *vertex;

    int matXSize;
    int matYSize;
    int matZSize;
    float mostLeft = -1.0f;
    float mostRight = 1.0f;
    float mostTop = 1.0f;
    float mostBottom = -1.0f;

    void resetCamera(Shader& shader);
    void drawImage();
    void updateVertex();
public:
    Mesh(int sizeZ, int sizeY, int sizeX, std::vector<Shader>& shaders, Camera &camera);
    ~Mesh();

    void attach(Mat3d *matrix);

    void draw();
};

#endif