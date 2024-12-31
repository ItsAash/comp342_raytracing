#!/bin/bash

# Set the compiler and flags
CXX=g++
CXXFLAGS="-std=c++11 -I/opt/homebrew/opt/freeglut/include -I./include"
LDFLAGS="-L/opt/homebrew/opt/freeglut/lib -framework OpenGL -lglut"

# List of source files
SOURCES="src/ray.cpp src/intersection.cpp src/vector2.cpp src/ray_source.cpp src/raycasting.cpp src/wall.cpp"
OUTPUT="builds/two"

# Compile and link
$CXX $CXXFLAGS $SOURCES -o $OUTPUT $LDFLAGS

# Run the program
if [ $? -eq 0 ]; then
  echo "Compilation successful. Running the program..."
  ./$OUTPUT
else
  echo "Compilation failed."
fi