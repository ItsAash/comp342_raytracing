#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vector2.h"
#include "wall.h"
#include "ray_source.h"
#include "constants.h"
#include "map.h"

int mouse_x, mouse_y;
void specialKey(int key, int x, int y);
void mouse_handler(int x, int);

Map *map;

void init()
{
  std::srand(std::time(0));
  glClearColor(0, 0, 0, 1.0);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutSpecialFunc(specialKey);
  glutPassiveMotionFunc(mouse_handler);

  map = new Map(5, 5, 25); // Small 2D grid
  map->raySource.generate_rays();
  map->init();
}

void display()
{
  // Clear the screen and depth buffer once
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  map->generate_3D_World();
  map->render_3D();

  // Render 2D Map
  glViewport(0, 0, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4); // Bottom-left corner for 2D map
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, SCREEN_WIDTH / 4, 0, SCREEN_HEIGHT / 4);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  map->render_2D();

  glutSwapBuffers(); // Display final result
}

void specialKey(int key, int x, int y)
{
  map->keyboard_callback(key); // Handle key press
  glutPostRedisplay();         // Request display update
}

void mouse_handler(int x, int y)
{
  mouse_x = x;
  mouse_y = y;
  map->mouse_callback(x);
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("Maze");

  init();

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}