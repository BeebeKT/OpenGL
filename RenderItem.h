#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>

class RenderItem
{
public:
	RenderItem();
	~RenderItem();
	void Initialize();
	unsigned int * getVBO();
	unsigned int * getEBO();
	unsigned int * getVAO();

	void reset();
private:
	unsigned int VAO,VBO,EBO,colorVBO;
};

