#include "Point.h"


Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}

Point::Point(){
	x = 0;
	y = 0;
}

bool Point::operator==(Point& rhs){
	if (x == rhs.x && y == rhs.y)
		return true;
	else return false;
}

bool Point::operator!=(Point& rhs){
	if (x != rhs.x || y != rhs.y)
		return true;
	else return false;
}

Point& Point::operator+(Point& rhs){
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Point& Point::operator=(Point& rhs){
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Point::~Point()
{
}
