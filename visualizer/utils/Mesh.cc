#include "Mesh.hh"

void Mesh::updateVertex()
{
	float zoomFactorX = (camera.windowXSize / (float)matXSize);
	float zoomFactorY = (camera.windowYSize / ((float)matYSize));
	float offsetX = camera.getX() / float(matXSize);
	float offsetY = camera.getY() / float(matYSize);

	vertex[3] = (offsetX + zoomFactorX * 1.0f);
	vertex[4] = (offsetY + zoomFactorY * 1.0f); // Top Right
	vertex[8] = (offsetX + zoomFactorX * 1.0f);
	vertex[9] = (offsetY + zoomFactorY * 0.0f); // Bottom Right
	vertex[13] = offsetX;
	vertex[14] = offsetY; // Bottom Left
	vertex[18] = (offsetX + zoomFactorX * 0.0f);
	vertex[19] = (offsetY + zoomFactorY * 1.0f); // Top Left

	vaoMatrix.Bind();
	vertexVBO.Bind();
	vertexVBO.update(vertexVBO.getSize(), vertex);

	vaoMatrix.LinkAttrib(vertexVBO, 0, 3, 5, 0);
	vaoMatrix.LinkAttrib(vertexVBO, 1, 2, 5, 3);
}

void Mesh::resetCamera(Shader &shader)
{
	camera.updateMatrix(45.0f, 0.1f, 100.0f);
	camera.matrix(shader, "camMatrix");
}

Mesh::Mesh(int sizeZ, int sizeY, int sizeX, std::vector<Shader> &shaders, Camera &camera) : shaders(shaders), camera(camera), vertex(nullptr), matrix(nullptr), matXSize(sizeX), matYSize(sizeY), matZSize(sizeZ)
{
}

Mesh::~Mesh()
{
	vertexVBO.Delete();
	pointVBO.Delete();
	lineVBO.Delete();
	pathPointVBO.Delete();
	pathAlphaVBO.Delete();
	lineColorVBO.Delete();
	lineWidthVBO.Delete();

	delete[] vertex;
}
void Mesh::draw()
{
	if (matrix != nullptr && camera.enableImage)
	{
		resetCamera(shaders[0]);
		drawImage();
	}
}

void Mesh::attach(Mat3d *matrix)
{
	shaders[0].activate();
	this->matrix = matrix;
	vertex = new float[20];

	float margin = 0.0f;

	if (matXSize <= matYSize)
	{
		margin = (((matYSize - matXSize) / (float)matYSize));
		mostLeft += margin;
		mostRight -= margin;
	}

	if (matXSize > matYSize)
	{
		margin = (((matXSize - matYSize) / (float)matXSize));
		mostBottom += margin;
		mostTop -= margin;
	}

	// Assign the values directly to vertex
	vertex[10] = mostLeft;
	vertex[11] = mostBottom;
	vertex[12] = 0.0f;
	vertex[13] = 0.0f;
	vertex[14] = 0.0f; // Bottom Left
	vertex[15] = mostLeft;
	vertex[16] = mostTop;
	vertex[17] = 0.0f;
	vertex[18] = 0.0f;
	vertex[19] = 1.0f; // Top Left
	vertex[0] = mostRight;
	vertex[1] = mostTop;
	vertex[2] = 0.0f;
	vertex[3] = 1.0f;
	vertex[4] = 1.0f; // Top Right
	vertex[5] = mostRight;
	vertex[6] = mostBottom;
	vertex[7] = 0.0f;
	vertex[8] = 1.0f;
	vertex[9] = 0.0f; // Bottom Right

	vaoMatrix.Bind();

	vertexVBO.reset(20, vertex, GL_DYNAMIC_DRAW);

	vaoMatrix.LinkAttrib(vertexVBO, 0, 3, 5, 0);
	vaoMatrix.LinkAttrib(vertexVBO, 1, 2, 5, 3);

	vaoMatrix.Unbind();

	texture.reset(matrix, 0, matrix->getRows(), matrix->getCols(), 0);
}

void Mesh::drawImage()
{
	texture.texUnit(shaders[0], "tex0");

	texture.Bind();
	texture.update((int)camera.getZ());

	vaoMatrix.Bind();
	updateVertex();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	vaoMatrix.Unbind();
}