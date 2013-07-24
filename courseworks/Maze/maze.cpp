#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "maze.h"

using namespace std;

// a global variable to hold the string returned when we can't find solutions
const char *NO_SOLUTION = "no solution";

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* a function to find the coordinates (row, column) a given marker character ch within a width x height maze */
bool find_marker(char ch, char **maze, int height, int width, int& row, int& column) {
  //begin search at row 0 and column 0
  //try all the width values in row 0 then move onto row 1, and so on through all height rows
  for(row=0;row<height;row++) {
    for(column = 0;column<width;column++) {
      //check to see whether the character in row row and column column is the marker character
      if(maze[row][column] == ch) {
	//if it is we have set the row and column coordinates to the required values and can return false (thus leaving the function)
	return true;
      }
    }
  }
  //if we get here we have exhausted all possible parts of the maze and still not found the marker character so it cannot be present
  //so set the row and column to -1 and return false as set out by the spec
  row = -1;
  column = -1;
  return false;
}

/* a function to check whether a given path is a valid solution to a given height x width maze */
/* Method:
   We find the coordinates of the start and end markers using find_marker function with '>' and 'X' respectively.
   If the maze lacks a start or end marker, we will return false on the basis that there cannot be a solution without a start and an end point.
   We set our initial working coordinates to be the coordinates of the start coordinates.
   We then iterate through each character of the path, changing the working coordinates as follows:
     An E increases row by 1
     A W decreases row by 1
     An S increases column by 1
     An N decreases column by 1
   For each working coordinate, we check to see if we are in an invalid loction:
     A location is considered invalid if 
       * its coordinates are outside of the maze, i.e. row < 0, column < 0, row >= height OR column >= width.
       * its location is a barrier character, '-', '+' OR '|'.
       * its location is an unreachable location character, 'U'.
   If we're in an invalid location the path must be invalid, so we can return false
   Otherwise if we loop right through the string, we know the path is valid but we must check that the path is also a solution, i.e. that the final coordinates are the X coordinates. If this is the case we can return true to indicate the path is a valid solution, otherwise we return false.
  */

//NB this function may not be correct if there is more than one start or end point (i.e. more than one '>' marker or 'X' marker)
bool valid_solution(char *path, char **maze, int height, int width) {
  //we'll use a pair of integers to indicate where we are in the maze
  int working_row, working_column;
  // variables to store the end point coordinates
  int end_point_row, end_point_column;
  //variables to use with navigating the maze using the path
  char direction;
  int path_step;

  //initialize working coordinates to be the start marker
  //and check we find the start point, otherwise we're in trouble
  if(!find_marker('>', maze, height, width, working_row, working_column)) {
    cerr << "The maze has no start\n";
    return false;
  }
  
  //we'll get the end point markers too as we'll need them later and no point continuing if there is no end point
  if(!find_marker('X', maze, height, width, end_point_row, end_point_column)) {
    cerr << "The maze has no end\n";
    return false;
  }

  //otherwise we can start processing the path
  //start at 0th character
  path_step = 0;
  direction = path[path_step];
  //loop through all characters until we get to end of path string
  while(direction != '\0') {
    //move the working coordinates along according to the direction
    update_position_coords(direction, working_row, working_column);
    //check if the position if invalid
    if(!valid_coords(working_row, working_column, maze, height, width)) {
      return false;
    }
    //get the next direction character
    path_step++;
    direction = path[path_step];
  }
  //if we get to here we have a valid path
  //however, we need to check the coordinates are the same as the end marker
  return compare_coords(working_row, working_column, end_point_row, end_point_column);
}

