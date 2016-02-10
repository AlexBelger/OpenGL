#include "stdafx.h"
#include "GLRenderer.h"
#include "Shapes/ShapeGenerator.h"
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

CGLRenderer::CGLRenderer():
	X_STEP(0.1f)
	, BODY_WIDTH(0.2f)
{
}

CGLRenderer::~CGLRenderer()
{
}

void CGLRenderer::PrepareScene()
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	m_program = new CGLProgram();
	m_pVertSh = new CGLShader(GL_VERTEX_SHADER);
	m_pFragSh = new CGLShader(GL_FRAGMENT_SHADER);

	m_pVertSh->Load("minimal.vert");
	m_pFragSh->Load("minimal.frag");

	m_pVertSh->Compile();
	m_pFragSh->Compile();

	m_program->AttachShader(*m_pVertSh);
	m_program->AttachShader(*m_pFragSh);

	m_program->BindAttribLocation(0, "in_Position");
	m_program->BindAttribLocation(1, "in_Color");

	m_program->Link();
	m_program->Use();

	m_program->DeleteShader(*m_pVertSh);
	m_program->DeleteShader(*m_pFragSh);

	SetData();
}

void CGLRenderer::SetData()
{
	CShapeData cube = CShapeGenerator::makeCube();

	GLuint verticesBufferId;
	glGenBuffers(1, &verticesBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId);
	glBufferData(GL_ARRAY_BUFFER, cube.getVertexBufferSize(), cube.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), reinterpret_cast<char*>(3 * sizeof(GLfloat)));

	GLuint indexArrayBufferId;
	glGenBuffers(1, &indexArrayBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.getIndexBufferSize(), cube.indices, GL_STATIC_DRAW);
	cube.cleanup();
}

void CGLRenderer::Reshape(int w, int h)
{
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);
}

void CGLRenderer::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projectionMatrix = glm::perspective(30.0f, (static_cast<float>(m_width) / m_height), .1f, 10.0f);
	glm::mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, glm::vec3(.0f, .0f, -3.0f));
	glm::mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, 76.0f, glm::vec3(.0f, 1.0f, .0f));

	GLint translationMatrixUniformLocation = glGetUniformLocation(m_program->GetProgramId(), "fullTransformMatrix");

	glUniformMatrix4fv(translationMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	FinishDrawing();
}

void CGLRenderer::FinishDrawing()
{
	glFinish();
	glFlush();
}

void CGLRenderer::DestroyScene()
{
	m_program->DetachShader(*m_pVertSh);
	m_program->DetachShader(*m_pFragSh);

	delete m_program;
	m_program = nullptr;

	delete m_pVertSh;
	m_pVertSh = NULL;
	delete m_pFragSh;
	m_pFragSh = NULL;
}
