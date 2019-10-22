#pragma once
#include "MVC_observer.h"
#include "Twitter_Model.h"
#include <stdint.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"

#define MAX_UNAME 16
#define MAX_VEL 10


class Twitter_Controller :
	public MVC_observer
{
public:
	Twitter_Controller(Twitter_Model* m);
	~Twitter_Controller();
	void update(void*);
	bool isFinished(void);
	void cycle(void);

	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_EVENT_QUEUE* getEventQueue();

	void show();
	void drawWindows();

private:
	Twitter_Model* model;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ImVec4 clear_color;

	errorType::errorVar error;
	statusType::statusVar status;

	char username[MAX_UNAME];	//usuario de Twitter
	int vel;					//velocidad

	bool finished;

	int cant;					//cantidad te tuits para mostrar
	int tweetsAvailable;		//tuits encontrado por la programa
	int showThisTweet;			//numero de tuit para mostrar

	//window flags
	bool show_welcome_window;
	bool show_loading_window;
	bool show_tweet_window;
	bool show_error_window;
};

