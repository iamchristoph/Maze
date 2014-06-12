
#include "Pathfinder.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>


Pathfinder::Pathfinder() {
	// TODO Auto-generated constructor stub
	srand(time(NULL));
	current_x = 0;
	current_y = 0;
}

Pathfinder::~Pathfinder() {
	// TODO Auto-generated destructor stub
}


/*
 * getMaze
 *
 * Returns a string representation of the current maze. Returns "INVALID" if no maze
 * has yet been generated or imported.
 *
 *A valid maze must also have 1s in the entrance cell (0, 0) and in the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1).
 *
 * Cell (0, 0) is represented by the first number in the string representation of the
 * maze. Increasing in x means moving toward the east, meaning cell (1, 0) is the second
 * number. Increasing in y means moving toward the south, meaning cell (0, 1) is the
 * MAZE_WIDTH + 1 number. Cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1) is represented by the last number.
 *
 * Returns:		string
 *				A single string representing the current maze
 */
string Pathfinder::getMaze() {
	string bad_string = "INVALID";
	if (Maze[0][0] != 1 || Maze[(MAZE_WIDTH - 1)][(MAZE_HEIGHT - 1)] != 1) {
		return bad_string;
	}
	string output_string = "";
	string input;
	stringstream ss;
	for (int x = 0; x < MAZE_WIDTH; x++) {
		for (int y = 0; y < MAZE_HEIGHT; y++) {
				ss.str(std::string());
				ss << Maze[x][y];
				output_string = output_string + ss.str() + " ";
		}
		output_string = output_string + "\n";
	}
	return output_string;

}   //end getMaze

/*
 * createRandomMaze
 *
 * Generates a random maze and stores it as the current maze.
 *
 * The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
 * in the entrance cell (0, 0) and in the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1).  The generated maze may be
 * solvable or unsolvable, and this method should be able to produce both kinds of mazes.
 */
void Pathfinder::createRandomMaze() {
	cout<<"random maze:";
	for (int x = 0; x < MAZE_WIDTH; x++) {
		for (int y = 0; y < MAZE_HEIGHT; y++) {
				int r = (rand() % (1 + 1));
				Maze[x][y] = r;
		}
	}
	Maze[0][0] = 1;  //maze start must be 1
	Maze[(MAZE_WIDTH - 1)][(MAZE_HEIGHT - 1)] = 1;  //maze end must be 1

	for (int x = 0; x < MAZE_WIDTH; x++) {
		for (int y = 0; y < MAZE_HEIGHT; y++) {
				cout << Maze[x][y];
		}
	}

	cout << endl;

}    //end createRandomMaze

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

bool Pathfinder::importMaze(string file_name) {
	string variable = "";
	int counter = 0;
	bool is_valid = true;
	ifstream infile(file_name.c_str());

	if (infile.is_open()) {
		if (infile.fail()) {
			cout << "File read failed.";
			return false;
		}	//end if infile fails

		for (int x = 0; x < MAZE_WIDTH; x++) {
			for (int y = 0; y < MAZE_HEIGHT; y++) {
					infile >> variable;
					if (variable != "1" && variable != "0" && variable != "2" && variable != "3") {//checks invalid input  changed 6/11
					cout << "characters are not 1, 0, 2, or 3.  character: "<<variable<<endl;
						is_valid = false;
					}
			}
		}					//end for x

		infile.close();

	}					//end if infile is open

	if (is_valid) {
		int variable2 = 0;
		//cout << "is valid apparently...";
		ifstream infile(file_name.c_str());
		if (infile.is_open()) {
			if (infile.fail()) {
				cout << "File read failed code location 2.";
				return false;
			}					//end if infile fails

			for (int x = 0; x < MAZE_WIDTH; x++) {
				for (int y = 0; y < MAZE_HEIGHT; y++) {
						infile >> variable2;
						Maze[y][x] = variable2;
				}
			}					//end for x
			infile.close();
		}					//end if infile is open
		else {
			cout << "Unable to open file code location 2";
			return false;
		}
		return true;
	}					//end if is valid
	else {
		cout << "Did not change maze because imported maze is invalid";
		return false;
	}
}					//end import maze

/*
 * solveMaze
 *
 * Attempts to solve the current maze and returns a solution if one is found.
 *
 * A solution to a maze is a list of coordinates for the path from the entrance to the exit
 * (or an empty vector if no solution is found). This list cannot contain duplicates, and
 * any two consecutive coordinates in the list can only differ by 1 for only one
 * coordinate. The entrance cell (0, 0) and the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1) should be included
 * in the solution. Each string in the solution vector must be of the format "(x, y)",
 * where x, and y are the integer coordinates of a cell.
 *
 * Understand that most mazes will contain multiple solutions
 *
 * Returns:		vector<string>
 *				A solution to the current maze, or an empty vector if none exists
 */

int start_x = -1;
int start_y = -1;
int end_x = -1;
int end_y = -1;

