
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Point.h"

#ifndef PATHFINDER_H_
#define PATHFINDER_H_


using namespace std;



class Pathfinder {
public:
	Pathfinder(string);
	~Pathfinder();


	/*
	 * getMaze
	 *
	 * Returns a string representation of the current maze. Returns "INVALID" if no maze
	 * has yet been generated or imported.
	 *
	 * A valid maze must also have 1s in the entrance cell (0, 0) and in the exit cell (MAZE_WIDTH, MAZE_HEIGHT).
	 *
	 * Cell (0, 0) is represented by the first number in the string representation of the
	 * maze. Increasing in x means moving toward the east, meaning cell (1, 0) is the second
	 * number. Increasing in y means moving toward the south, meaning cell (0, 1) is the
	 * MAZE_WIDTH + 1 number.  Cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1) is represented by the last number.
	 *
	 * Returns:		string
	 *				A single string representing the current maze
	 */
	string getMaze();

	/*
	 * createRandomMaze
	 *
	 * Generates a random maze and stores it as the current maze.
	 *
	 * The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
	 * in the entrance cell (0, 0) and in the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT  - 1).  The generated maze may be
	 * solvable or unsolvable, and this method should be able to produce both kinds of mazes.
	 */
	void createRandomMaze(int width, int height, string fileName);

	/*
	 * importMaze
	 *
	 * Reads in a maze from a file with the given file name and stores it as the current maze.
	 * Does nothing if the file does not exist or if the file's data does not represent a valid
	 * maze.
	 *
	 * The file's contents must be of the format described above to be considered valid.
	 *
	 * Parameter:	file_name
	 *				The name of the file containing a maze
	 * Returns:		bool
	 *				True if the maze is imported correctly; false otherwise
	 */
	bool importMaze(string file_name);

	/*
	 * vector solveMaze
	 *
	 * Attempts to solve the current maze and returns a solution if one is found.
	 *
	 * A solution to a maze is a list of coordinates for the path from the entrance to the exit
	 * (or an empty vector if no solution is found). This list cannot contain duplicates, and
	 * any two consecutive coordinates in the list can only differ by 1 for only one
	 * coordinate. The entrance cell (0, 0) and the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1) should be included
	 * in the solution. Each string in the solution vector must be of the format "(x, y)",
	 * where x and y are the integer coordinates of a cell.
	 *
	 * Understand that most mazes will contain multiple solutions
	 *
	 * Returns:		vector<string>
	 *				A solution to the current maze, or an empty vector if none exists
	 */
	vector<string> solveMaze();

	/* 
	* bool solvemaze
	*
	* Uses recursion and a depth-first graph algorithm to find the maze.  Returns true if a next-step is found.
	* If x+1 or y+1 (etc.) are not blocked by a wall (a '0') or out of bounds(x or y < 0, or MAZE_WIDTH, MAZE_HEIGHT), then this function returns true.
	*/
	bool solvemaze(int current_x, int current_y);
	bool solvemaze(int current_x, int current_y, Point direction, int tries);
	/*
	* void getPath
	*
	* picks a random direction and generates ai path using solvmaze
	*/
	bool getPath(Point);
	bool getPath(Point, Point, int);
	/*
	*return_full_maze_path_ints
	*returns a stack of ints as coordinates for the full path of the maze traversal.
	*Every odd number is x coordinate, even number is y coordinate.
	*/
	stack<int> return_full_maze_path_ints();

	/*
	*return_full_maze_path_string
	*returns a stack of strings as coordinates for the full path of the maze traversal
	*in the form x, y.
	*/
	stack<string> return_full_maze_path_string();
	vector<Point> full_path;  //patfh to end goal
	stack<Point> _path;
	/*
	*return_path
	*returns points of full maze traversal
	*/
	stack<Point> return_path();

	void getDirection(void);
	vector<string> return_path_string();
private:
	void changePath(vector<vector<int>>&, Point, Point);
	int MAZE_WIDTH;  //update this for maze width
	int MAZE_HEIGHT;  //update this for maze height
	vector<vector<int>> map;
	//int Maze[MAZE_WIDTH][MAZE_HEIGHT];  //original maze to be used
	//int test_maze[MAZE_WIDTH][MAZE_HEIGHT];  //this maze is a copy of Maze[][], and is marked up with the path and visited cells for the solution.
	int current_x;
	int current_y;
	//get direction fills the direction stack with a set of random directions to try
	stack<Point> direction;
	vector<string> path_vector;
	stack<Point> mazeSolution;

	Point back;
	Point start;
	Point end;
	Point up = Point(0, -1);
	Point down = Point(0, 1);
	Point left = Point(-1, 0);
	Point right = Point(1, 0);
};

#endif /* PATHFINDER_H_ */
