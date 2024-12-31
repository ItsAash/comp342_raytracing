#include "ray_source.h"
#include <GL/freeglut.h>
#include <cmath>

RaySource::RaySource() : position(Vector2(0, 0)), walls() {}

RaySource::RaySource(Vector2 pos) : position(pos), walls() {}

RaySource::RaySource(float vision_angle) : vision_angle(vision_angle) {}

void RaySource::generate_rays()
{
  float angle_increment = vision_angle / NO_OF_RAYS;
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    float angle = base_angle + i * angle_increment;
    rays[i] = Ray(position);
    rays[i].set_direction(angle);
  }
}

void RaySource::update_rays_angle()
{
  float angle_increment = vision_angle / NO_OF_RAYS;
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    float angle = base_angle + i * angle_increment;
    rays[i].set_direction(angle);
  }
}

void RaySource::update_base_angle(float angle)
{
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    base_angle = angle;
  }
  update_rays_angle();
}

void RaySource::update_position(Vector2 pos)
{
  position = pos;
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    rays[i].update_origin(pos);
  }
}

void RaySource::render()
{
  // Render each ray with smooth circular light effects
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    rays[i].check_walls_intersect(walls);
    rays[i].show_ray_lines(true);
  }
}
