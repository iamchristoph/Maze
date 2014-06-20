#include "Set.h"


Set::Set()
{
}

void Set::add(PointNode toAdd){
	if (!search(toAdd.data)){
		data.push_back(toAdd);
	}

}

PointNode Set::getPoint(Point find){
	for (int i = 0; i < data.size(); i++){
		if (data.at(i).data == find){
			return data.at(i);
		}
	}
}

bool Set::search(Point find){

	for (int i = 0; i < data.size(); i++){
		if (data.at(i).data == find){
			return true;
		}
	}
	return false;
}

Set::~Set()
{
}
