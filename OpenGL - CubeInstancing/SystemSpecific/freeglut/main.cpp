
#include "Main.h"
#include "GL/freeglut.h"

int main( int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(800,600);
  glutCreateWindow("OpenGL - Cube");

  GLenum err = glewInit();
  if (GLEW_OK != err)
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
 
  glClearColor(.0f,.0f,.0f,.0f);
  gluOrtho2D(0, 800, 0, 600);
  glutDisplayFunc(&CMain::drawScene);
  glutReshapeFunc(&CMain::reshape);
  glutKeyboardFunc(&CMain::keyCB);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  
  CGLRenderer& renderer = CMain::getInstance().getRenderer();
  renderer.PrepareScene();
  glutTimerFunc(1000, CMain::timedDraw, 1);
  glutMainLoop();
  renderer.DestroyScene();

  return 0;
}

CMain& CMain::getInstance()
{
  static CMain instance;
  return instance;
}

CGLRenderer& CMain::getRenderer()
{
  return m_renderer;
}

void CMain::keyCB(unsigned char key, int x, int y)
{
  if( key == 'q' ) 
    glutLeaveMainLoop();
}

void CMain::timedDraw(int value)
{
  CMain::drawScene();
  glutTimerFunc(100, CMain::timedDraw, 1);
}

void CMain::drawScene()
{
  CGLRenderer& renderer = CMain::getInstance().getRenderer();
  renderer.DrawScene();
  glutSwapBuffers();
}

void CMain::reshape(int w, int h)
{
  CMain::getInstance().getRenderer().Reshape(w, h);
}

