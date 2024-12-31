#include "map.h"
#include "wall.h"
#include "constants.h"
#include "ray_source.h"
#include "vertex3.h"
#include <vector>
#include <cstdlib>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

#define PI 3.141592

int left_offset = 20;

// Constructor
Map::Map() {}

Map::Map(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), raySource(Vector2((width * cellSize) / 2 + left_offset, height * cellSize / 2)) {}

void Map::init()
{
  // Generate a simple grid-based maze
  generate_maze();
  raySource.vision_angle = PI / 3;
  raySource.generate_rays();
}

// Generate a grid-based maze
void Map::generate_maze()
{
  walls.clear();

  // Create outer boundaries
  walls.push_back(new Wall(left_offset, 0, width * cellSize + left_offset, 0));                                    // Top wall
  walls.push_back(new Wall(left_offset, 0, left_offset, height * cellSize));                                       // Left wall
  walls.push_back(new Wall(left_offset, height * cellSize, width * cellSize + left_offset, height * cellSize));    // Bottom wall
  walls.push_back(new Wall(width * cellSize + left_offset, 0, width * cellSize + left_offset, height * cellSize)); // Right wall

  // Add internal walls
  for (int y = 1; y < height; y++)
  {
    for (int x = 1; x < width; x++)
    {
      if (std::rand() % 2 == 0)
      { // Random vertical walls
        walls.push_back(new Wall(x * cellSize + left_offset, y * cellSize, x * cellSize + left_offset, (y - 1) * cellSize));
      }
      if (std::rand() % 2 == 0)
      { // Random horizontal walls
        walls.push_back(new Wall(x * cellSize + left_offset, y * cellSize, (x - 1) * cellSize + left_offset, y * cellSize));
      }
    }
  }

  // Assign walls to the ray source
  raySource.walls = walls;
}

void Map::mouse_callback(int x)
{
  // update the base angle of the ray by mapping the mouse x from 0 to screen width to 0 to 2 * pi
  float angle = (x * 2 * PI) / SCREEN_WIDTH;
  raySource.update_base_angle(angle);
}

void Map::keyboard_callback(int key)
{
  // Define boundaries for the ray source
  float minX = left_offset;                    // Minimum X boundary (left wall)
  float maxX = left_offset + width * cellSize; // Maximum X boundary (right wall)
  float minY = 0.0f;                           // Minimum Y boundary (bottom wall)
  float maxY = height * cellSize;              // Maximum Y boundary (top wall)

  Vector2 newPosition = raySource.position; // Start with the current position

  // Calculate the middle ray direction
  int middleRayIndex = NO_OF_RAYS / 2; // Index of the middle ray
  Vector2 direction = raySource.rays[middleRayIndex].direction;

  // Normalize the direction vector to ensure uniform movement
  direction = direction.normalize();

  // Determine movement step size
  float stepSize = width * cellSize / 20; // Adjust step size as needed

  switch (key)
  {
  case GLUT_KEY_UP: // Move ray source forward
    newPosition += direction * stepSize;
    break;
  case GLUT_KEY_DOWN: // Move ray source backward
    newPosition -= direction * stepSize;
    break;
  case GLUT_KEY_LEFT:                                             // Strafe left
    newPosition += Vector2(-direction.y, direction.x) * stepSize; // Perpendicular to direction
    break;
  case GLUT_KEY_RIGHT:                                            // Strafe right
    newPosition += Vector2(direction.y, -direction.x) * stepSize; // Perpendicular to direction
    break;
  default:
    break;
  }

  // Clamp the new position within the boundaries
  newPosition.x = std::max(minX, std::min(newPosition.x, maxX));
  newPosition.y = std::max(minY, std::min(newPosition.y, maxY));

  // Update the ray source's position
  raySource.update_position(newPosition);
}
void Map::generate_3D_World()
{
  // Clear the quads for the new frame
  quads.clear();

  // Loop through each ray
  for (int i = 0; i < NO_OF_RAYS; i++)
  {
    Ray &ray = raySource.rays[i];

    // Calculate the screen width for each slice (quad) based on the number of rays
    float sliceWidth = SCREEN_WIDTH / NO_OF_RAYS;

    // Calculate the screen position for this slice
    float screenX = SCREEN_WIDTH - (i + 1) * sliceWidth; // Map the first ray to the rightmost part of the screen

    // Determine the height of the wall based on the distance
    float wallHeight = 10.0f * SCREEN_HEIGHT / ray.intersect_distance;

    // Define the top and bottom Y-coordinates for the wall
    float topY = (SCREEN_HEIGHT / 2) - (wallHeight / 2);    // Centered vertically
    float bottomY = (SCREEN_HEIGHT / 2) + (wallHeight / 2); // Centered vertically

    // Create the vertices of the quad
    Vertex3 topLeft(screenX, topY, ray.intersect_distance);
    Vertex3 topRight(screenX + sliceWidth, topY, ray.intersect_distance);
    Vertex3 bottomLeft(screenX, bottomY, ray.intersect_distance);
    Vertex3 bottomRight(screenX + sliceWidth, bottomY, ray.intersect_distance);

    // Add the quad to the list
    std::vector<Vertex3> quad = {topLeft, topRight, bottomRight, bottomLeft};
    quads.push_back(quad);
  }
}

// Render the 2D map
void Map::render_2D()
{
  // Draw walls
  for (Wall *wall : walls)
  {
    wall->render();
  }

  raySource.render();
}

void Map::render_3D()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);

  // Set up a 2D orthographic view for the full screen
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Render ground and sky
  glBegin(GL_QUADS);
  // Ground
  glColor4f(0.0f, 0.5f, 0.0f, 1.0f); // Greenish color
  glVertex2f(0, 0);
  glVertex2f(SCREEN_WIDTH, 0);
  glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
  glVertex2f(0, SCREEN_HEIGHT / 2);

  // Sky
  glColor4f(0.5f, 0.7f, 1.0f, 1.0f); // Blueish color
  glVertex2f(0, SCREEN_HEIGHT / 2);
  glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
  glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
  glVertex2f(0, SCREEN_HEIGHT);
  glEnd();

  // Render walls
  for (std::vector<Vertex3> &quad : quads)
  {
    float distance = quad[0].z;

    // Calculate brightness based on distance
    float intensity = std::max(0.2f, 1.0f / (distance * distance)); // Fade with distance
    glColor4f(0.5f, 0.5f, 0.5f, intensity);

    glBegin(GL_QUADS);
    // Draw the 2D quad (rectangle)
    glVertex2f(quad[0].x, quad[0].y); // Top-left
    glVertex2f(quad[1].x, quad[1].y); // Top-right
    glVertex2f(quad[2].x, quad[2].y); // Bottom-right
    glVertex2f(quad[3].x, quad[3].y); // Bottom-left
    glEnd();
  }

  glFlush();
}