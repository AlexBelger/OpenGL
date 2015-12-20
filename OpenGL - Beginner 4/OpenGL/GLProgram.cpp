#include "stdafx.h"
#include "GLProgram.h"


CGLProgram::CGLProgram()
{
	m_program = glCreateProgram();
}


CGLProgram::~CGLProgram()
{
}

void CGLProgram::AttachShader(CGLShader &shader)
{
	glAttachShader(m_program, shader.GetShader());
}

void CGLProgram::BindAttribLocation(UINT pos, CString &&attrib)
{
	CT2A asciiAttrib(attrib);
	glBindAttribLocation(m_program, pos, asciiAttrib.m_psz);
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