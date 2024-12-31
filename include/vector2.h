#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2
{

public:
  float x, y;

  // Constructors
  Vector2();
  Vector2(float x, float y);

  float magnitude() const;
  float dot(const Vector2 &other);
  Vector2 normalize() const;
  float direction() const;
  Vector2 set_magnitude(float mag) const;
  Vector2 set_coordinates(float, float);
  Vector2 rotate(float angle) const;

  // Overloads
  Vector2 operator+(const Vector2 &other) const;
  Vector2 operator-(const Vector2 &other) const;
  Vector2 operator*(float scalar) const;
  Vector2 operator/(float scalar) const;
  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator*=(float scalar);
  Vector2 &operator/=(float scalar);
  bool operator==(const Vector2 &other) const;
  bool operator!=(const Vector2 &other) const;
  void print() const;
};

#endif // VECTOR2_H