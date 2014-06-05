#pragma once
#include "player.h"
#include <fstream>



class Map
{
public:

	Map(string);
	~Map();
	
	//send a 1 for left 2 for up 3 for right and 4 for down
	void movePlayer(Point);
	Point getPlayerLocation();
	ALLEGRO_BITMAP* createMapCopy(int, int);
	bool levelFinished();

private:
	vector<vector<int>> map;
	ALLEGRO_BITMAP* level;
	void updateBitmap();
	player person;
	bool goalFound;

	//bitmaps for drawing the map
	ALLEGRO_BITMAP* canGo;
	ALLEGRO_BITMAP* noGo;
	ALLEGRO_BITMAP* goal;


};