vector<string> Pathfinder::solveMaze() {
	for (int x = 0; x < MAZE_WIDTH; x++) {     //create test maze to modify
		for (int y = 0; y < MAZE_HEIGHT; y++) {
				test_maze[x][y] = Maze[x][y];
		}
	}
	/*started here, changed 6/11*/
	//int start_point = test_maze[0][0]; //make sure maze start point is open
	//int end_point = test_maze[(MAZE_WIDTH - 1)][(MAZE_HEIGHT - 1)];  //make sure maze end point is open
	//if (start_point != 1 || end_point != 1) {
		//cout << "invalid entrance and/or exit to maze";
	//}

	

	for (int i = 0; i < Pathfinder::MAZE_WIDTH; i++){
		for (int j = 0; j < Pathfinder::MAZE_HEIGHT; j++){
			if (Pathfinder::Maze[i][j] == 2){
				start_x = i;
				start_y = j;
			}
			if (Pathfinder::Maze[i][j] == 3){
				end_x = i;
				end_y = j;
			}
		}
	}
	if (start_x == -1 || end_x == -1 || start_y == -1 || end_y == -1){  //changed 6/11
		cout << "No entrance and/or exit to maze found." << endl;
	}

	Pathfinder::solvemaze(start_x, start_y);			//starting point  ended here changed 6/11

	//cout <<"path vector: "<<endl;
	if(path_vector.empty()){
		cout << "Maze Unsolvable" << endl;  //if nothing in vector then no solution found
	}
	//for (int i = 0; i < path_vector.size(); i++){
		//cout << path_vector[i] << endl;
	//} //this prints path_vector
	
	/*cout << endl << "Test maze after run-through.  8 marks true path, 5 marks visited: " << endl;    
	for (int y = 0; y < MAZE_WIDTH; y++) {             //the following for loops print the marked-up maze from beginning to end. 
		for (int x = 0; x < MAZE_HEIGHT; x++) {        //shows true path and visited areas.
				cout << test_maze[x][y] << " ";
		}
		cout << "\n";
	}
	cout << endl; */
	return path_vector;

}//end solvemaze


/* coords_to_string is used twice in the below function.  
* It is a helper function to put the coordinates into a string for storing in the vector.
*/
string coords_to_string(int x, int y) {
	stringstream ss1;
	ss1 << x;
	string str1 = ss1.str();
	stringstream ss2;
	ss2 << y;
	string str2 = ss2.str();
	string output_string = str1 + ", " + str2;
	return output_string;
}

bool Pathfinder::solvemaze(int current_x, int current_y)
{

	int path = 8; //mark test maze as path
	int visited = 5;  //mark test maze as visited
	int barrier = 0;  //mark as barrier.  Not used in this code.

	if ((test_maze[current_x][current_y] == 5 || test_maze[current_x][current_y] == 8) && ((current_x < MAZE_WIDTH) && (current_y < MAZE_HEIGHT))){  //6/11
		path_vector.push_back(coords_to_string(current_x, current_y));
		full_path.push_back(Point(current_x, current_y));
	}




	if (current_x < 0 || current_y < 0 || current_x >(MAZE_WIDTH - 1) || current_y >(MAZE_HEIGHT - 1)) {
		//cout <<"Cell is out of bounds" <<endl;  //cell is out of bounds
		return false;
	}
	else if (current_x == end_x && current_y == end_y) {  //changed 6/11
		test_maze[current_x][current_y] = path; //cell is on path
		path_vector.push_back(coords_to_string(current_x, current_y));
		full_path.push_back(Point(current_x, current_y));
		//cout << "Exit Found." << endl;
		return true;     			//and is maze exit

	}
	else if (test_maze[current_x][current_y] != 1 && test_maze[current_x][current_y] != 2 && test_maze[current_x][current_y] != 3) {  //changed 6/11
		//cout<<"cell is on barrier or dead end or visited at: " <<current_x<<", " <<current_y<<endl;
		return false;  //cell is on a barrier or dead end

	}
	test_maze[current_x][current_y] = path;  //mark as on path because coordinate is not out of bounds, maze exit, or barrier or dead end

	path_vector.push_back(coords_to_string(current_x, current_y));
	full_path.push_back(Point(current_x, current_y));


	if (solvemaze(current_x + 1, current_y) == true){
		return true;
	}
	if (solvemaze(current_x, current_y + 1) == true){
		return true;
	}
	if (solvemaze(current_x - 1, current_y) == true){
		return true;
	}
	if (solvemaze(current_x, current_y - 1) == true){
		return true;
	}
	test_maze[current_x][current_y] = visited;  //been here, doesn't work
	//if (test_maze[current_x][current_y] == 5){ //6/11
		//path_vector.pop_back(); //pop back coordinates.  Omit this line if you want the entire path of the maze traversal to be printed,
	//}			6/11									//including all paths traversed, not just the solution path.
													//note: doesn't print full return path, prints all paths tried, but after unsuccessful venture
													//into a path it resumes at the point before that path.
	return false;


	

}  //end bool solvemaze




stack<Point> Pathfinder::return_path(){  //6/11
	stack<Point> points_path;
	for (int i = 0; i < full_path.size() - 1; i++){
		points_path.push(full_path[full_path.size()-1 - i]);
	}
	return points_path;
}

vector<string> Pathfinder::return_path_string(){
	return path_vector;
}