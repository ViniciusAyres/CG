#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100.0f
#define X_COLISION 1
#define Y_COLISION 2
#define N_TRIANGLES 1

float xSpeed = 0.5f;
float ySpeed = 0.5f;
float xPosition = 0.0f;
float yPosition = 0.0f;
float desiredFPS = 60;

typedef struct POINTS {
  float x;
  float y;
} point;

typedef struct TriangleObject {
  point points[3];

  double xSpeed, ySpeed;
} TriangleObject;

TriangleObject triangles[1];

int colision(TriangleObject triangleObject);
void idle(void);
void display(void);
void init(void);
void initializeTriangles(void);
TriangleObject updatePosition(TriangleObject triangleObject);

int colision(TriangleObject triangleObject) {
  for(int i = 0; i < 3; i++) {
    if(triangleObject.points[i].x >= MAX && triangleObject.xSpeed > 0) {
      return X_COLISION;
    } else if(triangleObject.points[i].x <= 0.0f && triangleObject.xSpeed < 0) {
      return -X_COLISION;
    } else if(triangleObject.points[i].y >= MAX && triangleObject.ySpeed > 0) {
      return Y_COLISION;
    } else if(triangleObject.points[i].y <= 0.0f && triangleObject.ySpeed < 0) {
      return -Y_COLISION;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  initializeTriangles();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  int crashed = colision(triangles[0]);
  if(crashed == X_COLISION) {
    triangles[0].xSpeed = -0.5f;
  } else if(crashed == -X_COLISION) {
    triangles[0].xSpeed = 0.5f;
  } else if(crashed == Y_COLISION) {
    triangles[0].ySpeed = -0.5f;
  } else if(crashed == -Y_COLISION) {
    triangles[0].ySpeed = 0.5f;
  }

  //TODO:Desenha triangulo()
  glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(triangles[0].points[0].x, triangles[0].points[0].y, 0);
    glVertex3f(triangles[0].points[1].x, triangles[0].points[1].y, 0);
    glVertex3f(triangles[0].points[2].x, triangles[0].points[2].y, 0);
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

void initializeTriangles() {
  triangles[0] = {
    .points = {
      { 10.0f, 10.0f },
      { 30.0f, 50.0f },
      { 45.0f, 20.0f }
    },
    .xSpeed = 0.5f,
    .ySpeed = 0.5f
  };
}

TriangleObject updatePosition(TriangleObject triangleObject) {
  TriangleObject modifiedTriangle = triangleObject;

  for(int i = 0; i < 3; i++) {
    modifiedTriangle.points[i].x += modifiedTriangle.xSpeed;
    modifiedTriangle.points[i].y += modifiedTriangle.ySpeed;
  }

  return modifiedTriangle;
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

  //updatePosition
  triangles[0] = updatePosition(triangles[0]);

  /* Update tLast for next time, using static local variable */
  lastTime = firstTime;

  glutPostRedisplay();
}