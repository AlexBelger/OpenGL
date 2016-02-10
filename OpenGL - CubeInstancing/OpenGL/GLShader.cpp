#include "stdafx.h"
#include "GLShader.h"

#include <iostream>
#include <fstream>

#include <memory>

CGLShader::CGLShader(unsigned int shaderType):
	m_shaderType(shaderType)
{
}

CGLShader::~CGLShader()
{
}

void CGLShader::Load(std::string &&filename)
{
  std::string shaderCode = GetShaderCode(filename);
  GLint length = shaderCode.size();
	
  m_shader = glCreateShader(m_shaderType);

  const char *code = shaderCode.c_str();
  glShaderSource(m_shader, 1, &code, &length);
}

std::string CGLShader::GetShaderCode(const std::string &filename)
{
  std::string shaderCode;
  std::string line;
  std::ifstream file("../../Shader/" + filename);
  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      shaderCode.append(line + '\n');
    }
    file.close();
  }
  else
  {
    std::cout << "Unable to open file";
    throw; //TODO
  }
  return shaderCode;
}

void CGLShader::Compile()
{
  GLint compiled;

  glCompileShader(m_shader);
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled)
  {
    std::cout << "Vertex shader not compiled.\n";
    PrintShaderInfoLog();
  }
}

void CGLShader::PrintShaderInfoLog()
{
  int infoLogLen = 0;
  glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLen);

  // should additionally check for OpenGL errors here

  if (infoLogLen > 0)
  {
    std::unique_ptr<GLchar[]> infoLog(new GLchar[infoLogLen]);
    int charsWritten = 0;
    glGetShaderInfoLog(m_shader, infoLogLen, &charsWritten, infoLog.get());
    std::cout << L"InfoLog: " << std::string(infoLog.get());
  }

  // should additionally check for OpenGL errors here
}

GLuint CGLShader::GetShader()
{
  return m_shader;
}
