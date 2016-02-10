#pragma once
#include "stdafx.h"
#include "GLProgram.h"
#include "GLShader.h"

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
	void PrepareScene();		// Scene preparation stuff
	void SendMoreData();
	void Reshape(int w, int h);	// Changing viewport
	void DrawScene();		// Draws the scene
	void DestroyScene();		// Cleanup

protected:
	void SetData();	                        // Creates VAO and VBOs and fill them with data

protected:
	void FinishDrawing();

	CGLProgram* m_pProgram;	               // Program
	CGLShader* m_pVertSh;		       // Vertex shader
	CGLShader* m_pFragSh;		       // Fragment shader

	GLuint m_vaoID[2];			// two vertex array objects, one for each drawn object
	GLuint m_vboID[3];			// three VBOs
	int m_dataOffset;
	const GLfloat X_STEP;
	const GLfloat BODY_WIDTH;
	enum StepInfo
	{
		MAX_STEPS = 22
	};
};

