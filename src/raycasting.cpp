#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "vector2.h"
#include "wall.h"
#include "ray_source.h"
#include "constants.h"

int mouse_x, mouse_y;
std::vector<Wall *> walls;
RaySource source;

void init()
{
  walls.clear();
  std::srand(std::time(0));
  glClearColor(0, 0, 0, 1.0);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (int i = 0; i < NO_OF_WALLS; i++)
  {
    int x1 = std::rand() % SCREEN_WIDTH;
    int y1 = std::rand() % SCREEN_HEIGHT;
    int x2 = std::rand() % SCREEN_WIDTH;
    int y2 = std::rand() % SCREEN_HEIGHT;
    walls.push_back(new Wall(x1, y1, x2, y2));
  }

  source = RaySource(Vector2(400, 300));
  source.vision_angle = 2 * M_PI;
  source.walls = walls;
  source.generate_rays();
}

void mouseMotion(int x, int y)
{
  mouse_x = x;
  mouse_y = SCREEN_HEIGHT - y;
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto &wall : walls)
  {
    wall->render();
  }
  source.update_position(Vector2(mouse_x, mouse_y));
  source.render();

  glutSwapBuffers();
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Ray Casting");

  init();

  glutPassiveMotionFunc(mouseMotion);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}