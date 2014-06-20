#include "Node.h"


Node::Node(PointNode in, int setId)
{
	
	data = in;
	next = nullptr;
	id = setId;
}

PointNode Node::getData(){

	return this->data;
}
Node::~Node()
{
}
