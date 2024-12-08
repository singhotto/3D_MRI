#include "Visualizer.hh"

Visualizer::Visualizer(int maxZ, int maxY, int maxX) : maxZ(maxZ), maxY(maxY), maxX(maxX), road(nullptr)
{
	const unsigned int width = 500;
	const unsigned int height = 500;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Pipes", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoaderLoadGL();

	glViewport(0, 0, width, height);
	
	shaders.reserve(3);
	shaders.push_back(Shader("texture.vert", "texture.frag"));
	shaders.push_back(Shader("point.vert", "point.frag"));
	shaders.push_back(Shader("line.vert", "line.frag", "line.geom"));

	camera = new Camera(maxZ, maxY, maxX, width, height);

	road = new Mesh(maxZ, maxY, maxX, shaders, *camera);
}

Visualizer::~Visualizer()
{
	delete road;
	delete camera;

	for(Shader& shader : shaders){
		shader.Delete();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Visualizer::attach(Mat3d &matrix)
{
	road->attach(&matrix);
}

void Visualizer::show()
{
	std::cout<<"Processing complete."<<std::endl;
	std::cout<<"Rendering 3D visualization..."<<std::endl;
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		//  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->inputs(window);
		road->draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		// glfwWaitEventsTimeout(0.025);
		glfwPollEvents();
	}
}