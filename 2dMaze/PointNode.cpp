#include "PointNode.h"


PointNode::PointNode(Point first, Point second)
{
	data.x = first.x;
	data.y = first.y;
	prev.x = second.x;
	prev.y = second.y;
}

PointNode::PointNode(){
	data.x = 0;
	data.y = 0;
	prev.x = 0;
	prev.y = 0;
}


PointNode::~PointNode()
{
}

