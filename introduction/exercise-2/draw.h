#include <GL/glut.h>
#include <stdio.h>

#include "math_operations.h"

void drawAxis(void);
void drawSinPoints(int numberOfPoints);

void drawAxis(void)
{
  glLineWidth(1.0);
  glColor3f(1.0, 1.0, 1.0);

  glBegin(GL_LINES);
    glVertex2f(-0.5, 0.0);
    glVertex2f(7, 0.0);
  glEnd();

  glBegin(GL_LINES);
    glVertex2f(0.0, -1.5);
    glVertex2f(0.0, 1.5);
  glEnd();

  glFlush();
}

void drawSinPoints(int slices)
{
  glClear(GL_COLOR_BUFFER_BIT);
  Point *points = splitInterval(0, 360, slices);

  drawAxis();

  //Desenha reta
  glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    
    for(int i = 0; i < slices; i++)
    {
      printf("[%d] x: %lf, y: %lf\n", i, points[i].x, points[i].y);
      glVertex2f(points[i].x, points[i].y);
    }
  glEnd();
  
  glFlush();
}