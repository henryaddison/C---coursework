#ifndef MAZE_H
#define MAZE_H

// a global variable to hold the string returned when we can't find solutions
extern const char *NO_SOLUTION;

/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

// Programmer-defined functions to answer the questions in the assignment

/* a function to find the coordinates (row, column) a given marker character ch within a width x height maze */
bool find_marker(char ch, char **maze, int height, int width, int& row, int& column);

/* a function to check whether a given path is a valid solution to a given height x width maze */
bool valid_solution(char *path, char **maze, int height, int width);

// a function to find a valid path from start character to end character in height x width maze
char *find_path(char **maze, int height, int width, char start, char end);

//Helper functions produced as part of answering the questions in the assignment

//a function to the change a pair of coordinates based on which direction we want to go
void update_position_coords(char direction, int &row, int &column);

//an function that will compare a pair of coordinates and return true if and only if they are the same
bool compare_coords(int row1, int column1, int row2, int column2);

// a function to say whether a pair of coordinates are a valid location to be in a given height x width maze
bool valid_coords(int row, int column, char **maze, int height, int width);

// a function to determine if a path can go in a certain direction
// i.e. would moving in the given direction take us to a valid maze square and not have us cross over the path that has already been laid out
bool can_go(char direction, char **maze, int height, int width);

// a function to move current location on and update the path in the maze based on the given direction
void make_move(char direction, char **maze, int height, int width, char *path);

//a function to undo a move in a given direction where the current position is given by coordinates that get changed in place
void undo_move(char direction, char **maze, int height, int width);

//a function which, given a direction, returns the reverse direction
// so e.g. 'E' becomes 'W' and 'S' becomes 'N'
char reverse(char direction);

// a function to replace a start marker with out universal C marker to denote current location
bool set_start_as_current_location(char start, char **maze, int height, int width);

// a function to determine whether the current location marker is at the coordinates of the maze end
bool at_end_of_maze(int end_row, int end_column, char **maze, int height, int width);

// a function to put the final # in place of the C when our path reaches the end of the maze
void complete_path_on_maze(char **maze, int height, int width);

// a function to make and act on a move in a maze in a particular direction as part of finding a path from current location to end character
void do_go(char direction, char **maze, int height, int width, char *path, char end, int end_row, int end_column);

#endif
