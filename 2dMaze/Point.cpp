#include "Point.h"


Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}

Point::Point(){
	x = 0;
	y = 0;
}


Point::~Point()
{
}

bool Point::operator==(const Point& rSide){
	if (this->x == rSide.x){
		if (this->y == rSide.y){
			return true;
		}

	}
	return false;

}