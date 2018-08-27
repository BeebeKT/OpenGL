#include "ShaderProgram.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram()
{
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::reset() {
	glDeleteProgram(programId);
}

unsigned int * ShaderProgram::getId() {
	return &programId;
}

void ShaderProgram::Initialize(const char * vertexFile, const char * fragmentFile) {
	programId = glCreateProgram();

	string str;
	ifstream file(vertexFile);
	const GLchar* shaderSource;
	if (!file) {
	std:cout << "file not found";
	}
	else {
		str.assign((istreambuf_iterator< char >(file)), istreambuf_iterator< char >());
		shaderSource = str.c_str();
	}

	
	unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vertexId);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	ifstream file2(fragmentFile);
	const GLchar* source;
	if (!file2) {
	cout << "file not found";
	}
	else {
		str.assign((istreambuf_iterator< char >(file2)), istreambuf_iterator< char >());
		source = str.c_str();
	}

	


	unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &source, NULL);
	glCompileShader(fragmentId);

	// check for shader compile errors
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//attach vertex and fragment sahders to shader program
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);

	//individual shader objects are no longer needed, delete
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);


}
