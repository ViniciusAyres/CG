#include <GL/glut.h>

#define BOARD_SPACES 6

void drawBoard(float xMax, float yMax);

void drawBoard(float xMax, float yMax) {
  float xIncrement = xMax / BOARD_SPACES;
  float yIncrement = yMax / BOARD_SPACES;
  glLoadIdentity();
  glColor3f (1.0, 1.0, 1.0);

  for(int i = 0; i < BOARD_SPACES; i++) {
    for(int j = 0; j < BOARD_SPACES; j++) {
      if((i + j) % 2 == 0) {
        glRecti(i * xIncrement, j * yIncrement, (i+1) * xIncrement, (j+1) * yIncrement);
      }
    }
  }
}