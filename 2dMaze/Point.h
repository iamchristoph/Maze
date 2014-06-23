#pragma once
class Point{
public:
	int x;
	int y;
	Point(int, int);
	Point();
	Point& operator=(Point&);
	Point& operator+(Point&);
	bool operator!=(Point&);
	bool operator==(Point&);
	~Point();
};