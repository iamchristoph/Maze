#pragma once
#include "PointNode.h"

class Node
{
public:
	PointNode data;
	Node* next;
	Node(PointNode, int);
	PointNode getData();
	int id;
	~Node();
};

