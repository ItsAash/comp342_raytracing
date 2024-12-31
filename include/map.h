#ifndef MAP_H
#define MAP_H

#include <vector>
#include "vector2.h"
#include "wall.h"
#include "vertex3.h"
#include "ray_source.h"
#include "constants.h"
#define PI 3.141592

class Map
{
public:
  int width;                               // Map width (in grid cells)
  int height;                              // Map height (in grid cells)
  int cellSize;                            // Size of each cell (in pixels)
  std::vector<Wall *> walls;               // Collection of walls for the map
  std::vector<std::vector<Vertex3>> quads; // Collection of quads for the 3D world
  RaySource raySource;                     // Ray source for tracing

  // Constructor
  Map();
  Map(int width, int height, int cellSize);

  void init();
  void keyboard_callback(int key);
  void mouse_callback(int x);

  // Generate a simple grid-based maze
  void generate_maze();

  // Generate a 3D world based on ray tracing
  void generate_3D_World();

  // Render the 2D map
  void render_2D();

  // Render the 3D world
  void render_3D();
};

#endif // MAP_H