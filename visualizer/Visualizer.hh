#ifndef VISUALIZER__HH
#define VISUALIZER__HH

#include <vector>
#include "../utils/Mat3d.hh"
#include "./utils/Mesh.hh"

class Visualizer{
private:
    std::vector<Shader> shaders;
    Camera* camera;
    Mesh* road;
    GLFWwindow *window;

    int maxX;
    int maxY;
    int maxZ;
public:
    Visualizer(int maxZ, int maxY, int maxX);
    ~Visualizer();

    void attach(Mat3d& matrix);

    void show();
};

#endif