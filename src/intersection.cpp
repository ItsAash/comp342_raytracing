#include "intersection.h"
#include "ray.h"
#include "wall.h"
bool checkIntersection(const Ray &ray, const Wall &wall, Vector2 &intersectionPoint)
{
  Vector2 rayDirection = ray.direction.normalize(); // Ensure ray direction is normalized
  Vector2 wallStart = wall.start;
  Vector2 wallEnd = wall.end;
  Vector2 wallDirection = wallEnd - wallStart;

  float det = rayDirection.x * wallDirection.y - rayDirection.y * wallDirection.x;
  if (fabs(det) < 1e-6)
  {
    return false; // Parallel or coincident lines
  }

  Vector2 diff = wallStart - ray.origin;
  float t = (diff.x * wallDirection.y - diff.y * wallDirection.x) / det; // Along the ray
  float u = (diff.x * rayDirection.y - diff.y * rayDirection.x) / det;   // Along the wall segment

  Vector2 displacement = rayDirection * t;
  if (t >= 0 && u >= 0 && u <= 1)
  {
    intersectionPoint = ray.origin + displacement;

    return true;
  }
  return false; // No intersection
}