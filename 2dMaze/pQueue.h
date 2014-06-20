#pragma once
#include "Point.h"
#include "PointNode.h"
#include "Node.h"

class pQueue
{
public:
	pQueue(Point);
	~pQueue();

	bool add(PointNode);
	PointNode top();
	void pop();
	bool search(Point);
private:
	
	Point destination;
	Node* head;
};

