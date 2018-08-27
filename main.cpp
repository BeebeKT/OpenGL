#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <memory>

#include <fstream>
#include <string>
#include <iostream>
#include "RenderItem.h"
#include "ShaderProgram.h"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window =  glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	
	if (window == NULL)
	{
		// error handling
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; 

		return -1;
	}

	glViewport(0,0,800,600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	unique_ptr<ShaderProgram> shader = make_unique<ShaderProgram>();
	shader->Initialize("Vertex.txt", "Fragment.txt");
	
	unique_ptr<RenderItem> first = make_unique<RenderItem>();

	first->Initialize();

	// to draw wireframes instead of filling
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		// render commands HERE
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // set window color
		glClear(GL_COLOR_BUFFER_BIT); // clear color buffer

		
		// use shader program object
		glUseProgram(*shader->getId());

		//bind VAO
		glBindVertexArray(*first->getVAO());

		// enable face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW); // front face is counter clock-wise indices


		// draw  triangles, 6 elements, type of indices, 0 offset in EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		// check/call events then double buffer swap
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	first->reset();
	shader->reset();
	glfwTerminate();
	return 0;

}

//  whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