// a function to find a path from start character to end character in height x width maze
/* The method is to try going E from start and trying to find a path from new location to end using this method.
   If there is a solution Path from new location then a solution from start is E+Path. 
   Otherwise, undo the move E and try S and then W and then N from start. 
   Thus recursively try an exhaustive search of paths from start to everywhere reachable in the maze (returning as soon as we find a solution). 
   If no solution is found in this exhaustive search, then we return "no solution". 
   
   I will use the character 'C' to indicate our current location in the maze while trying different paths.
*/
// N.B. the function below is by no means the most efficient implentation of the algorithm used but hopefully it is readable and there aren't too many coupled variables.
char *find_path(char **maze, int height, int width, char start, char end) {
  //a variable on the heap to store our solution in
  //fairly arbitrarily going to limit paths to be 2048 characters long at most (roughly 10 times longer than the solution from Centre to Exit of the Hatfield maze, not a huge memory requirement (suppose we end up making 2048 moves we may have 2048 paths of size 2048 floating around, still only ~4MB, Firefox currently has 180M just resident in the main memory) and chances are if the path ends up being that long the function will be too slow to be useful).
  char *path = new char[2048];
  //something to preserve where the we want to end (as we may overwrite the end marker)
  int end_row, end_column;

  //replace start location with the C marker denoting current location
  if(!set_start_as_current_location(start, maze, height, width)) {
    cerr << "Cannot find marker " << start << "to start in the maze at, so there can be no solution.\n";
    //return no solution if there is no start point
    strcpy(path, NO_SOLUTION);
    return path;
  }
   
  //find coordinates of the end marker, if there is one
  if(!find_marker(end, maze, height, width, end_row, end_column)) {
    cerr << "No end point marked by " << end << " so there can be no solution.\n";
    //return no solution if there is no end marker
    strcpy(path, NO_SOLUTION);
    return path;
  }
  
  //now we try going East, if that is a valid move that doesn't double back on itself, try finding a path from the new location to the end
  //if going East isn't valid, try the same but for South and then West and then North (so recursively we will eventually get to the end if we can)
  //if none of those work, then there is no solution from where we are currently, so return no solution
  char directions[4] = {'E', 'S', 'W', 'N'};
  for(int i=0; i<4; i++) {
    char direction = directions[i];
    //check if going in the given direction is a legal move
    if(can_go(direction, maze, height, width)) {
      //do the move in the direction
      do_go(direction, maze, height, width, path, end, end_row, end_column);
      //if that sets path to something other than no solution, we can happily return this path as a solution
      if(strcmp(path, NO_SOLUTION)) {
      	return path;
      }
      //otherwise we'll just carry on and try the next direction
    }
  }
  //if we tried all directions and haven't found a path, there can't be one
  strcpy(path, NO_SOLUTION);
  return path;
}

// a function to make and act on a move in a maze in a particular direction as part of finding a path from current location to end character
// N.B. we need the end marker so we can call find_path recursively
// Separately we need end_row and end_column incase we are already at the end point but have overwritten the end marker with a C to mark our currrent location.
void do_go(char direction, char **maze, int height, int width, char *path, char end, int end_row, int end_column) {
  //make the move from current location in direction given, updating the location of our 'C' current location marker and the string of characters stored in path.
  make_move(direction, maze, height, width, path);
      
  //what can we do from here?
  //either we're at the end - hooray
  //or we can try and find a solution from here
  //or else moving direction to here didn't help us and we should undo the move
      
  //are we at the end point?
  if(at_end_of_maze(end_row, end_column, maze, height, width)) {
    //if so we can return straight away, path is already a solution (and fill in the final path marking # on the maze)
    complete_path_on_maze(maze, height, width);
    return;
  } 

  //otherwise, we're not at the end but we can try and find a path from here
  char *onwards_path = find_path(maze, height, width, 'C', end);
  if(strcmp(onwards_path, NO_SOLUTION)) {
    //we found a path from this new position to the end, so the path from starting postion to end is the move we just took followed by the onward_path we just found
    strcat(path, onwards_path);
    //once we've tacked onwards_path onto path itself, we should release the memory used to onwards path (each call to find_path allocates a little bit more memory from the heap to hold the return value)
    delete [] onwards_path;
    return;
  } else {
    //going in this direction didn't work so back out the change to maze
    strcpy(path, NO_SOLUTION);
    undo_move(direction, maze, height, width);
    //similarly want to release the memory pointed at by onward_path
    delete [] onwards_path;
    return;
  }
}

//a function to the change a pair of coordinates based on which direction we want to go
void update_position_coords(char direction, int &row, int &column) {
  /* assuming we layout the maze from top left to bottom right, then
     East means right, i.e. increase column coordinate
     West means left, i.e. decrease column coordinate
     North means up, i.e. decrease row coordinate
     South means down, i.e. increase row coordinate
  */
  switch(direction) {
  case 'E':
    column++;
    break;
  case 'W':
    column--;
    break;
  case 'N':
    row--;
    break;
  case 'S':
    row++;
    break;
  default:
    cerr << "Unrecognised direction: " << direction << endl << "Terminating program..." << endl;
    exit(1);
  }
}

