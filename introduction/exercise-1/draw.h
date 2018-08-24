#include <GL/glut.h>

#define WINDOW_HEIGHT 5
#define WINDOW_WIDTH 5

void drawAxis(void);
void drawTriangle(void);
void drawEmptyTriangle(void);
void drawBothTriangles(void);
void drawSemiHexagon(void);
void clearScreen(void);

void clearScreen(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawAxis();
  glFlush();
}

void drawAxis(void)
{
  glLineWidth(1.0);
  glColor3f(0.0, 0.0, 0.0);

  glBegin(GL_LINES);
  glVertex2f(-WINDOW_WIDTH, 0.0);
  glVertex2f(WINDOW_WIDTH, 0.0);
  glEnd();

  glBegin(GL_LINES);
  glVertex2f(0.0, -WINDOW_HEIGHT);
  glVertex2f(0.0, WINDOW_HEIGHT);
  glEnd();
  glFlush();
}

void drawTriangle(void)
{
  clearScreen();
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(2, 4);
  glVertex2f(4, 0);
  glEnd();
  glFlush();
}

void drawEmptyTriangle(void)
{
  clearScreen();
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(2, 4);
  glVertex2f(4, 0.0);
  glEnd();
  glFlush();
}

void drawBothTriangles(void)
{
  clearScreen();
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(2, 4);
  glVertex2f(4, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(0.0, 0.0);
  glVertex2f(-2, -4);
  glVertex2f(-4, 0.0);
  glEnd();
  glFlush();
}

void drawSemiHexagon(void)
{
  clearScreen();
  glBegin(GL_LINE_STRIP);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(2, 4);
  glVertex2f(4, 0.0);
  glVertex2f(2, -4);
  glVertex2f(-2, -4);
  glVertex2f(-4, 0.0);
  glVertex2f(-2, 4);
  glEnd();
  glFlush();
}
