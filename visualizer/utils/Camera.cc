#include "Camera.hh"

Camera::Direction Camera::getDirection()
{
	float rt = rotation * 2.0f;
	if (rt > NorthNorthWest || rt <= NorthNorthEast)
		return North;
	if (rt <= EastNorthEast)
		return NorthEast;
	if (rt <= EastSouthEast)
		return East;
	if (rt <= SouthSouthEast)
		return SouthEast;
	if (rt <= SouthSouthWest)
		return South;
	if (rt <= WestSouthWest)
		return SouthWest;
	if (rt <= WestNorthWest)
		return West;
	if (rt <= NorthNorthWest)
		return NorthWest;

	return Error;
}

void Camera::check()
{
	if (y >= (maxY - windowYSize))
	{
		y = maxY - windowYSize;
	}
	if (x >= (maxX - windowXSize))
	{
		x = maxX - windowXSize;
	}
	if (x <= 0.0f)
	{
		x = 0.0f;
	}
	if (y <= 0.0f)
	{
		y = 0.0f;
	}
	if(windowXSize > maxX)
		windowXSize = maxX;
	if(windowYSize > maxY)
		windowYSize = maxY;
}

Camera::Camera(int maxZ, int maxY, int maxX, int width, int height) : maxZ(maxZ), maxY(maxY), maxX(maxX)
{
	Camera::width = width;
	Camera::height = height;
	Camera::x = 0;
	Camera::y = 0;
	Camera::z = 0;
	this->windowXSize = maxX;
	this->windowYSize = maxY;
	this->scalaColorePoint = 1.0f;
	scalaColoreLine = 1.0f;
	shiftHolding = false;
	rotation = 0.0f;
	enableImage = enablePoints = enableLines = enablePointsPath = true;
}

void Camera::updateMatrix(float fovDeg, float nearPlane, float farPlane)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 1.0f));
	model *= glm::rotate(model, glm::radians(up), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 proj = glm::perspective(glm::radians(fovDeg), (float)(width / height), nearPlane, farPlane);

	Camera::cameraMatrix = proj * view * model;
}