//an function that will compare a pair of coordinates and return true if and only if they are the same
bool compare_coords(int row1, int column1, int row2, int column2) {
  //coordinates are the same if and only if the row values match AND the column values match
  return (row1 == row2) && (column1 == column2);
}

// a function to say whether a pair of coordinates are in a given height x width maze and a valid location to be (so not a border or an unreachable location).
bool valid_coords(int row, int column, char **maze, int height, int width) {
  char maze_char;
  //first check the coordinates lie within the area covered by the maze
  if((row < 0) || (column < 0) || (row >= height) || (column >= width)) {
    return false;
  }
  //check whether the character at the coordinates is NOT a barrier character or an unreachable character
  maze_char = maze[row][column];
  return (maze_char != '-') && (maze_char != '+') && (maze_char != '|') && (maze_char != 'U');
}

// a function to move current location on and update the path in the maze based on the given direction
void make_move(char direction, char **maze, int height, int width, char *path) {
  int current_row, current_column;
  if(!find_marker('C', maze, height, width, current_row, current_column)) {
    cerr << "Cannot find current location so unable to make move in the desired direction\nDon't know what to do. Terminating...\n";
    exit(1);
  }
  path[0] = direction;
  path[1] = '\0';
       
  maze[current_row][current_column] = '#';
  update_position_coords(direction, current_row, current_column);
  maze[current_row][current_column] = 'C';
}

//a function to undo a move in a given direction where the current position is given by a marker character
void undo_move(char direction, char **maze, int height, int width) {
  int current_row, current_column;
  if(!find_marker('C', maze, height, width, current_row, current_column)) {
    cerr << "Cannot find current location so unable to make undo move.\nDon't know what to do. Terminating...\n";
    exit(1);
  }
  //reset the move to the current location
  maze[current_row][current_column] = ' ';
  //get the coordinates of the moving in the reverse direction to the one we just moved
  update_position_coords(reverse(direction), current_row, current_column);
  //check the new position is valid (if it isn't something has gone very wrong indeed
  if(!valid_coords(current_row, current_column, maze, height, width)) {
    cerr << "Couldn't reverse the move to " << direction << ". Something has gone badly wrong. Terminating...\n";
    exit(1);
  }
  //set the curren marker to be at those coordinates
  maze[current_row][current_column] = 'C';
}

//a function which, given a direction, returns the reverse direction
char reverse(char direction) {
  switch (direction) {
  case 'E': 
    return 'W';
  case 'W':
    return 'E';
  case 'S':
    return 'N';
  case 'N':
    return 'S';
  default:
    cerr << "Unknown direction " << direction << endl << "Terminating..." << endl;
    exit(1);
  }
}

// a function to determine if a path can go in a certain direction from current location
// i.e. would moving in the given direction take us to a valid maze square and not have us cross over the path that has already been laid out
bool can_go(char direction, char **maze, int height, int width) {
  int row, column;
  if(!find_marker('C', maze, height, width, row, column)) {
    cerr << "Cannot find current location so unable to determine if we can go in the desired direction\n";
    return false;
  }
  update_position_coords(direction, row, column);
  return valid_coords(row, column, maze, height, width) && (maze[row][column] != '#');
}

// a function to replace a start marker with out universal C marker to denote current location
bool set_start_as_current_location(char start, char **maze, int height, int width) {
  //something to store the coordinates of where we currently are
  int current_row, current_column;
  //find the start marker, if there is one
  if(!find_marker(start, maze, height, width, current_row, current_column)) {
    cerr << "No start point\n";
    return false;
  }
  //put our current location on the maze, indicated with a C
  maze[current_row][current_column] = 'C';
  return true;
}

// a function to determine whether the current location marker is at the coordinates of the maze end
bool at_end_of_maze(int end_row, int end_column, char **maze, int height, int width) {
  int current_row, current_column;
  if(!find_marker('C', maze, height, width, current_row, current_column)) {
    cerr << "Cannot find current location marked by 'C'." << endl;
    return false;
  }
  return compare_coords(current_row, current_column, end_row, end_column);
}

// a function to to change the current location to a hash marking a path
void complete_path_on_maze(char **maze, int height, int width) {
  int current_row, current_column;
  if(!find_marker('C', maze, height, width, current_row, current_column)) {
    cerr << "Cannot find current location so unable to complete path on maze\n";
    return;
  }
  maze[current_row][current_column] = '#';
}
