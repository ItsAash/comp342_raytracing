#ifndef RAY_SOURCE_H
#define RAY_SOURCE_H

#include "ray.h"
#include "wall.h"
#include "vector2.h"
#include "constants.h"

class RaySource
{
public:
  Vector2 position;
  Ray rays[NO_OF_RAYS];
  Wall *walls;

  // Constructors
  RaySource();
  explicit RaySource(Vector2 pos);

  // Methods
  void generate_rays();
  void update_position(Vector2 pos);
  void render(int wall_count);
};

#endif // RAY_SOURCE_H