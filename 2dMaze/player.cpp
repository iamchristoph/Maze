#include "player.h"


player::player(int x, int y)
{
	image = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	location.x = x;
	location.y = y;
}
player::player(){
	image = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(255, 117, 255));

}
void player::move(Point p){
	//if next to desired location
	if (p.y == location.y){
		if (p.x - location.x <= 1 && p.x - location.x >= -1){
			location.x = p.x;
			
		}

	}
	else if (p.x == location.x){
		if (p.y - location.y <= 1 && p.y - location.y >= -1){
			
			location.y = p.y;
		}
	}

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
	return image;
}

player::~player()
{
	al_destroy_bitmap(image);
}
