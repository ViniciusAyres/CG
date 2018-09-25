#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100.0f
#define X_COLISION 1
#define Y_COLISION 2

float xSpeed = 0.5f;
float ySpeed = 0.5f;
float xPosition = 0.0f;
float yPosition = 0.0f;
float desiredFPS = 60;

typedef struct POINTS {
  float x;
  float y;
} point;

int colision(point triangle[3]);
void idle(void);
void display(void);
void init(void);

int colision(point triangle[3]) {
  for(int i = 0; i < 3; i++) {
    if(triangle[i].x >= MAX && xSpeed > 0) {
      return X_COLISION;
    } else if(triangle[i].x <= 0.0f && xSpeed < 0) {
      return -X_COLISION;
    } else if(triangle[i].y >= MAX && ySpeed > 0) {
      return Y_COLISION;
    } else if( triangle[i].y <= 0.0f && ySpeed < 0) {
      return -Y_COLISION;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  point triangle[3] = { {10.0f + xPosition, 10.0f + yPosition},
                        {30.0f + xPosition, 50.0f + yPosition},
                        {45.0f + xPosition, 20.0f + yPosition} };

  int crashed = colision(triangle);
  if(crashed == X_COLISION) {
    xSpeed = -0.5f;
  } else if(crashed == -X_COLISION) {
    xSpeed = 0.5f;
  } else if(crashed == Y_COLISION) {
    ySpeed = -0.5f;
  } else if(crashed == -Y_COLISION) {
    ySpeed = 0.5f;
  }

  glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(triangle[0].x, triangle[0].y, 0);
    glVertex3f(triangle[1].x, triangle[1].y, 0);
    glVertex3f(triangle[2].x, triangle[2].y, 0);
  glEnd();

  glutSwapBuffers ();
  glutPostRedisplay();
}

void init (void) {
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("triangles");

  // selecionar cor de fundo (preto)
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, MAX, 0.0, MAX, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle() {
  float firstTime, desiredFrameTime, frameTime;
  static float lastTime = 0.0;

  // Get elapsed time
  firstTime = glutGet(GLUT_ELAPSED_TIME);
  // convert milliseconds to seconds
  firstTime /= 1000.0;

  // Calculate frame time
  frameTime = firstTime - lastTime;
  // Calculate desired frame time
  desiredFrameTime = 1.0 / (float) (desiredFPS);

  // Check if the desired frame time was achieved. If not, skip animationRunning.
  if( frameTime <= desiredFrameTime)
      return;

  xPosition += xSpeed;
  yPosition += ySpeed;

  /* Update tLast for next time, using static local variable */
  lastTime = firstTime;

  glutPostRedisplay();
}