#include <GL/glut.h>

void drawBoard(float xMax, float yMax);
void drawCircle(int x, int y);

void drawBoard(float xMax, float yMax, int boardSpaces) {
  float xIncrement = xMax / boardSpaces;
  float yIncrement = yMax / boardSpaces;
  glLoadIdentity();
  glColor3f (1.0, 1.0, 1.0);

  for(int i = 0; i < boardSpaces; i++) {
    for(int j = 0; j < boardSpaces; j++) {
      if((i + j) % 2 == 0) {
        glRecti(i * xIncrement, j * yIncrement, (i+1) * xIncrement, (j+1) * yIncrement);
      }
    }
  }
}

void drawCircle(int x, int y) {
  glPushMatrix();
    glColor3f (1.0, 0.0, 0.0);
    glTranslatef(x, y, 0.0);
    glutSolidSphere(25, 100, 100);
  glPopMatrix();
}