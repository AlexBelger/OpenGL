#include "stdafx.h"
#include "GLShader.h"

#include <memory>

CGLShader::CGLShader(UINT shaderType):
	m_shaderType(shaderType)
{
}

CGLShader::~CGLShader()
{
}

void CGLShader::Load(CString &&filename)
{
	CString shaderCode = GetShaderCode(filename);
	CT2A asciiShader(shaderCode);
	GLint length = shaderCode.GetLength();
	
	m_shader = glCreateShader(m_shaderType);

	const char *code = asciiShader.m_psz;
	glShaderSource(m_shader, 1, &code, &length);
}

CString CGLShader::GetShaderCode(const CString &filename)
{
	CFileException exception;
	CStdioFile file;
	if (!file.Open(filename, CFile::modeRead, &exception))
	{
		TRACE(L"Shader file opening error: %d\n", exception.m_lOsError);
		throw; //TODO
	}
	CString shaderCode;
	CString line;
	while (file.ReadString(line))
		shaderCode.Append(line + L"\n");
	file.Close();
	return shaderCode;
}

void CGLShader::Compile()
{
	GLint compiled;

	glCompileShader(m_shader);
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		TRACE(L"Vertex shader not compiled.\n");
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
		TRACE(L"InfoLog: %S", infoLog);;
	}

	// should additionally check for OpenGL errors here
}

GLuint CGLShader::GetShader()
{
	return m_shader;
}