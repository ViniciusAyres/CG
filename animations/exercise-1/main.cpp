#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100.0f
#define X_COLISION 1
#define Y_COLISION 2
#define N_TRIANGLES 2

float xSpeed = 0.5f;
float ySpeed = 0.5f;
float xPosition = 0.0f;
float yPosition = 0.0f;
float desiredFPS = 60;

typedef struct POINTS {
  float x;
  float y;
} point;

typedef struct Colors {
  float red, green, blue;
} Colors;

typedef struct TriangleObject {
  point points[3];

  double xSpeed, ySpeed;
} TriangleObject;

TriangleObject triangles[N_TRIANGLES];

int colision(TriangleObject triangleObject);
void idle(void);
void display(void);
void init(void);
void initializeTriangles(void);
void drawTriangle(point points[3], Colors colors);
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

  for(int i = 0; i < N_TRIANGLES; i++) {
    int crashed = colision(triangles[i]);
    if(crashed == X_COLISION) {
      triangles[i].xSpeed = -0.5f;
    } else if(crashed == -X_COLISION) {
      triangles[i].xSpeed = 0.5f;
    } else if(crashed == Y_COLISION) {
      triangles[i].ySpeed = -0.5f;
    } else if(crashed == -Y_COLISION) {
      triangles[i].ySpeed = 0.5f;
    }
  }

  Colors colors = { 0.0f, 1.0f, 0.0f };
  drawTriangle(triangles[0].points, colors);

  colors = { 1.0f, 0.0f, 0.0f };
  drawTriangle(triangles[1].points, colors);

  glutSwapBuffers ();
  glutPostRedisplay();
}

void drawTriangle(point points[3], Colors colors) {
  glBegin(GL_LINE_LOOP);
    glColor3f(colors.red, colors.green, colors.blue);
    glVertex3f(points[0].x, points[0].y, 0);
    glVertex3f(points[1].x, points[1].y, 0);
    glVertex3f(points[2].x, points[2].y, 0);
  glEnd();
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

  triangles[1] = {
    .points = {
      { 40.0f, 40.0f },
      { 85.0f, 45.0f },
      { 60.0f, 75.0f }
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
  for(int i = 0; i < N_TRIANGLES; i++) {
    triangles[i] = updatePosition(triangles[i]);
  }

  /* Update tLast for next time, using static local variable */
  lastTime = firstTime;

  glutPostRedisplay();
}