
#include "Pathfinder.h"


Pathfinder::Pathfinder(string filePath) {
	// TODO Auto-generated constructor stub
	srand(time(NULL));
	current_x = 0;
	current_y = 0;
	importMaze(filePath);


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
/*
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
*/
/*
 * createRandomMaze
 *
 * Generates a random maze and stores it as the current maze.
 *
 * The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
 * in the entrance cell (0, 0) and in the exit cell (MAZE_WIDTH - 1, MAZE_HEIGHT - 1).  The generated maze may be
 * solvable or unsolvable, and this method should be able to produce both kinds of mazes.
 */

void Pathfinder::createRandomMaze(int width, int height, string fileName) {
	
	//create map size
	vector<vector<int>> tempMap;
	for (int i = 0; i < width; i++){
		vector<int> temp;
		for (int j = 0; j < height; j++){
			temp.push_back(0);
		}
		tempMap.push_back(temp);

	}
	//create start
	Point start(20 % width, 20 % height);
	stack<Point> nextPoint;
	nextPoint.push(start);
	int pathSize = 3;

	while (!nextPoint.empty()){
		Point current = nextPoint.top();
		nextPoint.pop();
		//right
		//check if the next location is allowed
		
			bool pathValid = true;
			if (current.x + pathSize + 1 > width){

								pathValid = false;
							}
			else{
				if (tempMap[current.y][current.x + pathSize + 1] != 0){
					pathValid = false;
				}
				for (int i = pathSize; i > 0; i--){
					if (current.y - 1 >= 0){
						if (tempMap[current.y - 1][current.x + i] != 0){
							pathValid = false;
						}
					}
					if (current.y + 1 < height){
						if (tempMap[current.y + 1][current.x + i] != 0){
							pathValid = false;
						}
					}

					if (tempMap[current.y][current.x + i] != 0){
						pathValid = false;

					}
				}
			}
			
			if (pathValid){
				Point newPoint(current.x + pathSize, current.y);
				changePath(tempMap, current, newPoint);
				nextPoint.push(newPoint);
			}
			
			
		//write location and put location as the next to be run

		//left
			pathValid = true;
			if (current.x - pathSize - 1 < 0){
				pathValid = false;
			}
			else{
				if (tempMap[current.y][current.x - pathSize - 1] != 0){
					pathValid = false;
				}
				for (int i = pathSize; i > 0; i--){
					if (current.y - 1 >= 0){
						if (tempMap[current.y-1][current.x - i] != 0){
							pathValid = false;
						}
					}
					if (current.y + 1 < width){
						if (tempMap[current.y+1][current.x - i] != 0){
							pathValid = false;
						}
					}
					if (tempMap[current.y][current.x - i] != 0){
						pathValid = false;

					}
				}
			}
			if (pathValid){
				Point newPoint(current.x - pathSize, current.y);
				changePath(tempMap, current, newPoint);
				nextPoint.push(newPoint);
			}

		//down
			pathValid = true;
			if (current.y + pathSize + 1 >= height){
				pathValid = false;
			}
			else{
				if (tempMap[current.y + pathSize + 1][current.x] != 0){
					pathValid = false;
				}
				for (int i = pathSize; i > 0; i--){
					if (current.x + 1 < width){
						if (tempMap[current.y + i][current.x + 1] != 0){
							pathValid = false;
						}
					}
					if (current.x - 1 <= 0){
						if (tempMap[current.y + i][current.x-1] != 0){
							pathValid = false;
						}
					}
					if (tempMap[current.y + i][current.x] != 0){
						pathValid = false;

					}
				}
			}
			if (pathValid){
				Point newPoint(current.x, current.y + pathSize);
				changePath(tempMap, current, newPoint);
				nextPoint.push(newPoint);
			}
		//up
			pathValid = true;
			if (current.y - pathSize - 1 < 0){
				pathValid = false;
			}
			else{
				if (tempMap[current.y - pathSize - 1][current.x] != 0){
					pathValid = false;
				}
				for (int i = pathSize; i > 0; i--){

					if (current.x - 1 >= 0){
						if (tempMap[current.y - i][current.x - 1] != 0){
							pathValid = false;
						}
					}
					if (current.x + 1 < width){
						if (tempMap[current.y - i][current.x + 1] != 0){
							pathValid = false;
						}
					}
					if (tempMap[current.y - i][current.x] != 0){
						pathValid = false;

					}
				}
			}
			if (pathValid){
				Point newPoint(current.x, current.y - pathSize);
				changePath(tempMap, current, newPoint);
				nextPoint.push(newPoint);
			}

	}

	tempMap[start.y][start.x] = 2;

	//write maze to file
	std::ofstream file;
	file.open(fileName);
	if (!file){ throw 1; }
	for(int i = 0; i < tempMap.size(); i++){
		vector<int> out = tempMap[i];
		for (int j = 0; j < out.size(); j++){

			
			file << out.at(j);
			if (j < out.size() - 1){
				file << " ";
			}

		}

		file << endl;
	}
	file.close();
	

}    //end createRandomMaze

void Pathfinder::changePath(vector<vector<int>> &map, Point begin, Point finish){




	if (begin.x - finish.x == 0){
		int dist = finish.y - begin.y;
		if (dist > 0){
			for (int i = 0; i < dist; i++){
				map[begin.y + i][begin.x] = 1;
			}
		}
		else if(dist < 0){
			dist *= -1;
			for (int i = 0; i < dist; i++){
				map[begin.y - i][begin.x] = 1;
			}
		}
		
	}
	else if (begin.y - finish.y == 0){
		int dist = finish.x - begin.x;
		if (dist > 0){
			for (int i = 0; i < dist; i++){
				map[begin.y][begin.x + i] = 1;
			}
		}
		else if (dist < 0){
			dist *= -1;
			for (int i = 0; i < dist; i++){
				map[begin.y][begin.x - i] = 1;
			}
		}
	}

}

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

bool Pathfinder::importMaze(string filePath) {

	map.clear();
	while (!mazeSolution.empty()){
		mazeSolution.pop();
	}
	std::ifstream file;
	file.open(filePath);
	if (!file){ throw 1; }
	while (!file.eof()){
		vector<int> store;
		while (file.peek() != '\n'){

			int num;
			file >> num;
			if (file.fail())break;
			store.push_back(num);

		}

		file.ignore();
		map.push_back(store);
		store.clear();
	}
	file.close();
	MAZE_WIDTH = map[0].size();
	MAZE_HEIGHT = map.size();

	solveMaze();
	/*
	string variable = "";
	int counter = 0;
	bool is_valid = true;
	ifstream infile(file_name);

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
		ifstream infile(file_name);
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
	*/
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


vector<string> Pathfinder::solveMaze() {
	/*for (int x = 0; x < MAZE_WIDTH; x++) {     //create test maze to modify
		for (int y = 0; y < MAZE_HEIGHT; y++) {
				test_maze[x][y] = Maze[x][y];
		}
	}*/
	/*started here, changed 6/11*/
	//int start_point = test_maze[0][0]; //make sure maze start point is open
	//int end_point = test_maze[(MAZE_WIDTH - 1)][(MAZE_HEIGHT - 1)];  //make sure maze end point is open
	//if (start_point != 1 || end_point != 1) {
		//cout << "invalid entrance and/or exit to maze";
	//}

	

	for (int i = 0; i < MAZE_WIDTH; i++){
		for (int j = 0; j < MAZE_HEIGHT; j++){
			if (map[j][i] == 2){
				start.x = i;
				start.y = j;
			}
			if (map[j][i] == 3){
				end.x = i;
				end.y = j;
			}
		}
	}
/*	if (start_x == -1 || end_x == -1 || start_y == -1 || end_y == -1){  //changed 6/11
		cout << "No entrance and/or exit to maze found." << endl;
	}
	*/
	solvemaze(start.x, start.y);			//starting point  ended here changed 6/11

	//cout <<"path vector: "<<endl;
	/*if(path_vector.empty()){
		cout << "Maze Unsolvable" << endl;  //if nothing in vector then no solution found
	}*/
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

bool solvemaze(Point current, Point direction); {}

//get direction fills the direction stack with a set of random directions to try
void Pathfinder::getDirection(void){
	Point dir[4] = { Point(0, -1), Point(0, 1), Point(-1, 0), Point(1, 0) };
	random_shuffle(dir[0], dir[3]);
	for (int i = 0; i > 4; i++)
	{
		direction.push(Point(dir[i].x, dir[i].y));
	}


};

bool Pathfinder::getPath(Point current)
{
	int distance = 3;
	Point go;
	getDirection();
	do{
		if (direction.empty())
		{
			direction.push(back);
		}
		else
		{
			go = direction.top();
			direction.pop();
		}
	}while(!getPath(current, go, distance));
	while (!direction.empty())
	{
		direction.pop();
	}
	back.x = 0;
	back.y = 0;
	return true;
};

bool Pathfinder::getPath(Point current, Point go, int distance)
{

	if (distance == 0)
	{
		return false;
	}
	current = current + go;
	distance--;
	if (current.x >= MAZE_WIDTH || current.y >= MAZE_HEIGHT || current.x < 0 || current.y < 0){
		return false;
	}

	int path = 1; //mark test maze as path
	int visited = 5;  //mark test maze as visited
	int barrier = 0;  //mark as barrier.  Not used in this code.
	int end = 3;

	if (map[current.y][current.x] == end){
		_path.push(Point(current.x, current.y));
		distance = 0;
		return true;
	}
	else if (map[current.y][current.x] == barrier || (map[current.y][current.x] == visited && go != back)){
		distance = 0;
		back = go;
		return false;
	}
	else if (map[current_y][current_x] == 1 || map[current_y][current_x] == 2 || go == back){
		map[current_y][current_x] = visited;
		_path.push(current);
		if (distance == 0){
			return true;
		}
		else if (go == up || go == down){
			if (getPath(current, left, 1)){
				distance = 0;
				_path.pop();
			}
			if (getPath(current, right, 1)){
				distance = 0;
				_path.pop();
			}
		}
		else if (go == left || go == right){
			if (getPath(current, up, 1)){
				distance = 0;
				_path.pop();
			}
			if (getPath(current, down, 1)){
				distance = 0;
				_path.pop();
			}
		}

};

bool Pathfinder::solvemaze(int current_x, int current_y)
{
	if (current_x >= MAZE_WIDTH || current_y >= MAZE_HEIGHT || current_x < 0 || current_y < 0){
		return false;
	}

	int path = 1; //mark test maze as path
	int visited = 5;  //mark test maze as visited
	int barrier = 0;  //mark as barrier.  Not used in this code.
	int end = 3;

	if (map[current_y][current_x] == end){
		mazeSolution.push(Point(current_x, current_y));
		return true;
	}
	else if (map[current_y][current_x] == barrier || map[current_y][current_x] == visited){
		return false;
	}
	else if (map[current_y][current_x] == 1 || map[current_y][current_x] == 2){
		map[current_y][current_x] = visited;
		if (solvemaze(current_x+1, current_y)){
			mazeSolution.push(Point(current_x, current_y));
			return true;
		}
		if (solvemaze(current_x-1, current_y)){
			mazeSolution.push(Point(current_x, current_y));
			return true;
		}
		if (solvemaze(current_x, current_y+1)){
			mazeSolution.push(Point(current_x, current_y));
			return true;
		}
		if (solvemaze(current_x, current_y-1)){
			mazeSolution.push(Point(current_x, current_y));
			return true;
		}

	}



	/*
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

	*/
	

}  //end bool solvemaze




stack<Point> Pathfinder::return_path(){  //  6/11
	
	return mazeSolution;
}

vector<string> Pathfinder::return_path_string(){
	return path_vector;
}
