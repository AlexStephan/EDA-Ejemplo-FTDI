/*
	DUDAS A RESOLVER:

	con S (Accompanies display shift) = 1 en la instruccion Entry mode set:
	-avanza de la 0F a la 10 o a la 40?
	-avanza de la 4F a la 00 o a la 50?
	-en caso de ser la seguna, shiftea el display?

	con S = 0:
	-avanza de la 0F a la 40 o a la 00? (simil 4F a 00 o 40)

	NOTA:
	-Estilo C? separar en .h y .c

	-Recordar usar FT_Close(lcdHandle)

	-Hacer instrucciones con namespaces!!!




*/
#include "LCDClass.h"

using namespace std;

int main(void)
{
	LCD newLcd(5);
	if (newLcd.getHandler() != NULL) {
		newLcd.lcdWriteDR('H');
		Sleep(1);
		newLcd.lcdWriteDR('o');
		Sleep(1);
		newLcd.lcdWriteDR('l');
		Sleep(1);
		newLcd.lcdWriteDR('a');
		Sleep(1);
		newLcd.lcdWriteDR(' ');
		Sleep(1);
		newLcd.lcdWriteDR('m');
		Sleep(1);
		newLcd.lcdWriteDR('u');
		Sleep(1);
		newLcd.lcdWriteDR('n');
		Sleep(1);
		newLcd.lcdWriteDR('d');
		Sleep(1);
		newLcd.lcdWriteDR('o');
		Sleep(1);
		newLcd.lcdWriteDR('!');
		Sleep(1);
		newLcd.lcdWriteIR(LCD_CONTROL | LCD_CTRL_DISPLAY_ON | LCD_CTRL_CURSOR_ON | LCD_CTRL_BLINK_ON);
		Sleep(20000);


	}
	else {
		cout << "Oh no, me lleva la cachetada..." << endl;
	}
}