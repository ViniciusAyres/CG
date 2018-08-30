#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void drawAxis(void);
void display(void);
void init(void);

float angle = 0.0, scale = 1.0;
float x = 0.0, y = 0.0;

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

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  drawAxis();
  glutWireCube(10);

  glutSwapBuffers ();
  glutPostRedisplay();
}

void init (void)
{
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("hello");

  // selecionar cor de fundo (preto)
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // inicializar sistema de viz.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}