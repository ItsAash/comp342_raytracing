#include "ray.h"
#include "wall.h"
#include "constants.h"
#include "intersection.h"
#include <cmath>
#include <vector>
#include <iostream>

void draw_circle(Vector2 center, float radius, float alpha, float red = 1.0f, float green = 1.0f, float blue = 1.0f)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set color with transparency
  glColor4f(red, green, blue, alpha);

  // Draw the circle
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(center.x, center.y); // Center of the circle

  // Smaller step size for smoother circle
  for (int angle = 0; angle <= 360; angle += 1)
  {
    float radian = angle * M_PI / 180.0f;
    float x = radius * cos(radian) + center.x;
    float y = radius * sin(radian) + center.y;
    glVertex2f(x, y);
  }
  glEnd();

  glDisable(GL_BLEND);
}

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

void Ray::check_walls_intersect(std::vector<Wall *> walls)
{
  intersect_distance = std::sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT); // Reset to max
  for (int i = 0; i < walls.size(); i++)
  {
    Vector2 intersection_point;
    if (checkIntersection(*this, *walls[i], intersection_point))
    {
      float distance = (intersection_point - origin).magnitude();
      if (distance < intersect_distance)
      {
        intersect_distance = distance;
      }
    }
  }
}

Vector2 Ray::get_intersection_point()
{
  return origin + direction.normalize() * intersect_distance;
}

void Ray::show_ray_lines(bool show_intersection)
{
  Vector2 endpoint = get_intersection_point();

  // Draw ray line
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex2f(origin.x, origin.y);
  glVertex2f(endpoint.x, endpoint.y);
  glEnd();

  if (show_intersection)
  {
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(endpoint.x, endpoint.y);
    glEnd();
  }
}
