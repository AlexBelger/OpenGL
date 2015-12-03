#pragma once
#include "GLShader.h"

class CGLProgram
{
public:
	CGLProgram();
	~CGLProgram();

	void AttachShader(CGLShader &shader);
	void BindAttribLocation(UINT pos, CString &&attrib);
	void Link();
	void Use();
	void DetachShader(CGLShader &shader);

private:
	GLuint m_program;
};

