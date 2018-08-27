#include <GL/glut.h>
#include <stdio.h>

#include "draw.h"

void init(void)
{
  gluOrtho2D(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_WIDTH, WINDOW_HEIGHT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  drawFirstQuadrant();
  // drawSecondQuadrant();
  drawThirdQuadrant();
  // drawFourthQuadrant();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(20, 20);
  glutCreateWindow("Exercise 1");
  

  init();
  glutDisplayFunc(display);
  glutMainLoop();
}