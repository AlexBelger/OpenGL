#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <string>

class CGLShader
{
public:
	CGLShader(unsigned int shaderType);
	~CGLShader();

	void Load(std::string &&file);
	void Compile();
	GLuint GetShader();

private:
	std::string GetShaderCode(const std::string &filename);
	void PrintShaderInfoLog();

	GLuint m_shader;
	unsigned int m_shaderType;
};

