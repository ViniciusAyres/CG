#include <math.h>

typedef struct Points
{
  double x;
  double y;
} Point;

double degreesToRadians(double degrees);
Point *splitInterval(double begin, double end, int slices);

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