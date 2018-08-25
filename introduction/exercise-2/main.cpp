#include <GL/glut.h>

#include "draw.h"

void init(void)
{
  int windowWidth = 400,
      windowHeight = 400;

  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Exercise 2");
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(-0.5, 7, -1.5, 1.5);
}

int main(int argc, char **argv)
{
  int numberOfPoints = 3600;

  glutInit(&argc, argv);
  init();
  drawSinPoints(numberOfPoints);
  glutMainLoop();
}