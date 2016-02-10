#include "stdafx.h"
#include "GLProgram.h"

CGLProgram::CGLProgram()
{
  m_program = glCreateProgram();
}

CGLProgram::~CGLProgram()
{
  glUseProgram(0);
  glDeleteProgram(m_program);
}

GLuint CGLProgram::GetProgramId()
{
  return m_program;
}

void CGLProgram::AttachShader(CGLShader &shader)
{
  glAttachShader(m_program, shader.GetShader());
}

void CGLProgram::BindAttribLocation(UINT pos, std::string &&attrib)
{
	glBindAttribLocation(m_program, pos, attrib.c_str());
}

void CGLProgram::Link()
{
	glLinkProgram(m_program);
}

void CGLProgram::Use()
{
	glUseProgram(m_program);
}

void CGLProgram::DetachShader(CGLShader &shader)
{
	glDetachShader(m_program, shader.GetShader());
}

void CGLProgram::DeleteShader(CGLShader &shader)
{
	glDeleteShader(shader.GetShader());
}
