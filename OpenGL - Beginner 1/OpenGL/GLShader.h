#pragma once
class CGLShader
{
public:
	CGLShader(UINT shaderType);
	~CGLShader();

	void Load(CString &&file);
	void Compile();
	GLuint GetShader();

private:
	CString GetShaderCode(const CString &filename);
	void PrintShaderInfoLog();

	GLuint m_shader;
	UINT m_shaderType;
};

