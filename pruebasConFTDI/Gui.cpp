#include "gui.h"

#include <iostream>

using namespace std;

Gui::Gui() {

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
	userFound = false;
	showCtrlWindow = 0;
}

Gui::~Gui() {
	ImGui_ImplAllegro5_Shutdown();
	al_destroy_event_queue(queue);
	al_destroy_display(display);
}

void Gui::show() {
	ImGui::Render();
	al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
	ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
	al_flip_display();
}

bool Gui::getUserFlag() {
	return askUser;
}

ALLEGRO_DISPLAY* Gui::getDisplay() {
	return display;
}

ALLEGRO_EVENT_QUEUE* Gui::getEventQueue() {
	return queue;
}

bool Gui::askUsername() {
	bool r = false;
	ImGui::Begin("Tweet LCD ", &askUser);

	ImGui::Text("Ingrese el nombre de usuario del que desea obtener los tuits");
	ImGui::NewLine();
	ImGui::InputText("Usuario de Twitter", username, MAX_UNAME);
	ImGui::NewLine();

	if (ImGui::Button("Submit")) {
		/* TODO:
		 * llama a Model
		 * recieve information if user was found
		 */
		userFound = true;
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
	return r;
}

void Gui::drawController() {

	ImGui::Begin("LCD Controller");
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

	ImGui::NewLine();
	if (ImGui::Button("Disminuir")) {
		//...
		vel--;
		cout << "disminuyendo. velocidad: " << vel << endl;
	}

	ImGui::SameLine();
	if (ImGui::Button("Aumentar")) {
		//...
		vel++;
		cout << "aumentando. velocidad: " << vel << endl;
	}

	ImGui::NewLine();
	if (ImGui::Button("Salir")) {
		//salir
	}

	ImGui::End();

}