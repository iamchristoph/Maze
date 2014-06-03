#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include "Pathfinder.h"


using namespace std;

int main(){

	Pathfinder test;
	if (test.importMaze("Mazes/tenbytensolvable1.txt")){  //maze to be imported and used
		//test.createRandomMaze();
		//test.getMaze();
		test.solveMaze();
	}
	cin.get();
	return 0;
}
