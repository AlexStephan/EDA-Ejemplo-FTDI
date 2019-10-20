#include "Twitter_Controller.h"

#include <iostream>

using namespace std;

Twitter_Controller::Twitter_Controller(Twitter_Model* m) {

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
	askUser = true;
	vel = 5;
	cant = 0;
	userFound = false;
	show_download_window = 0;
	downloadDone = 0;
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

bool Twitter_Controller::getUserFlag() {
	return askUser;
}

ALLEGRO_DISPLAY* Twitter_Controller::getDisplay() {
	return display;
}

ALLEGRO_EVENT_QUEUE* Twitter_Controller::getEventQueue() {
	return queue;
}

void Twitter_Controller::setMyModel(Twitter_Model* model) {
	mimodel = model;
}

bool Twitter_Controller::askUsername() {
	bool r = false;
	ImGui::Begin("Tweet LCD ", &askUser);

	ImGui::Text("Por favor, ingrese el nombre de usuario del que desea \nobtener los tuits y la cantidad de tuits a bajar.");
	ImGui::NewLine();
	ImGui::InputText("Usuario de Twitter", username, MAX_UNAME);
	ImGui::NewLine();
	ImGui::InputInt("Cantidad de tuits", &cant); //falta chequear si el numero es positivo
	ImGui::Text("Si no elige una cantidad, se usara el default de Twitter");
	ImGui::NewLine();

	if (ImGui::Button("Submit")) {
		//si el usuario no ingresó cantidad o ingresó cantidad negativo
		if (cant <= 0) {
			cant = DEFAULT_CANT;
		}

		mimodel->setNumberOfTweets(cant);
		mimodel->setUser(username);

		/* TODO:
		 * recieve information if user was found
		 */

		 //userFound = true;

		//if todo bien
		show_download_window = true;

		if (userFound) {
			askUser = false;
			/* TODO:
			 *
			 */
			cout << "ok" << endl;
		}
		else {
			//error
			askUser = true;
			cout << "not ok" << endl;
		}
	}
	ImGui::End();

	if (show_download_window) {
		ImGui::Begin("Output");
		ImGui::Text("Cargando tuits...");
		if (ImGui::Button("Stop")) {

			//TODO: stop descarga

			tweetsAvailable = mimodel->getNumberOfTweets;
			downloadDone = 1;
		}
		if (mimodel->getStatus() == statusType::FINISHED_LOADING) {
			tweetsAvailable = mimodel->getNumberOfTweets;
			downloadDone = 1;
		}
		ImGui::End();
	}

	if (downloadDone) {
		show_download_window = 0;
		drawController();

	}

	return r;
}

void Twitter_Controller::drawController() {

	ImGui::Begin("LCD Controller");
	ImGui::Text("Desgargado %d tuits", tweetsAvailable);
	ImGui::Text("Mostrando tuits del usuario @%s", username);
	ImGui::NewLine();
	ImGui::Text("Opciones:");
	ImGui::NewLine();
	if (ImGui::Button(" << anterior")) {
		//... 
		cout << "Tuit anterior" << endl;
	}

	ImGui::SameLine();
	if (ImGui::Button(" actual ")) {
		//...
		cout << "Actual de nuevo" << endl;

	}

	ImGui::SameLine();
	if (ImGui::Button("siguiente >>")) {
		//...
		cout << "Tuit siguiente" << endl;
	}

	ImGui::NewLine();
	ImGui::Text("Velocidad: %d", vel);
	ImGui::SliderInt("Velocidad", &vel, 0, MAX_VEL);
	ImGui::NewLine();

	ImGui::NewLine();
	if (ImGui::Button("Salir")) {
		//TODO: salir
	}

	ImGui::End();

}