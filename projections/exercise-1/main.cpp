#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int squareSide = 12;
float rotationX = 25.0, rotationY = 0.0;
int last_x, last_y;
int width = 1200, height = 480;

int distOrigem = 45;

void init(void);
void display(void) ;
void idle(void);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void mouse(int button, int state, int x, int y);
void drawGrid(float xMin, float xStep, float xMax, float zMin, float zStep, float zMax);
void drawCube(float x, float z);
void reshape(int w, int h);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (width, height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc( mouse );
  glutMotionFunc( motion );
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

void init(void) {
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  glEnable(GL_LIGHT0);                   // habilita luz 0
  glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
  glColorMaterial(GL_FRONT, GL_DIFFUSE);

  glEnable(GL_LIGHTING);                 // Habilita luz
  glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
  glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

  glutSetWindowTitle("3D Board");
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(70.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt (0.0, 30.0, 0, 0.0, 0.0, 25.0, 0.0, 1.0, 0.0);

  drawGrid(-30, squareSide, 30, 6, squareSide, 66);

  drawCube(0, 36);

  glutSwapBuffers();
}

void drawCube(float x, float z) {

  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(x , squareSide/2, z);
    glutSolidCube(squareSide);
  glPopMatrix();
}

void drawGrid(float xMin, float xStep, float xMax, float zMin, float zStep, float zMax) {

  glPushMatrix();
    glColor3f (1.0, 1.0, 1.0);
    for(float i = xMin; i < xMax; i = i + xStep) {
      for(float j = zMin; j < zMax; j = j + zStep) {
        glBegin(GL_LINE_LOOP);
          glVertex3f(i, 0, j);
          glVertex3f(i + xStep, 0, j);
          glVertex3f(i + xStep, 0, j + zStep);
          glVertex3f(i, 0, j + zStep);
        glEnd();
      }
    }
  glPopMatrix();
}

void idle () {
  glutPostRedisplay();
}

void reshape (int w, int h) {
  width = w;
  height = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y) {
  switch (tolower(key))
  {
    case '+' :
      distOrigem--;
      if(distOrigem<20) distOrigem=20;
    break;
    case '-' :
      distOrigem++;
      if(distOrigem>180) distOrigem=180;
    break;
    case 27:
      exit(0);
    break;
  }
}

// Motion callback
void motion(int x, int y ) {
  rotationX += (float) (y - last_y);
  rotationY += (float) (x - last_x);

  last_x = x;
  last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
}