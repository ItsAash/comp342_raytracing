#ifndef RAY_SOURCE_H
#define RAY_SOURCE_H

#include "ray.h"
#include "wall.h"
#include "vector2.h"
#include "constants.h"
#include <vector>

class RaySource
{
public:
  Vector2 position;
  float base_angle = 0;
  Ray rays[NO_OF_RAYS];
  std::vector<Wall *> walls;
  float vision_angle = M_2_PI;

  // Constructors
  RaySource();
  RaySource(float vision_angle);
  explicit RaySource(Vector2 pos);

  // Methods
  void generate_rays();
  void update_rays_angle();
  void update_base_angle(float angle);
  void update_position(Vector2 pos);
  void render();
};

#endif // RAY_SOURCE_H