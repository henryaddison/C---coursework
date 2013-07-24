/* This file will produce an execuable used to test the various parts of maze.cpp as I go */

#include <iostream>
#include "maze.h"

using namespace std;

/* a method to find and print out the location of the character marker in a given maze */
void testMarker(char marker, char **maze, int height, int width);

/* a method to test a given path really is a solution to a given height x width maze */
void testSolution(char *path, char **maze, int height, int width);

/* a method to test whether given coordinates are valid coordinates for a maze */
void testValidCoords(int row, int column, char **maze, int height, int width);

/* a function to test finding a path in the maze */
void testFindPath(char **maze, int height, int width);

int main() {
  int height, width;
  char **maze = load_maze("simple.txt", height, width);
  char *test_path;
  cout << "Height " << height << endl;
  cout << "Width " << width << endl;

  //if we look for X we should find it in row 7, column 8 of simple maze
  testMarker('X', maze, height, width);
  //if we look for Y we shouldn't find it anywhere
  testMarker('Y', maze, height, width);
  
  //expect the start marker coordinates to be valid
  testValidCoords(1, 0, maze, height, width);
  // and end marker
  testValidCoords(7, 8, maze, height, width);
  // and a selected corridor
  testValidCoords(1, 1, maze, height, width);
  //expect barriers to be invalid
  testValidCoords(0, 0, maze, height, width);
  testValidCoords(0, 1, maze, height, width);
  testValidCoords(3, 8, maze, height, width);

  // and outside maze coordinates
  testValidCoords(-1, 5, maze, height, width);
  testValidCoords(1, -2, maze, height, width);
  testValidCoords(1, 9, maze, height, width);
  testValidCoords(10, 5, maze, height, width);

  //expect the following to be a valid solution to simple maze
  test_path = "ESSSSSSEEEEEEE";
  testSolution(test_path, maze, height, width);
  //the following path should go outside the confines of the maze
  test_path = "WEESSSSSSEEEEEEE";
  testSolution(test_path, maze, height, width);
  //the following does not end up at the end
  test_path = "ESSSSSSEEEEEEEN";
  testSolution(test_path, maze, height, width);
  //the following goes through hedge
  test_path = "EEEEEEEESSSSSS";
  testSolution(test_path, maze, height, width);

  //expect this to produce a valid solution
  testFindPath(maze, height, width);

  return 0;
}

/* a method to find and print out the location of the character marker in a given maze */
void testMarker(char marker, char **maze, int height, int width) {
  int row, column;
  bool success = find_marker(marker, maze, height, width, row, column);
  cout << "Marker " << marker << " was ";
  if(!success) {
    cout << " NOT ";
  }
  cout << "found\n";
  cout << "Coordinates of " << marker << " are row: " << row << " column: " << column << endl;
}

/* a method to test a given path really is a solution to a given height x width maze */
void testSolution(char *path, char **maze, int height, int width) {
  cout << "The move sequence '" << path << "' is ";
  if(!valid_solution(path, maze, height, width)) {
    cout << "NOT ";
  }
  cout << "a solution to the maze." << endl << endl;
}

/* a method to test whether given coordinates are valid coordinates for a maze */
void testValidCoords(int row, int column, char **maze, int height, int width) {
  cout << "The coordinates row: " << row << " column: " << column << " are ";
  if(!valid_coords(row, column, maze, height, width)) {
    cout << "NOT ";
  }
  cout << "valid for the maze." << endl << endl;
}

void testFindPath(char **maze, int height, int width) {
  cout << "Expect solution to " << endl;
  print_maze(maze, height, width);
  cout << "To be " << endl;
  cout << find_path(maze, height, width, '>', 'X');
  print_maze(maze, height, width);
}
