#ifndef RAY_H
#define RAY_H

#include "vector2.h"
#include "wall.h"

class Ray
{
public:
  Vector2 origin;
  Vector2 direction;
  float intersect_distance;

  // Constructors
  Ray();
  Ray(Vector2 origin);

  // Methods
  void set_direction(float angle);
  void update_origin(Vector2 pos);
  void check_walls_intersect(Wall *walls, int wall_count);
};

#endif // RAY_H