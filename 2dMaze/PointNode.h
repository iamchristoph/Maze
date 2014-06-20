#pragma once
#include "Point.h"
class PointNode
{
public:
	PointNode(Point, Point);
	PointNode();
	~PointNode();
	Point data;
	Point prev;
};

