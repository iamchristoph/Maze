

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include "Pathfinder.h"
#include "Map.h"

using namespace std;

int displayHeight = 600;
int displayWidth = 800;


int main(){
	const float FPS = 40;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_TIMER* opponentSpeed = NULL;
	ALLEGRO_TIMEOUT* dontWait;
	//al_init_timeout(dontWait, .000001);


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
	opponentSpeed = al_create_timer(30);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(opponentSpeed));
	//setup drawing
	al_init_image_addon();
	//al_init_primitives_addon();
	Map level("map.txt");
	Map computer("map.txt");
	//create a path to the end of the level
	Pathfinder finder;
	finder.importMaze("map2.txt");
	finder.solveMaze();
	//stack<Point> path = finder.return_path();
	


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
				//computer.movePlayer(path.top());
				//path.pop();
				gameOver = true;

			}
			//check if the level is finished
			if (level.levelFinished()){
				gameOver = true;
			}
			
			ALLEGRO_BITMAP* left = level.createMapCopy(displayWidth / 2, displayHeight);
			ALLEGRO_BITMAP* right = computer.createMapCopy(displayWidth / 2, displayHeight);

			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(left, 0, 0, 0);
			al_draw_bitmap(right, displayWidth / 2, 0, 0);
			al_destroy_bitmap(left);
			al_destroy_bitmap(right);
			al_flip_display();
		}

		//send event when key pressed
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			//point that player wants to move to
			Point playLoc;
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_RIGHT:
				playLoc = level.getPlayerLocation();
				playLoc.x += 1;
				level.movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_LEFT:

				playLoc = level.getPlayerLocation();
				playLoc.x -= 1;
				level.movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_UP:
				
				playLoc = level.getPlayerLocation();
				playLoc.y -= 1;
				level.movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_DOWN:
				
				playLoc = level.getPlayerLocation();
				playLoc.y += 1;
				level.movePlayer(playLoc);
				
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameOver = true;
				break;

			}
		}
	}
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);


	return 0;
}
