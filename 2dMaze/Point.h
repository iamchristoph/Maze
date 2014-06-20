#pragma once
class Point{
public:
	int x;
	int y;
	Point(int, int);
	Point();
	~Point();
	bool operator==(const Point&);
};