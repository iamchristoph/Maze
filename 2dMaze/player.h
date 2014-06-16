
#include <string>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <iostream>
#include "Point.h"

using namespace std;



const int TILE_SIZE = 40;

class player
{
public:
	player(int, int);
	player();
	//set desired location (only sets new point if player was next to the coordinate
	void move(Point);
	ALLEGRO_BITMAP* getPlayer();
	Point getLocation();
	void setX(int);
	void setY(int);
	~player();
private:
	ALLEGRO_BITMAP* current;
	ALLEGRO_BITMAP* left;
	ALLEGRO_BITMAP* right;
	ALLEGRO_BITMAP* down;
	ALLEGRO_BITMAP* up;
	Point location;
	
};

