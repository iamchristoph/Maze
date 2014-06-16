	#include "player.h"


player::player(int x, int y)
{
	left = al_load_bitmap("resource/charLeft.png");
	right = al_load_bitmap("resource/charRight.png");
	up = al_load_bitmap("resource/charUp.png");
	down = al_load_bitmap("resource/charDown.png");
	current = down;
	
	location.x = x;
	location.y = y;
}
player::player(){
	
	left = al_load_bitmap("resource/charLeft.png");
	al_convert_mask_to_alpha(left, al_map_rgb(32, 114, 157));
	right = al_load_bitmap("resource/charRight.png");
	al_convert_mask_to_alpha(right, al_map_rgb(32, 114, 157));
	up = al_load_bitmap("resource/charUp.png");
	al_convert_mask_to_alpha(up, al_map_rgb(32, 114, 157));
	down = al_load_bitmap("resource/charDown.png");
	al_convert_mask_to_alpha(down, al_map_rgb(32,114,157));
	current = down;
	

}
void player::move(Point p){
	//if next to desired location
	if (p.y == location.y){
		if (p.x - location.x == 1){
			location.x = p.x;
			current = right;
			
		}
		else if (p.x - location.x == -1){
			location.x = p.x;
			current = left;
		}
		else{ cout << "tile too far away " << p.x << ", " << p.y << endl; }

	}
	else if (p.x == location.x){
		if (p.y - location.y == 1){
			
			location.y = p.y;
			current = down;
		}
		else if (p.y - location.y == -1){
			location.y = p.y;
			current = up;

		}
		else{ cout << "tile too far away " << p.x << ", " << p.y << endl; }
	}
	else{ cout << "tile too far away " << p.x << ", " << p.y << endl; }

}
void player::setX(int x){
	location.x = x;
}
void player::setY(int y){
	location.y = y;
}

Point player::getLocation(){
	return this->location;
}

ALLEGRO_BITMAP* player::getPlayer(){
	return current;
}

player::~player()
{
	/*al_destroy_bitmap(left);
	al_destroy_bitmap(right);
	al_destroy_bitmap(up);
	al_destroy_bitmap(down);*/
}
