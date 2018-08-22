#include <GL/glut.h>
#include <stdio.h>

#include "draw.h"

void init(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'a':
    drawTriangle();
    break;
  case 'b':
    drawEmptyTriangle();
    break;
  case 'c':
    drawBothTriangles();
    break;
  case 'd':
    drawSemiHexagon();
    break;
  default:
    clearScreen();
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Exercise 1");

  init();

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(clearScreen);
  glutMainLoop();
}