#include "ray.h"
#include "constants.h"
#include "intersection.h"
#include <cmath>

// Constructors
Ray::Ray() : origin(Vector2(0, 0)), direction(Vector2(0, 0))
{
  intersect_distance = std::sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT);
}

Ray::Ray(Vector2 origin) : origin(origin)
{
  intersect_distance = std::sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT);
}

void Ray::set_direction(float angle)
{
  direction = Vector2(std::cos(angle), std::sin(angle));
}

void Ray::update_origin(Vector2 pos)
{
  origin = pos;
}

void Ray::check_walls_intersect(Wall *walls, int wall_count)
{
  intersect_distance = std::sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT); // Reset to max
  for (int i = 0; i < wall_count; i++)
  {
    Vector2 intersection_point;
    if (checkIntersection(*this, walls[i], intersection_point))
    {
      float distance = (intersection_point - origin).magnitude();
      if (distance < intersect_distance)
      {
        intersect_distance = distance;
      }
    }
  }
}