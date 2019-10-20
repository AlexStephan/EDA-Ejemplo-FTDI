//NOTA: este archivo quedara obsoleto (en su lugar, emplear tp9main.cpp) y se empleara solo para pruebas

/*
	DUDAS A RESOLVER:

	con S (Accompanies display shift) = 1 en la instruccion Entry mode set:
//	-avanza de la 0F a la 10 o a la 40?
//	-avanza de la 4F a la 00 o a la 50?
//	-en caso de ser la seguna, shiftea el display?

	con S = 0:
	-avanza de la 0F a la 40 o a la 00? (simil 4F a 00 o 40)

	NOTA:
	-Estilo C? separar en .h y .c

	-Recordar usar FT_Close(lcdHandle)

	-Hacer instrucciones con namespaces!!!




*/

#define ONE_SENTENCE 1
#define CURSOR_MOVE	2
#define LCD_MODE ONE_SENTENCE



#include "HitachiLCD.h"
#include "Twitter_Controller.h"

using namespace std;

void loop(HitachiLCD lcd);
void launchGui();

int not_main_anymore(void)
{
	/*
	HitachiLCD lcd(5);
	if (lcd.lcdInitOk() == true) {



		cout << "Oh yeah!" << endl;
		lcd << "Oh yeah Mr. Crabs!";
		Sleep(1000);
		lcd.lcdClear();

		loop(lcd);
	}
	else {
		cout << "Que sad... :(" << endl;
	}
	*/
	launchGui();
	return 0;
}

void launchGui() {
	Twitter_Controller testi;

	bool running = true;
	while (running)
	{
		ALLEGRO_EVENT ev;
		while (al_get_next_event(testi.getEventQueue(), &ev))
		{
			ImGui_ImplAllegro5_ProcessEvent(&ev);
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}
			if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				ImGui_ImplAllegro5_InvalidateDeviceObjects();
				al_acknowledge_resize(testi.getDisplay());
				ImGui_ImplAllegro5_CreateDeviceObjects();
			}
		}

		//Start Dear ImGui frame
		ImGui_ImplAllegro5_NewFrame();
		ImGui::NewFrame();

		//Pide input del ususario
		if (testi.getUserFlag()) {
			if (!testi.askUsername() && !testi.getUserFlag()) {
				break;
			}
		}

		// Rendering
		testi.show();
}

}

#if LCD_MODE == ONE_SENTENCE

void loop(HitachiLCD lcd) {
	char c = 0;
	bool salir = false;
	while (salir == false) {
		cin >> noskipws >> c;
		switch (c) {
		case '~':
			salir = true;
			break;
		case '\n':
			cursorPosition pos = lcd.lcdGetCursorPosition();
			if (pos.column == 0 && pos.row == 0) {
				//do nothing
			}
			else {
				lcd.lcdClearToEOL();
				if (pos.row == 0) {
					lcd.lcdSetCursorPosition(cursorPosition{ 1,0 });
					lcd.lcdClearToEOL();
				}
				lcd.lcdSetCursorPosition(cursorPosition{ 0,0 });
			}



			break;
		default:
			lcd << c;
			break;
		}
	}
}

#elif LCD_MODE == CURSOR_MOVE

void loop(HitachiLCD lcd) {
	char c = 0;
	bool salir = false;
	while (salir == false) {
		cin >> noskipws >> c;
		switch (c) {
		case '8':
			lcd.lcdMoveCursorUp();
			break;
		case '4':
			lcd.lcdMoveCursorLeft();
			break;
		case '6':
			lcd.lcdMoveCursorRight();
			break;
		case '2':
			lcd.lcdMoveCursorDown();
			break;
		case '~':
			salir = true;
			break;
		case '\n':
			//Do nothing at all!
			break;
		default:
			lcd << c;
			break;
		}
	}
}


#else
	//Missing//

#endif
