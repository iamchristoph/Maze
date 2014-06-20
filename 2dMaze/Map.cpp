#include "Map.h"


Map::Map(string filePath)
{
	goalFound = false;
	//create the vector map
	std::ifstream file;
	file.open(filePath);
	if (!file){ throw 1; }
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
	
	canGo = al_load_bitmap("resource/ground40.png");
	noGo = al_load_bitmap("resource/water40.png");
	//goal = al_load_bitmap("");
	goal = al_load_bitmap("resource/door.png");
	al_convert_mask_to_alpha(goal, al_map_rgb(32, 114, 157));
	entrance = al_load_bitmap("resource/odoor.png");
	al_convert_mask_to_alpha(entrance, al_map_rgb(32, 114, 157));

	al_convert_mask_to_alpha(goal, al_map_rgb(32, 114, 157));
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
	
	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){
			if (map[i][j] == 0){
					al_draw_bitmap(noGo, j*TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (map[i][j] == 1){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (map[i][j] == 2){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
				al_draw_bitmap(entrance, j * TILE_SIZE, i * TILE_SIZE, 0);

				
			}
			else if (map[i][j] == 3){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
				al_draw_bitmap(goal, j * TILE_SIZE, i * TILE_SIZE, 0);

			}

		}
		Point location = person.getLocation();
		al_draw_bitmap(person.getPlayer(), location.x * TILE_SIZE, location.y * TILE_SIZE, 0);

	}
}

void Map::movePlayer(Point newLocation){
	//overwrite the player location
	Point location = person.getLocation();
	al_set_target_bitmap(level);
	al_draw_bitmap(canGo, location.x * TILE_SIZE, location.y * TILE_SIZE, 0);

	if (newLocation.x >= 0 && newLocation.x < map[0].size() && newLocation.y < map.size() && newLocation.y >= 0){
		
		if (map[newLocation.y][newLocation.x] == 0){
		cout << "invalid tile at " << newLocation.x << ", " << newLocation.y << endl;
		}
		else{
			person.move(newLocation);
			if (map[newLocation.y][newLocation.x] == 3){
			goalFound = true;
			
			}
		}
	}
	//draw the player
	location = person.getLocation();
	al_draw_bitmap(person.getPlayer(), location.x * TILE_SIZE, location.y * TILE_SIZE, 0);
	//updateBitmap();
	
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
	/*al_destroy_bitmap(canGo);
	al_destroy_bitmap(noGo);
	al_destroy_bitmap(goal);*/
	//al_destroy_bitmap(level);

}
