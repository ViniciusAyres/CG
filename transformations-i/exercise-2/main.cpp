#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, scale = 1.0;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;
float dx = xtrans,
      dy = ytrans;

float desiredFPS = 60;
int animationRunning = 0;

void idle(void);
void display(void);
void init (void);
void desenhaEixos();
void showMenu();
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
  glutInitWindowSize (300, 300);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("hello");
  glutMouseFunc( mouse );
  glutIdleFunc( idle);
  init ();
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    enableMenu = 1;
}

void showMenu() {
  int op;
  // system("clear");
  printf("\n=== MENU ===");
  printf("\n1 - Translacao");
  printf("\n2 - Rotacao");
  printf("\n3 - Escala");
  printf("\n4 - Sair");
  printf("\nOpcao: ");

  scanf("%d", &op);
  switch(op)
  {
    case 1:
      printf("\n\nInforme o vetor de translacao (entre -100.0 e 100.0)");
      printf("\nX : ");
      scanf("%f", &dx);
      printf("Y : ");
      scanf("%f", &dy);
      break;
    case 2:
      printf("\n\nInforme o angulo de rotacao (em graus): ");
      scanf("%f", &angle);
      break;
    case 3:
      printf("\n\nInforme o fator de escala: ");
      scanf("%f", &scale);
      break;
    case 4:
      exit(1);
      break;
    default:
      printf("\n\nOpcao invalida\n\n");
      break;
  }
}

void desenhaEixos() {
  glColor3f (0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex2f (0.0, -100.0);
    glVertex2f (0.0, 100.0);
    glVertex2f (-100.0, 0.0);
    glVertex2f (100.0, 0.0);
  glEnd();
}

void display(void) {
  // Limpar todos os pixels
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Inicializa com matriz identidade

  desenhaEixos();

  glColor3f (1.0, 0.0, 0.0);

  glPushMatrix();
    glTranslatef(xtrans, ytrans, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);
    glutWireCube(10);
  glPopMatrix();

  glutSwapBuffers ();
  glutPostRedisplay();

  if(animationRunning == 0){
    showMenu();
  }
}

void init (void) {
  // selecionar cor de fundo (preto)
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // inicializar sistema de viz.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void idle() {
  float firstTime, desiredFrameTime, frameTime;
  static float lastTime = 0.0;

  // Get elapsed time
  firstTime = glutGet(GLUT_ELAPSED_TIME);
  // convert milliseconds to seconds
  firstTime /= 1000.0;

  // Calculate frame time
  frameTime = firstTime - lastTime;
  // Calculate desired frame time
  desiredFrameTime = 1.0 / (float) (desiredFPS);

  // Check if the desired frame time was achieved. If not, skip animationRunning.
  if( frameTime <= desiredFrameTime)
      return;

  /*
    *UPDATE animationRunning VARIABLES
    */
  float xDirection = dx - xtrans > 0 ? 1 : -1;
  float yDirection = dy - ytrans > 0 ? 1 : -1;

  animationRunning = 0;
  if(xtrans != dx) {
    animationRunning = 1;
    xtrans += 1 * xDirection;
  }

  if(ytrans != dy) {
    animationRunning = 1;
    ytrans += 1 * yDirection;
  }

  /* Update tLast for next time, using static local variable */
  lastTime = firstTime;

  glutPostRedisplay();
}