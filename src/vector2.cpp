#include <iostream>
#include <cmath>
#include "vector2.h"

// Constructors
Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

// Magnitude
float Vector2::magnitude() const
{
  return std::sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2 &other)
{
  return this->x * other.x + this->y * other.y;
}

Vector2 Vector2::set_coordinates(float p, float q)
{
  x = p;
  y = q;
  return *this;
}

// Normalize (unit vector)
Vector2 Vector2::normalize() const
{
  float mag = magnitude();
  return (mag > 0) ? Vector2(x / mag, y / mag) : Vector2(0, 0);
}

// Direction (angle in radians)
float Vector2::direction() const
{
  return std::atan2(y, x);
}

// Set magnitude (scale vector to desired magnitude)
Vector2 Vector2::set_magnitude(float mag) const
{
  return normalize() * mag;
}

// Rotate vector by an angle (in radians)
Vector2 Vector2::rotate(float angle) const
{
  float cosA = std::cos(angle);
  float sinA = std::sin(angle);
  return Vector2(x * cosA - y * sinA, x * sinA + y * cosA);
}

// Overloaded Operators
Vector2 Vector2::operator+(const Vector2 &other) const
{
  return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
  return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const
{
  return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
  return (scalar != 0) ? Vector2(x / scalar, y / scalar) : Vector2(0, 0);
}

Vector2 &Vector2::operator+=(const Vector2 &other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector2 &Vector2::operator*=(float scalar)
{
  x *= scalar;
  y *= scalar;
  return *this;
}

Vector2 &Vector2::operator/=(float scalar)
{
  if (scalar != 0)
  {
    x /= scalar;
    y /= scalar;
  }
  return *this;
}

// Equality Operators
bool Vector2::operator==(const Vector2 &other) const
{
  return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2 &other) const
{
  return !(*this == other);
}

// Utility Functions
void Vector2::print() const
{
  std::cout << "Vector2(" << x << ", " << y << ")\n";
}