#include <GL/glut.h>

#include "draw.h"

int numberOfPoints = 6;

void keyboard(unsigned char key, int x, int y)
{

  switch (key)
  {
  case '+':
    numberOfPoints++;
    break;
  case '-':
    numberOfPoints--;
    break;
  }

  drawSinPoints(numberOfPoints);
}

void init(void)
{
  int windowWidth = 400,
      windowHeight = 400;

  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Exercise 2");
  glutKeyboardFunc(keyboard);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(-0.5, 7, -1.5, 1.5);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  init();
  drawSinPoints(numberOfPoints);
  glutMainLoop();
}