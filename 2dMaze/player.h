#pragma once
#include <string>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

using namespace std;

struct Point{
	int x;
	int y;
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
	Point(){
		x = 0;
		y = 0;
	}
};

const int TILE_SIZE = 80;

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
	ALLEGRO_BITMAP* image;
	Point location;
	
};

