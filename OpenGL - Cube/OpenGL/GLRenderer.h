#pragma once
#include "GLProgram.h"
#include "GLShader.h"

#include <GL/glew.h>
#include <GL/wglew.h>

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
	void PrepareScene();		// Scene preparation stuff
//	void SendMoreData();
	void Reshape(int w, int h);	// Changing viewport
	void DrawScene();		// Draws the scene
	void DestroyScene();		// Cleanup

protected:
	void SetData();	                        // Creates VAO and VBOs and fill them with data

protected:
	static void FinishDrawing();

	HGLRC	 m_hrc;                        // OpenGL Rendering Context 
	CGLProgram* m_program;	               // Program
	CGLShader* m_pVertSh;		       // Vertex shader
	CGLShader* m_pFragSh;		       // Fragment shader

	GLuint m_vaoID[2];			// two vertex array objects, one for each drawn object
	GLuint m_vboID[3];			// three VBOs
	const GLfloat X_STEP;
	const GLfloat BODY_WIDTH;
	enum StepInfo
	{
		MAX_STEPS = 22
	};
	int m_width;
	int m_height;
};

