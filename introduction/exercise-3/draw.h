#include <GL/glut.h>

#define WINDOW_HEIGHT 200
#define WINDOW_WIDTH 200

typedef struct Quadrants
{
  int x;
  int y;
} Quadrant;

typedef struct Colors
{
  double red;
  double green;
  double blue;
} Color;

void drawFirstQuadrant(void);
void drawSecondQuadrant(void);
void drawThirdQuadrant(void);
void drawFourthQuadrant(void);
void drawTriangle(Quadrant quadrant, Color color);
void drawEmptyTriangle(Quadrant quadrant, Color color);
void drawZLine(Quadrant quadrant, Color color);
void drawAxis(void);
void drawBorder(void);

void drawAxis(void)
{
  glLineWidth(1.0);
  glBegin(GL_LINES);
    //desenhar linha vertical vermelha
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0, -10000);
    glVertex2f(0, 10000);
    
    //desenhar linha horizontal verde
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-10000, 0);
    glVertex2f(10000, 0);
  glEnd();
}

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

void drawTriangle(Quadrant quadrant, Color color)
{
  glBegin(GL_POLYGON);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 1.0);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 5.0);
    glVertex2f(quadrant.x * 5.0, quadrant.y * 1.0);
  glEnd();
}

void drawEmptyTriangle(Quadrant quadrant, Color color)
{
  glBegin(GL_LINE_LOOP);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 1.0);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 5.0);
    glVertex2f(quadrant.x * 5.0, quadrant.y * 1.0);
  glEnd();
}

void drawZLine(Quadrant quadrant, Color color)
{
  glBegin(GL_LINE_STRIP);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(quadrant.x * 5.0, quadrant.y * 5.0);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 5.0);
    glVertex2f(quadrant.x * 5.0, quadrant.y * 1.0);
    glVertex2f(quadrant.x * 1.0, quadrant.y * 1.0);
  glEnd();
}

void drawFirstQuadrant(void)
{
  double xMin = -1.0,
    xMax = 6.0,
    yMin = -1.0,
    yMax = 6.0;
  Quadrant quadrant = {1, 1};
  Color color = {1.0, 1.0, 0.0};

  //cria o viewport no primeiro quadrante
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport (200, 200, 190, 190);

  // drawBorder(xMin, xMax, yMin, yMax);
  drawAxis();
  drawTriangle(quadrant, color);

  glFlush();
}

void drawSecondQuadrant(void)
{
  double xMin = -6.0,
    xMax = 6.0,
    yMin = -6.0,
    yMax = 6.0;
  Quadrant firstQuadrant = {1, 1};
  Quadrant thirdQuadrant = {-1, -1};
  Quadrant fourthQuadrant = {1, -1};
  Color triangleColor = {1.0, 1.0, 0.0};
  Color zLineColor = {1.0, 0.0, 1.0};
  Color emptyTriangleColor = {0.0, 1.0, 1.0};

  //cria o viewport no primeiro quadrante
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport (5, 200, 190, 190);

  // drawBorder(xMin, xMax, yMin, yMax);
  drawAxis();
  drawTriangle(firstQuadrant, triangleColor);
  drawEmptyTriangle(fourthQuadrant, emptyTriangleColor);
  drawZLine(thirdQuadrant, zLineColor);

  glFlush();
}

void drawThirdQuadrant(void)
{
  double xMin = -6.0,
    xMax = 1.0,
    yMin = -6.0,
    yMax = 1.0;
  Quadrant quadrant = {-1, -1};
  Color color = {1.0, 0.0, 1.0};

  //cria o viewport no primeiro quadrante
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport (5, 10, 190, 185);

  // drawBorder(xMin, xMax, yMin, yMax);
  drawAxis();
  drawZLine(quadrant, color);

  glFlush();
}

void drawFourthQuadrant(void)
{
  double xMin = -1.0,
    xMax = 6.0,
    yMin = -6.0,
    yMax = 1.0;
  Quadrant quadrant = {1, -1};
  Color color = {0.0, 1.0, 1.0};

  //cria o viewport no primeiro quadrante
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport (200, 10, 190, 185);

  // drawBorder(xMin, xMax, yMin, yMax);
  drawAxis();
  drawEmptyTriangle(quadrant, color);

  glFlush();
}