#pragma once
#include <stdint.h>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"

#define MAX_UNAME 16

class Gui {

public:
	Gui();
	~Gui();

	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_EVENT_QUEUE* getEventQueue();

	void show();
	bool askUsername();
	bool getUserFlag();

	void drawController();

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ImVec2 cursor;
	ImVec4 clear_color;

	bool askUser;
	char username[MAX_UNAME];
	int vel;					//velocidad

	bool userFound;
	int showCtrlWindow;

};