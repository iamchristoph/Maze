#include "Map.h"


Map::Map(string filePath)
{
	goalFound = false;
	//create the vector map
	std::ifstream file;
	file.open(filePath);
	while (!file.eof()){
		vector<int> store;
		while (file.peek() != '\n'){

			int num;
			file >> num;
			if (file.fail())break;
			store.push_back(num);

		}

		file.ignore();
		map.push_back(store);
		store.clear();
	}
	file.close();
	//create the tiles for the map
	canGo = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(canGo);
	al_clear_to_color(al_map_rgb(0, 255, 0));
	noGo = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(noGo);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	goal = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(goal);
	al_clear_to_color(al_map_rgb(177, 177, 0));
	level = al_create_bitmap(TILE_SIZE*map[0].size(), TILE_SIZE*map.size());

		//find and create players
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){

			if (map[i][j] == 2){
				person.setX(j);
				person.setY(i);
				
			}

		}



	}
	updateBitmap();

}

void Map::updateBitmap(){

	al_set_target_bitmap(level);
	int TILE_SIZE = al_get_bitmap_width(person.getPlayer());
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){
			if (map[i][j] == 1){
				al_draw_bitmap(noGo, j*TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (map[i][j] == 0){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (map[i][j] == 2){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
				
			}
			else if (map[i][j] == 3){
				al_draw_bitmap(goal, j * TILE_SIZE, i * TILE_SIZE, 0);
			}

		}
		Point location = person.getLocation();
		al_draw_bitmap(person.getPlayer(), location.x * TILE_SIZE, location.y * TILE_SIZE, 0);

	}
}

void Map::movePlayer(Point newLocation){

	if (newLocation.x >= 0 && newLocation.x < map[0].size() && newLocation.y < map.size() && newLocation.y >= 0){
		
		if (map[newLocation.y][newLocation.x] == 1){

		}
		else{
			person.move(newLocation);
			if (map[newLocation.y][newLocation.x] == 3){
			goalFound = true;
			
			}
		}
	}

	updateBitmap();
	
}

ALLEGRO_BITMAP* Map::createMapCopy(int width, int height){
	ALLEGRO_BITMAP* out = al_create_bitmap(width, height);
	al_set_target_bitmap(out);
	Point location = person.getLocation();
	al_draw_bitmap_region(level, TILE_SIZE*location.x- width/2, TILE_SIZE * location.y - height / 2, width, height, 0, 0, 0);
	return out;
}

Point Map::getPlayerLocation(){
	return person.getLocation();
}
bool Map::levelFinished(){
	return goalFound;
}

Map::~Map()
{


}
