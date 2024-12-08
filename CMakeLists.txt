cmake_minimum_required(VERSION 3.16)

# Project name
project(3D_MRI)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Find GLFW
find_package(glfw3 REQUIRED)
# Find OpenGL
find_package(OpenGL REQUIRED)
# Find GLEW
find_package(GLEW REQUIRED)
# Find GLM
find_package(GLM REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/visualizer/utils)
include_directories(${GLM_INCLUDE_DIRS})

# Manually specify GDCM include and library paths
set(GDCM_INCLUDE_PATH "/opt/homebrew/Cellar/gdcm/3.0.24/include/gdcm-3.0")
set(GDCM_LIB_PATH "/opt/homebrew/Cellar/gdcm/3.0.24/lib")

set(SOURCE_FILES
    main.cpp
    main.cpp
    utils/DcmReader.cc
    utils/Mat3d.cc
    visualizer/utils/EBO.cc
    visualizer/utils/VBO.cc
    visualizer/utils/VAO.cc
    visualizer/utils/Shader.cc
    visualizer/utils/Texture.cc
    visualizer/utils/Camera.cc
    visualizer/utils/ThreadPool.cc
    visualizer/utils/Mesh.cc
    visualizer/Visualizer.cc
)

# Prevent a "command line is too long" failure in Windows.
add_library(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/visualizer/glad/src/gl.c)
target_include_directories(GLAD PUBLIC visualizer/glad/include)
add_executable(main ${SOURCE_FILES})

# Include GDCM headers
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${GDCM_INCLUDE_PATH})


# Link all necessary GDCM libraries
target_link_libraries(main PRIVATE 
    glfw 
    ${OPENGL_gl_LIBRARY} 
    GLEW::GLEW 
    GLAD
    ${GDCM_LIB_PATH}/libgdcmMSFF.dylib
    ${GDCM_LIB_PATH}/libgdcmIOD.dylib
    ${GDCM_LIB_PATH}/libgdcmDICT.dylib
    ${GDCM_LIB_PATH}/libgdcmCommon.dylib
    ${GDCM_LIB_PATH}/libgdcmDSED.dylib  # Add this if necessary
    ${GDCM_LIB_PATH}/libgdcmjpeg8.dylib  # Add JPEG library if required
)

# Optionally, add the library path for the linker
link_directories(${GDCM_LIB_PATH})
