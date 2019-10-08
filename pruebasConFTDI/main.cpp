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
#define LCD_MODE CURSOR_MOVE



#include "HitachiLCD.h"

using namespace std;

void loop(HitachiLCD lcd);

int main(void)
{
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
