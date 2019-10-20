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
#define DEFAULT_CANT 10		//??

class Twitter_Controller :
	public MVC_observer
{
public:
	Twitter_Controller(Twitter_Model* m) : model(m){};
	~Twitter_Controller();
	virtual void update(void*) {};
	bool isFinished(void) {};
	void cycle(void) {};

	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_EVENT_QUEUE* getEventQueue();

	void show();
	bool askUsername();
	bool getUserFlag();

	void drawController();
	void setMyModel(Twitter_Model*);

private:
	Twitter_Model* model;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ImVec2 cursor;
	ImVec4 clear_color;

	Twitter_Model* mimodel;		//un puntero al model

	bool askUser;
	char username[MAX_UNAME];
	int vel;					//velocidad

	bool userFound;
	int cant;					//cantidad te tuits para mostrar
	int show_download_window;
	int downloadDone;
	int tweetsAvailable;
};

