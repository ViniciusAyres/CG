#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw.h"

#define MAX_X 300
#define MAX_Y 300
#define MAX_Z 300

#define WINDOW_X 300
#define WINDOW_Y 300

#define BOARD_SPACES 6

void display(void);
void init(void);
void mouse(int button, int state, int x, int y);

int circleX = 25;
int circleY = 25;

main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

void init (void) {
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (WINDOW_X, WINDOW_Y);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("checkerboard");

  glClearColor (0.0, 0.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, MAX_X, 0, MAX_Y, 0.0, MAX_Z);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
  int slotX = WINDOW_X / BOARD_SPACES;
  int slotXCenter = slotX / 2;
  int slotY = WINDOW_Y / BOARD_SPACES;
  int slotYCenter = slotY / 2;

  circleX = slotX * (x / slotX) + slotXCenter;
  circleY = slotY * ((MAX_Y - y) / slotY) + slotYCenter;
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawBoard(MAX_X, MAX_Y, BOARD_SPACES);
  drawCircle(circleX, circleY);

  glutSwapBuffers ();
  glutPostRedisplay();
}