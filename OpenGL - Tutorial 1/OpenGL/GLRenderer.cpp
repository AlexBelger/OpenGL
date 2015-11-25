#include "stdafx.h"
#include "GLRenderer.h"

CGLRenderer::CGLRenderer()
{
}


CGLRenderer::~CGLRenderer()
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	HGLRC tempContext = wglCreateContext(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, tempContext);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		AfxMessageBox(_T("GLEW is not initialized!"));
	}

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		m_hrc = wglCreateContextAttribsARB(pDC->m_hDC, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(pDC->m_hDC, m_hrc);
	}
	else
	{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
		m_hrc = tempContext;
	}

	//Checking GL version
	const GLubyte *GLVersionString = glGetString(GL_VERSION);

	//Or better yet, use the GL3 way to get the version number
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	m_pProgram = new CGLProgram();
	m_pVertSh = new CGLShader(GL_VERTEX_SHADER);
	m_pFragSh = new CGLShader(GL_FRAGMENT_SHADER);

	m_pVertSh->Load(_T("minimal.vert"));
	m_pFragSh->Load(_T("minimal.frag"));

	m_pVertSh->Compile();
	m_pFragSh->Compile();

	m_pProgram->AttachShader(*m_pVertSh);
	m_pProgram->AttachShader(*m_pFragSh);

	m_pProgram->BindAttribLocation(0, L"in_Position");
	m_pProgram->BindAttribLocation(1, L"in_Color");

	m_pProgram->Link();
	m_pProgram->Use();

	SetData();
}

void CGLRenderer::SetData()
{
	// First simple object
	float* vert = new float[9];	// vertex array
	float* col = new float[9];	// color array

	vert[0] = -0.3; vert[1] = 0.5; vert[2] = -1.0;
	vert[3] = -0.8; vert[4] = -0.5; vert[5] = -1.0;
	vert[6] = 0.2; vert[7] = -0.5; vert[8] = -1.0;

	col[0] = 1.0; col[1] = 0.0; col[2] = 0.0;
	col[3] = 0.0; col[4] = 1.0; col[5] = 0.0;
	col[6] = 0.0; col[7] = 0.0; col[8] = 1.0;

	// Second simple object
	float* vert2 = new float[9];	// vertex array

	vert2[0] = -0.2; vert2[1] = 0.5; vert2[2] = -1.0;
	vert2[3] = 0.3; vert2[4] = -0.5; vert2[5] = -1.0;
	vert2[6] = 0.8; vert2[7] = 0.5; vert2[8] = -1.0;

	// Two VAOs allocation
	glGenVertexArrays(2, &m_vaoID[0]);

	// First VAO setup
	glBindVertexArray(m_vaoID[0]);

	glGenBuffers(2, m_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), col, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Second VAO setup	
	glBindVertexArray(m_vaoID[1]);

	glGenBuffers(1, &m_vboID[2]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vert2, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	delete[] vert;
	delete[] vert2;
	delete[] col;
}

void CGLRenderer::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(m_vaoID[0]);		// select first VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	// draw first object

	glBindVertexArray(m_vaoID[1]);		// select second VAO
	glVertexAttrib3f((GLuint)1, 1.0, 0.0, 0.0); // set constant color attribute
	glDrawArrays(GL_TRIANGLES, 0, 3);	// draw second object

	glBindVertexArray(0);

	FinishDrawing();

	SwapBuffers(pDC->m_hDC);
}

void CGLRenderer::FinishDrawing()
{
	glFinish();
	glFlush();
}

void CGLRenderer::DestroyScene()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(3, m_vboID);

	glBindVertexArray(0);
	glDeleteVertexArrays(2, m_vaoID);

	m_pProgram->DetachShader(*m_pVertSh);
	m_pProgram->DetachShader(*m_pFragSh);

	delete m_pProgram;
	m_pProgram = NULL;

	delete m_pVertSh;
	m_pVertSh = NULL;
	delete m_pFragSh;
	m_pFragSh = NULL;

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}