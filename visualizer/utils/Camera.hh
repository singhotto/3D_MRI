#ifndef CAMERA__HH
#define CAMERA__HH

#define GLM_ENABLE_EXPERIMENTAL
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hh"

class Camera
{
private:
    enum Direction {
        North = 0,            // 0 gradi
        NorthNorthEast = 22,  // 22.5 gradi
        NorthEast = 45,       // 45 gradi
        EastNorthEast = 67,   // 67.5 gradi
        East = 90,            // 90 gradi
        EastSouthEast = 112,  // 112.5 gradi
        SouthEast = 135,      // 135 gradi
        SouthSouthEast = 157, // 157.5 gradi
        South = 180,          // 180 gradi
        SouthSouthWest = 202, // 202.5 gradi
        SouthWest = 225,      // 225 gradi
        WestSouthWest = 247,  // 247.5 gradi
        West = 270,           // 270 gradi
        WestNorthWest = 292,  // 292.5 gradi
        NorthWest = 315,      // 315 gradi
        NorthNorthWest = 337,  // 337.5 gradi
        Error = -1
    };

    int maxZ;
    int maxY;
    int maxX;
    float x, y, z;
    float up = -2.0f;
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    int width;
    int height;
    float rotation;
    bool checkPressPoints;
    bool checkPressPathPoints;
    bool checkPressLine;
    bool checkPressMesh;

    bool firstClick = true;
    float test = 1.0f;
    float sensitivity = 100.0f;
    bool shiftHolding;

    void check();
    Direction getDirection();

public:
    float speed = 2.0f;
    int windowXSize;
    int windowYSize;
    float scalaColorePoint;
    float scalaColoreLine;
    
    bool enablePoints;
    bool enablePointsPath;
    bool enableLines;
    bool enableImage;

    Camera(int maxZ, int maxY, int maxX, int width, int height);
    void updateMatrix(float fovDeg, float nearPlane, float farPlane);
    void matrix(Shader &shader, const char *uniform);
    void inputs(GLFWwindow *window);
    const float& getX() const;
    const float& getY() const;
    const float& getZ() const;
};

#endif