#include "pQueue.h"


pQueue::pQueue(Point dest)
{
	destination.x = dest.x;
	destination.y = dest.y;
	head = nullptr;
}

bool pQueue::add(PointNode toAdd){
	if (search(toAdd.data)){
		return false;
	}
	else{
		int dist, distX, distY;
		distX = toAdd.data.x - this->destination.x;
		distY = toAdd.data.y - this->destination.y;
		if (distX < 0)distX *= -1;
		if (distY < 0)distY *= -1;
		dist = distX + distY;

		Node* current = new Node(toAdd, dist);
		Node* traverse = head;
		if (head == nullptr){
			head = current;
			return true;
		}
		else{
			if (traverse->id >= current->id){
				head = current;
				current->next = traverse;
				return true;
			}
			else if (traverse->next == nullptr){
				traverse->next = current;
				return true;
			}
			else{
				while (traverse->next->id >= current->id){
					traverse = traverse->next;

					if (traverse->next == nullptr){
						traverse->next = current;
						return true;
					}
				}
				current->next = traverse->next;
				traverse->next = current;

				return true;
			}

		}

	}
}

bool pQueue::search(Point search){
	Node* traverse = head;
	if (head == nullptr){ return false; }
	else{
		if (head->data.data == search)return false;
		while (traverse != nullptr){
			if (traverse->data.data == search){
				return true;
			}
			traverse = traverse->next;
		}
		return false;
	}
}

PointNode pQueue::top(){
	if (head != nullptr){
		PointNode out = head->getData();
		return out;
	}
}

void pQueue::pop(){
	if (head != nullptr){
		Node* out = head;
		head = head->next;
		delete out;
	}
}


pQueue::~pQueue()
{
	
}
