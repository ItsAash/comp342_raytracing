#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector2.h"
#include "wall.h"
#include "ray.h"

bool checkIntersection(const Ray &ray, const Wall &wall, Vector2 &intersectionPoint);

#endif // INTERSECTION_H