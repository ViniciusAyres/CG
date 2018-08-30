#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TRANSLATION 2
#define SCALATION 1.1
#define ROTATION 5

void drawAxis(void);
void display(void);
void init(void);
void keyboard(unsigned char key, int x, int y);

float angle = 0.0, scale = 1.0;
float X = 0.0, Y = 0.0;

main(int argc, char **argv) {
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void drawAxis(void) {
  glColor3f (0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex2f (0.0, -100.0);
    glVertex2f (0.0, 100.0);
    glVertex2f (-100.0, 0.0);
    glVertex2f (100.0, 0.0);
  glEnd();
}

void display(void) {
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawAxis();
  glPushMatrix();
    glTranslatef(X, Y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);
    glutWireCube(10);
  glPopMatrix();

  glutSwapBuffers ();
  glutPostRedisplay();
}

void init (void) {
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("hello");
  glutKeyboardFunc(keyboard);

  // selecionar cor de fundo (preto)
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // inicializar sistema de viz.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      Y += TRANSLATION;
      break;
    case 's':
      Y -= TRANSLATION;
      break;
    case 'd':
      X += TRANSLATION;
      break;
    case 'a':
      X -= TRANSLATION;
      break;
    case '+':
      scale *= SCALATION;
      break;
    case '-':
      scale /= SCALATION;
      break;
  }
}