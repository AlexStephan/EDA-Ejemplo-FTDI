#include "Twitter_Controller.h"

#include <iostream>

using namespace std;

Twitter_Controller::Twitter_Controller(Twitter_Model* m) :model(m) {

	// Setup Allegro
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_image_addon();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	display = al_create_display(1280, 860);
	al_set_window_title(display, "EDA-LCD3");

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer bindings
	ImGui_ImplAllegro5_Init(display);

	// Initialize Variables
	cursor = ImVec2(0, 0);
	vel = 5;
	cant = 0;

	show_welcome_window = false;
	show_loading_window = false;
	show_tweet_window = false;
	show_error_window = false;
}

Twitter_Controller::~Twitter_Controller() {
	ImGui_ImplAllegro5_Shutdown();
	al_destroy_event_queue(queue);
	al_destroy_display(display);
}

void Twitter_Controller::show() {
	ImGui::Render();
	al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}

ALLEGRO_DISPLAY* Twitter_Controller::getDisplay() {
	return display;
}

ALLEGRO_EVENT_QUEUE* Twitter_Controller::getEventQueue() {
	return queue;
}


bool Twitter_Controller::isFinished()
{
	return finished;
}



void Twitter_Controller::cycle() 
{
	error = model->getError();
	status = model->getStatus();

	//setting the window flags
	if (error == errorType::NONE) 
	{
		show_error_window = false;

		switch (status) 
		{
		case statusType::WELCOME:
			show_welcome_window = true;
			show_loading_window = false;
			show_tweet_window = false;
			break;

		case statusType::LOADING:
			show_welcome_window = true;
			show_loading_window = true;
			show_tweet_window = false;
			break;

		case statusType::FINISHED_LOADING:
		case statusType::STOPPED_LOADING:
		case statusType::SHOW_TWEET:
			show_welcome_window = true;
			show_loading_window = false;
			show_tweet_window = true;
			break;


		case statusType::GOODBYE:
			show_welcome_window = false;
			show_loading_window = false;
			show_tweet_window = false;
		}
	}
	//error
	else 
	{
		show_error_window = true;

		show_welcome_window = true;
		show_loading_window = false;
		show_tweet_window = false;
	}

	drawWindows();
}

void Twitter_Controller::drawWindows()
{
	if (show_welcome_window) 
	{
		ImGui::Begin("Tweet LCD ");

		ImGui::Text("Por favor, ingrese el nombre de usuario del que desea \nobtener los tuits y la cantidad de tuits a bajar.");
		ImGui::NewLine();
		ImGui::InputText("Usuario de Twitter", username, MAX_UNAME);
		ImGui::NewLine();
		ImGui::InputInt("Cantidad de tuits", &cant);
		if (cant < 1) { cant = 1; }
		ImGui::Text("Si no elige una cantidad, se usara el default de Twitter");
		ImGui::NewLine();

		if (ImGui::Button("Submit")) {

			model->setNumberOfTweets(cant);
			model->setUser(username);
			/* TO DO:
			 * recieve information if user was found
			 */
		}
		ImGui::End();
	}
	if (show_loading_window)
	{
		ImGui::Begin("Output");
		ImGui::Text("Cargando tuits...");
		if (ImGui::Button("Stop")) {

			//TODO: stop descarga

			tweetsAvailable = model->getNumberOfTweets();
		}
		ImGui::End();
	}

	if (show_tweet_window)
	{
		ImGui::Begin("LCD Controller");
		ImGui::Text("Desgargado %d tuits", tweetsAvailable);
		ImGui::Text("Mostrando tuits del usuario @%s", username);
		ImGui::NewLine();
		ImGui::Text("Opciones:");
		ImGui::NewLine();
		ImGui::InputInt("Tuit para mostrar", &showThisTweet);
		if (showThisTweet > tweetsAvailable) { showThisTweet = tweetsAvailable; }
		if (showThisTweet < 1) { showThisTweet = 1; }

		ImGui::NewLine();
		ImGui::Text("Velocidad: %d", vel);
		ImGui::SliderInt("Velocidad", &vel, 0, MAX_VEL);
		ImGui::NewLine();

		ImGui::NewLine();
		if (ImGui::Button("Mostrar")) {
			//TODO: mostrar
		}

		if (ImGui::Button("Salir")) {
			//TODO: salir
		}

		ImGui::End();
	}
}
