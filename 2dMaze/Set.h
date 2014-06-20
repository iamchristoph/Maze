#pragma once
#include "Point.h"
#include "PointNode.h"
#include <vector>

class Set
{
public:
	Set();
	bool search(Point);
	PointNode getPoint(Point);
	void add(PointNode);
	~Set();

private:
	
	 std::vector<PointNode> data;
};

