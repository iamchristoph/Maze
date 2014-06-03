

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

const int TILE_SIZE = 40;
int displayHeight = 600;
int displayWidth = 800;



void drawMap(vector<vector<int>> v);

int main(){
	const float FPS = 40;
	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//ALLEGRO_TIMER *timer = NULL;
	
	vector<vector<int>> map;
	vector<int> p;

	ifstream file;
	file.open("map.txt");
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


	al_init();
	//setup for events
	event_queue = al_create_event_queue();
	//setup for display
	//al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(displayWidth, displayHeight);
	//setup for keyboard
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//setup for timer
	//timer = al_create_timer(1 / FPS);
	//al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//setup drawing
	al_init_image_addon();
	//al_init_primitives_addon();


	bool gameOver = false;
	drawMap(map);
	
	//al_start_timer(timer);

	while (!gameOver){




		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//main drawing function
		/*if (ev.type == ALLEGRO_EVENT_TIMER){

			draw = true;
		}*/

		//send event when key pressed
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			bool found = false;
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_RIGHT:
				for (int i = 0; i < map.size(); i++){
					for (int j = 0; j < map[i].size(); j++){
						if (map[i][j] == 2){
							//if off map or not valid spot then break
							if (j + 1 > map[i].size() || map[i][j + 1] == 1){
								break;
							}
							//move the player
							else{
								map[i][j] = 0;
								map[i][j + 1] = 2;
								break;
							}
						}
					}
				}
				al_set_target_bitmap(al_get_backbuffer(display));
				al_clear_to_color(al_map_rgb(0, 0, 0));
				drawMap(map);
				al_flip_display();
				break;
			case ALLEGRO_KEY_LEFT:
				for (int i = 0; i < map.size(); i++){
					for (int j = 0; j < map[i].size(); j++){
						if (map[i][j] == 2){
							//if off map or not valid spot then break
							if (j - 1 < 0 || map[i][j - 1] == 1){
								break;
							}
							//move the player
							else{
								map[i][j] = 0;
								map[i][j - 1] = 2;
								break;
							}
						}
					}
				}
				al_set_target_bitmap(al_get_backbuffer(display));
				al_clear_to_color(al_map_rgb(0, 0, 0));
				drawMap(map);
				al_flip_display();
				break;
			case ALLEGRO_KEY_UP:
				for (int i = 0; i < map.size(); i++){
					for (int j = 0; j < map[i].size(); j++){
						if (map[i][j] == 2){
							//if off map or not valid spot then break
							if (i - 1 < 0 || map[i - 1][j] == 1){
								break;
							}
							//move the player
							else{
								map[i][j] = 0;
								map[i - 1][j] = 2;
								break;
							}
						}
					}
				}
				al_set_target_bitmap(al_get_backbuffer(display));
				al_clear_to_color(al_map_rgb(0, 0, 0));
				drawMap(map);
				al_flip_display();
				break;
			case ALLEGRO_KEY_DOWN:
				
				for (int i = 0; i < map.size(); i++){
					for (int j = 0; j < map[i].size(); j++){
						if (map[i][j] == 2){
							//if off map or not valid spot then break
							if (i + 1 > map.size() || map[i + 1][j] == 1){
								break;
							}
							//move the player
							else{
								map[i][j] = 0;
								map[i + 1][j] = 2;
								found = true;
								break;
							}
						}
						if (found == true)break;
					}
				}
				al_set_target_bitmap(al_get_backbuffer(display));
				al_clear_to_color(al_map_rgb(0, 0, 0));
				drawMap(map);
				al_flip_display();
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameOver = true;
				break;
			case ALLEGRO_KEY_SPACE:
				al_set_target_bitmap(al_get_backbuffer(display));
				drawMap(map);
				al_flip_display();
				break;

			}
		}
	}
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	//al_destroy_timer(timer);


	return 0;
}

void drawMap(vector<vector<int>> file){
	
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();


	ALLEGRO_BITMAP* bitmap = al_create_bitmap(file[0].size()*TILE_SIZE, file.size()*TILE_SIZE);
	ALLEGRO_BITMAP* canGo = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(canGo);
	al_clear_to_color(al_map_rgb(0, 255, 0));
	ALLEGRO_BITMAP* noGo = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(noGo);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	ALLEGRO_BITMAP* player = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	al_set_target_bitmap(player);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	int playerX, playerY;

	al_set_target_bitmap(bitmap);
	for (int i = 0; i < file.size(); i++){
		for (int j = 0; j < file[i].size(); j++){
			if (file[i][j] == 1){
				al_draw_bitmap(noGo, j*TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (file[i][j] == 0){
				al_draw_bitmap(canGo, j * TILE_SIZE, i * TILE_SIZE, 0);
			}
			else if (file[i][j] == 2){
				al_draw_bitmap(player, j * TILE_SIZE, i * TILE_SIZE, 0);
				playerX = j * TILE_SIZE;
				playerY = i * TILE_SIZE;
			}

		}



	}
		al_set_target_bitmap(temp);
		al_draw_bitmap_region(bitmap, playerX - displayWidth / 2, playerY - displayHeight / 2, displayWidth, displayHeight, 0, 0, 0);

		al_destroy_bitmap(canGo);
		al_destroy_bitmap(noGo);
		al_destroy_bitmap(bitmap);
		al_destroy_bitmap(player);

	
}