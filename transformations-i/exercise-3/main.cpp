#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw.h"

#define MAX_X 60
#define MAX_Y 60
#define MAX_Z 60

void display(void);
void init(void);

main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void init (void) {
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("checkerboard");

  glClearColor (0.0, 0.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, MAX_X, 0, MAX_Y, 0.0, MAX_Z);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawBoard(MAX_X, MAX_Y);

  glutSwapBuffers ();
  glutPostRedisplay();
}