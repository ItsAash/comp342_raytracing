#include <GL/freeglut.h>
#include "vector2.h"
#include "wall.h"

Wall::Wall() {}
Wall::Wall(int x1, int y1, int x2, int y2)
{
  start.set_coordinates(x1, y1);
  end.set_coordinates(x2, y2);
}

void Wall::render()
{
  // Set up the color for the lines (White)
  glColor3f(1.0f, 1.0f, 1.0f);

  // Draw the lines
  glBegin(GL_LINES);

  glVertex2f(start.x, start.y); // Line segment start
  glVertex2f(end.x, end.y);     // Line segment end

  glEnd();
}