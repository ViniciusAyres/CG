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

void idle(void);
void mouse(int button, int state, int x, int y);
void display(void);
void init(void);

int circleX = 25,
    circleY = 25,
    dx = circleX,
    dy = circleY;

float desiredFPS = 60;

main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutIdleFunc(idle);
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

  dx = slotX * (x / slotX) + slotXCenter;
  dy = slotY * ((MAX_Y - y) / slotY) + slotYCenter;
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawBoard(MAX_X, MAX_Y, BOARD_SPACES);
  drawCircle(circleX, circleY);

  glutSwapBuffers ();
  glutPostRedisplay();
}

void idle() {
  float firstTime, desiredFrameTime, frameTime;
  static float lastTime = 0.0;

  firstTime = glutGet(GLUT_ELAPSED_TIME);
  firstTime /= 1000.0;
  frameTime = firstTime - lastTime;
  desiredFrameTime = 1.0 / (float) (desiredFPS);
  if( frameTime <= desiredFrameTime)
      return;

  lastTime = firstTime;


  float xDirection = dx - circleX > 0 ? 1 : -1;
  float yDirection = dy - circleY > 0 ? 1 : -1;

  if(circleX != dx) {
    circleX += 5 * xDirection;
  }

  if(circleY != dy) {
    circleY += 5 * yDirection;
  }

  glutPostRedisplay();
}