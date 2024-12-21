#include "ray_source.h"
#include <GL/freeglut.h>
#include <cmath>

#define PI 3.141592

RaySource::RaySource() : position(Vector2(0, 0)), walls(nullptr) {}

RaySource::RaySource(Vector2 pos) : position(pos), walls(nullptr)
{
  generate_rays();
}

void RaySource::generate_rays()
{
  float angle_increment = (2 * PI) / NO_OF_RAYS;
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    float angle = i * angle_increment;
    rays[i] = Ray(position);
    rays[i].set_direction(angle);
  }
}

void RaySource::update_position(Vector2 pos)
{
  position = pos;
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    rays[i].update_origin(pos);
  }
}

void RaySource::render(int wall_count)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    rays[i].check_walls_intersect(walls, wall_count);

    // Draw ray line
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    glBegin(GL_LINES);
    glVertex2f(rays[i].origin.x, rays[i].origin.y);
    Vector2 endpoint = rays[i].origin + rays[i].direction.normalize() * rays[i].intersect_distance;
    glVertex2f(endpoint.x, endpoint.y);
    glEnd();

    // Draw intersection point
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(endpoint.x, endpoint.y);
    glEnd();
  }
  glDisable(GL_BLEND);
}