void Camera::matrix(Shader &shader, const char *uniform)
{
	shader.activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.Id, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::inputs(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		rotation += 0.5f;
		if (shiftHolding)
			rotation += 0.5f;
		if (rotation >= 180.0f)
			rotation = fmod(rotation, 180.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		rotation -= 0.5f;
		if (shiftHolding)
			rotation -= 0.5f;

		rotation = fmod(rotation, 180.0f);
		if (rotation < 0.0f)
			rotation += 180.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		up -= 0.1f;
		if (shiftHolding)
			up -= 0.1f;

		up = fmod(up, 360.0f);
		if (up < 0.0f)
			up += 360.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		up += 0.1f;
		if (shiftHolding)
			up += 0.1f;
		if (up >= 360.0f)
			up = fmod(up, 360.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		if (windowXSize > 50 && windowYSize > 50)
		{
			float ratio = 1.0f;
			int margin = speed / 2;

			if (maxX <= maxY)
			{
				ratio = maxY / (float)maxX;
				x += margin;
				y += margin * ratio/2.0f;
				windowXSize = windowXSize - speed;
				windowYSize = windowYSize - speed * ratio;
			}
			else if (maxY < maxX)
			{
				ratio = maxX / (float)maxY;
				x += margin * ratio;
				y += margin;
				windowXSize = windowXSize - speed * ratio;
				windowYSize = windowYSize - speed;
			}
		}
		check();
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		float ratio = 1.0f;
		float margin = speed / 2.0f;

		if (windowXSize <= (maxX - speed))
		{
			if (maxX <= maxY)
				ratio = maxY / (float)maxX;
			x -= margin;
			y -= margin * ratio/2.0f;
			windowXSize = windowXSize + speed;
			windowYSize = windowYSize + speed * ratio;
		}
		else if (windowYSize <= (maxY - speed))
		{
			if (maxY < maxX)
				ratio = maxX / (float)maxY;
			x -= margin * ratio/2.0f;
			y -= margin;
			windowXSize = windowXSize + speed * ratio;
			windowYSize = windowYSize + speed;
		}
		check();
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (shiftHolding)
			scalaColorePoint *= 1.02f;
		else
			scalaColorePoint /= 1.02f;
	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		if (shiftHolding)
			scalaColoreLine *= 1.02f;
		else
			scalaColoreLine /= 1.02f;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Direction dir = getDirection();
		switch (dir)
		{
		case North:
			y -= 2 * speed;
			check();
			break;

		case NorthEast:
			y -= speed;
			x += speed;
			check();
			break;

		case East:
			x += 2 * speed;
			check();
			break;

		case SouthEast:
			x += speed;
			y += speed;
			check();
			break;

		case South:
			y += 2 * speed;
			check();
			break;
		case SouthWest:
			y += speed;
			x -= speed;
			check();
			break;
		case West:
			x -= 2 * speed;
			check();
			break;
		case NorthWest:
			x -= speed;
			y -= speed;
			check();
			break;

		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Direction dir = getDirection();
		switch (dir)
		{
		case North:
			y += 2 * speed;
			check();
			break;

		case NorthEast:
			y += speed;
			x -= speed;
			check();
			break;

		case East:
			x -= 2 * speed;
			check();
			break;

		case SouthEast:
			x -= speed;
			y -= speed;
			check();
			break;

		case South:
			y -= 2 * speed;
			check();
			break;
		case SouthWest:
			y -= speed;
			x += speed;
			check();
			break;
		case West:
			x += 2 * speed;
			check();
			break;
		case NorthWest:
			x += speed;
			y += speed;
			check();
			break;

		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Direction dir = getDirection();
		switch (dir)
		{
		case North:
			x -= 2 * speed;
			check();
			break;

		case NorthEast:
			x -= speed;
			y -= speed;
			check();
			break;

		case East:
			y -= 2 * speed;
			check();
			break;

		case SouthEast:
			y -= speed;
			x += speed;
			check();
			break;

		case South:
			x += 2 * speed;
			check();
			break;
		case SouthWest:
			y += speed;
			x += speed;
			check();
			break;
		case West:
			y += 2 * speed;
			check();
			break;
		case NorthWest:
			y += speed;
			x -= speed;
			check();
			break;

		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Direction dir = getDirection();
		switch (dir)
		{
		case North:
			x += 2 * speed;
			check();
			break;
		case NorthEast:
			x += speed;
			y += speed;
			check();
			break;
		case East:
			y += 2 * speed;
			check();
			break;
		case SouthEast:
			y += speed;
			x -= speed;
			check();
			break;
		case South:
			x -= 2 * speed;
			check();
			break;
		case SouthWest:
			y -= speed;
			x -= speed;
			check();
			break;
		case West:
			y -= 2 * speed;
			check();
			break;
		case NorthWest:
			y -= speed;
			x += speed;
			check();
			break;
		default:
			break;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && z < (maxZ - 1.0f))
	{
		z += 0.1;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && z > 0.9f)
		z -= 0.1;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		checkPressPoints = true;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		if (checkPressPoints)
		{
			enablePoints = !enablePoints;
			checkPressPoints = false;
		}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		checkPressPathPoints = true;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE)
		if (checkPressPathPoints)
		{
			enablePointsPath = !enablePointsPath;
			checkPressPathPoints = false;
		}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		checkPressLine = true;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE)
		if (checkPressLine)
		{
			enableLines = !enableLines;
			checkPressLine = false;
		}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		checkPressMesh = true;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE)
		if (checkPressMesh)
		{
			enableImage = !enableImage;
			checkPressMesh = false;
		}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
	{
		shiftHolding = true;
		speed = 10.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE)
	{
		shiftHolding = false;
		speed = 2.0f;
	}
}

const float &Camera::getX() const
{
	return x;
}

const float &Camera::getY() const
{
	return y;
}

const float &Camera::getZ() const
{
	return z;
}
