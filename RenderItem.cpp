#include "RenderItem.h"



RenderItem::RenderItem()
{
}


RenderItem::~RenderItem()
{
}

void RenderItem::Initialize() {
	
	/////////////////////////need to interleave attributes into one VBO


	float vertices[]{
	 -0.5f,  0.5f, 0.0f,  // top 1
	 -1.0f, -0.5f, 0.0f,  // bottom left 1
	0.0f, -0.5f, 0.0f,  // bottom right/bottom left
	1.0f,  -0.5f, 0.0f,  // bottom right 2
	0.5f,0.5f,0.0f  // top 2
	};

	unsigned int indices[] = {
	0, 1, 2,   // first triangle
	2, 3, 4    // second triangle
	};

	float colors[]{
	 1.0f,  0.0f, 0.0f,  // top 1
	 0.0f, 0.f, 1.0f,  // bottom left 1
	0.0f, 1.0f, 0.0f,  // bottom right/bottom left
	0.0f,  0.0f, 1.0f,  // bottom right 2
	1.0f,0.0f,0.0f  // top 2
	};

	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &EBO);
	

	// bind vertex array object first before VBO,EBO
	glBindVertexArray(VAO);

	//bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //static draw = positions not change frequently

	//bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); //static draw = positions not change frequently

	//bind Element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	// tell opengl how to interpret vertex data(location = 0, 3 values, float type, normalize = false,stride, start offset in buffer)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);   /////// can only bind one buffer at a time(bind then attribute pointer for each)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(0); // 0 = location of vertex attribute
	glEnableVertexAttribArray(1); // 0 = location of vertex attribute

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	// unbind VAO
	glBindVertexArray(0);
}

unsigned int * RenderItem::getVBO() {
	return &VBO;
}

unsigned int * RenderItem::getEBO() {
	return &EBO;
}

unsigned int * RenderItem::getVAO() {
	return &VAO;
}

void RenderItem::reset() {
	// delete VAO,VBO,EBO cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);
}