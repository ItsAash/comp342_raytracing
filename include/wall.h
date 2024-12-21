#ifndef WALL_H
#define WALL_H

#include <GL/freeglut.h>
#include "vector2.h"

class Wall
{
public:
  Vector2 start;
  Vector2 end;

  Wall();
  Wall(int x1, int y1, int x2, int y2);

  void render();
};

#endif // WALL_H