#pragma once

#include "../../OpenGL/GLRenderer.h"

class CMain
{
public:
  static CMain& getInstance();
  CGLRenderer& getRenderer();

  static void timedDraw(int);
  static void drawScene();
  static void reshape(int w, int h);
  static void keyCB(unsigned char key, int x, int y);

private:
  CMain() {};
  ~CMain() {};

  CGLRenderer m_renderer;
};
