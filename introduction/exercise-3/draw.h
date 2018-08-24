#include <GL/glut.h>

#define WINDOW_HEIGHT 200
#define WINDOW_WIDTH 200

void drawFirstQuadrant(void);
void drawSecondQuadrant(void);
void drawThirdQuadrant(void);
void drawFourthQuadrant(void);
void drawAxis(void);
void drawBorder(void);


void drawBorder(void)
{
  glLineWidth(3.0);
  glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_LINE_LOOP);
    glVertex2f(-WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, -WINDOW_HEIGHT);
    glVertex2f(-WINDOW_WIDTH, -WINDOW_HEIGHT);
  glEnd();
  glFlush();
}

void drawFirstQuadrant(void)
{
  //cria o viewport no primeiro quadrante
  glViewport (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
  drawBorder();
  
  //desenhar linha vertical vermelha
  glLineWidth(1.0);
  glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH + 30, -WINDOW_HEIGHT);
    glVertex2f(-WINDOW_WIDTH + 30, WINDOW_HEIGHT);
  glEnd();

  //desenha linha horizontal verde
  glLineWidth(1.0);
  glColor3f(0.0, 1.0, 0.0);

  glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH, -WINDOW_HEIGHT + 30);
    glVertex2f(WINDOW_WIDTH, -WINDOW_HEIGHT + 30);
  glEnd();

  //desenhar triangulo amarelo
  glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-140, -140.0);
    glVertex2f(-140, 40.0);
    glVertex2f(40, -140.0);
  glEnd();

  glFlush();
}