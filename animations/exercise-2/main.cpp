#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "extras.h"

typedef struct POINTS {
  float x;
  float y;
} Point;

typedef struct SPHERE_OBJECT {
  Point center;
  float size;
  float xSpeed, ySpeed;
} SphereObject;

int width  = 1000;
int height = 500;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;
SphereObject sphere;
float gravity = -1.0f;
float desiredFPS = 60;

void idle();
void init(void);
void initSphere();
void display(void);
void reshape (int w, int h);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void updateSpeed(void);
void updatePosition(void);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow("Ball animation");
  init();
  initSphere();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}



void updateSpeed() {
  sphere.ySpeed += gravity;
  sphere.xSpeed *= 0.995f;
}

void updatePosition() {
  float new_y = sphere.center.y + sphere.ySpeed;
  float new_x = sphere.center.x + sphere.xSpeed;

  if (new_y < sphere.size) {
    new_y = sphere.size;
    sphere.ySpeed *= -1 * 0.9;
  }
  if (new_x < sphere.size) {
    new_x = sphere.size;
    sphere.xSpeed *= -1;
  } else if (new_x > width - sphere.size){
    new_x = width - sphere.size;
    sphere.xSpeed *= -1;
  }

  sphere.center = { new_x, new_y};
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

  updateSpeed();
  updatePosition();

  /* Update tLast for next time, using static local variable */
  lastTime = firstTime;

  glutPostRedisplay();
}

void init(void) {
  glClearColor (0.5, 0.5, 0.5, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
	initLight(width, height);
}

void initSphere() {
  sphere = {
    .center = { 40.0f, 470.0f },
    .size = 20.0f,
    .xSpeed = 5.0f,
    .ySpeed = 0.0f
  };
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
	glOrtho(0.0, width, 0.0, height, -sphere.size, sphere.size);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity ();

  setMaterial();

	glTranslatef(sphere.center.x, sphere.center.y, 0.0); // Posicionamento inicial da esfera
  glutSolidSphere(sphere.size, 100, 100);

  glutSwapBuffers();
}

void reshape (int w, int h) {
  width = w;
  height = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y) {
  if (tolower(key) == 27) {
    exit(0);
  } else if (key == 'r') {
    initSphere();
  } else if (key == ' ') {
    sphere.ySpeed = 30.0f;
    sphere.xSpeed += 5.0f * (sphere.xSpeed > 0 ? 1 : -1); //increases speed in the current direction
  }
}

// Motion callback
void motion(int x, int y ) {
  glutPostRedisplay();
}