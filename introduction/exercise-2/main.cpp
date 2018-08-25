#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

typedef struct Points
{
  double x;
  double y;
} Point;

void init(void)
{
  int windowWidth = 400,
      windowHeight = 400;

  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Exercise 2");
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  gluOrtho2D(-0.5, 7, -1.5, 1.5);
}

double degreesToRadians(double degrees)
{
  return degrees * (M_PI / 180);
}

Point *splitInterval(double begin, double end, int slices)
{
  double interval = (end - begin) / (slices - 1);
  Point *slicesArray = (Point *)malloc(sizeof(Point) * slices);

  double acumulator = 0;
  double radians;
  for (int i = 0; i < slices; i++)
  {
    radians = degreesToRadians(acumulator);
    slicesArray[i].x = radians;
    slicesArray[i].y = sin(radians);
    acumulator += interval;
  }

  return slicesArray;
}

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
  Point *slicesArray = splitInterval(0, 360, slices);

  //Desenha eixos
  drawAxis();

  //Desenha reta
  glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    
    for(int i = 0; i < slices; i++)
    {
      printf("[%d] x: %lf, y: %lf\n", i, slicesArray[i].x, slicesArray[i].y);
      glVertex2f(slicesArray[i].x, slicesArray[i].y);
    }
  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  int slices = 3600;

  glutInit(&argc, argv);
  init();
  drawSinPoints(slices);
  glutMainLoop();
}