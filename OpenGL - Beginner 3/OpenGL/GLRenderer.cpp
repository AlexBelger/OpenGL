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
	glClearColor(0.0, 0.0, 1.0, 1.0);

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
	GLfloat vertices[] = {
		-1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};
	GLuint verticesBufferId;
	glGenBuffers(1, &verticesBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<char*>(2 * sizeof(GLfloat)));

	GLushort indices[] = { 0,2,1,2,3,4 };
	GLuint indicesBufferId;
	glGenBuffers(1, &indicesBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CGLRenderer::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
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
	m_pProgram->DetachShader(*m_pVertSh);
	m_pProgram->DetachShader(*m_pFragSh);

	delete m_pProgram;
	m_pProgram = NULL;

	delete m_pVertSh;
	m_pVertSh = NULL;
	delete m_pFragSh;
	m_pFragSh = NULL;
}