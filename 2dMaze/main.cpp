

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Map.h"
#include "Point.h"
#include "Pathfinder.h"


using namespace std;

int displayHeight = 600;
int displayWidth = 800;

string toString(int);

int main(){
	const float FPS = 40;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_TIMER* opponentSpeed = NULL;
	
	

	al_init();

	//setup for events
	event_queue = al_create_event_queue();
	//setup for display
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	
	display = al_create_display(displayWidth, displayHeight);

	
	//setup for keyboard
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//setup for timer
	timer = al_create_timer(1 / FPS);
	opponentSpeed = al_create_timer(.2);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(opponentSpeed));

	//setup drawing
	al_init_image_addon();

	//al_init_primitives_addon();
	//plevel tracks the current players level
	int plevel = 1;
	int clevel = 1;
	
	Map* level = new Map("resource/map" + toString(plevel) + ".txt");
	
	Map* computer = new Map("resource/map1.txt");

	//create a path to the end of the level
	Pathfinder finder("resource/map1.txt");
	//stack<Point> path;
	//path = finder.return_path();
	finder.createRandomMaze(30, 30, "resource/generatedMap.txt");
	
	

	
	bool gameOver = false;
	//drawMap(map);
	
	al_start_timer(timer);
	al_start_timer(opponentSpeed);

	while (!gameOver){
		



		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//main drawing function
		if (ev.type == ALLEGRO_EVENT_TIMER){
			if(ev.timer.source == opponentSpeed){
				if (finder._path.empty()){
					finder.getPath(computer->getPlayerLocation()) // get next steps using current location as start
				}

				else {
					computer->movePlayer(finder._path.top());
					finder._path.pop();
				
				}
				//gameOver = true;

			}
			//check if the level is finished
			
			
			ALLEGRO_BITMAP* left = level->createMapCopy(displayWidth / 2, displayHeight);
			ALLEGRO_BITMAP* right = computer->createMapCopy(displayWidth / 2, displayHeight);

			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(left, 0, 0, 0);
			al_draw_bitmap(right, displayWidth / 2, 0, 0);
			al_destroy_bitmap(left);
			al_destroy_bitmap(right);
			al_flip_display();

			if (level->levelFinished()){
				//gameOver = true;
				delete level;
				string next = "resource/map";
				plevel++;
				next += toString(plevel);
				next += ".txt";
				try{
					level = new Map(next);
				}
				catch (int e){ if (e == 1)gameOver = true; }
			}
			if (computer->levelFinished()){
				//gameOver = true;

				delete computer;
				string next = "resource/map";
				clevel++;
				next += toString(clevel);
				next += ".txt";
				try{
					computer = new Map(next);

					finder.importMaze(next);
					path = finder.return_path();
				}
				catch (int e){ if (e == 1)gameOver = true; }
			}
		}
		
		//send event when key pressed
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			//point that player wants to move to
			Point playLoc;
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_RIGHT:
				playLoc = level->getPlayerLocation();
				playLoc.x += 1;
				level->movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_LEFT:

				playLoc = level->getPlayerLocation();
				playLoc.x -= 1;
				level->movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_UP:
				
				playLoc = level->getPlayerLocation();
				playLoc.y -= 1;
				level->movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_DOWN:
				
				playLoc = level->getPlayerLocation();
				playLoc.y += 1;
				level->movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameOver = true;
				break;

			}
		}
	}
	system("pause");
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);


	return 0;
}

string toString(int in){
	string out;
	stringstream ss;
	ss << in;
	ss >> out;

	return out;
}