#pragma once
#include "basicLCD.h"
#include "LCDClass.h"
class HitachiLCD :
	public basicLCD
{
public:
	HitachiLCD(int iDevice = 5);
	~HitachiLCD();
	bool HitachiLCD::lcdInitOk();
	FT_STATUS lcdGetError();
	bool lcdClear();
	bool lcdClearToEOL();

	bool lcdMoveCursorUp();	//se mueve a la primera linea
	bool lcdMoveCursorDown();//se mueve a la segunda linea
	bool lcdMoveCursorRight();//avanza el cursor (cambia de linea si corresponde)
	bool lcdMoveCursorLeft(); //retrocede el cursor (cambia de linea si corresponde)

	bool lcdSetCursorPosition(const cursorPosition pos);
	cursorPosition lcdGetCursorPosition();

private:
	LCD lcd;
	int cadd;

	void caddToLCD();
	bool validatePosition(const cursorPosition pos);
};

