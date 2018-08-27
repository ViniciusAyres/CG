#include <GL/glut.h>

#define WINDOW_HEIGHT 200
#define WINDOW_WIDTH 200

void drawFirstQuadrant(void);
void drawSecondQuadrant(void);
void drawThirdQuadrant(void);
void drawFourthQuadrant(void);
void drawAxis(void);
void drawBorder(void);


void drawBorder(double xMin, double xMax, double yMin, double yMax)
{
  glLineWidth(3.0);
  glColor3f(1.0, 0.45, 0.0);

  glBegin(GL_LINE_LOOP);
    glVertex2f(xMin, yMin);
    glVertex2f(xMax, yMin);
    glVertex2f(xMax, yMax);
    glVertex2f(xMin, yMax);
  glEnd();
  glFlush();
}

void drawFirstQuadrant(void)
{
  double xMin = -1.0,
    xMax = 6.0,
    yMin = -1.0,
    yMax = 6.0;

  //cria o viewport no primeiro quadrante
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport (200, 200, 190, 190);
  drawBorder(xMin, xMax, yMin, yMax);

  //desenhar linha vertical vermelha
  glLineWidth(1.0);
  glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_LINES);
    glVertex2f(0, -10);
    glVertex2f(0, 10);
  glEnd();

  //desenha linha horizontal verde
  glLineWidth(1.0);
  glColor3f(0.0, 1.0, 0.0);

  glBegin(GL_LINES);
    glVertex2f(-10, 0);
    glVertex2f(10, 0);
  glEnd();

  // //desenhar triangulo amarelo
  glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 5.0);
    glVertex2f(5.0, 1.0);
  glEnd();

  glFlush();
}