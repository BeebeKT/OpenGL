#pragma once



class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void Initialize(const char * vertexFile, const char * fragmentFile);
	
	void reset();

	unsigned int * getId();

private:
	unsigned int programId;
	

};

