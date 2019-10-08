#include "HitachiLCD.h"

HitachiLCD::HitachiLCD(int iDevice)
	: lcd(iDevice), cadd(1)
{
}

HitachiLCD::~HitachiLCD()
{//Llama al destructor de su dato miembro LCD
}



bool HitachiLCD::lcdInitOk() {
	bool rta = true;
	if (lcd.getStatus() != FT_OK) {
		rta = false;
	}
	return rta;
}

FT_STATUS HitachiLCD::lcdGetError() {
	return lcd.getStatus();//check!!
}

bool HitachiLCD::lcdClear() {
	if (lcdInitOk() == false) {
		return false;
	}

	lcd.lcdWriteIR(LCD_CLEAR);
	Sleep(2); //por las dudas
	cadd = 1;
	return true;
}
bool HitachiLCD::lcdClearToEOL() {
	if (lcdInitOk() == false)
		return false;

	int tempcadd = (cadd - 1) % 16;
	for (; tempcadd < 16; tempcadd++)
	{
		lcd.lcdWriteDR(' ');
		Sleep(1);
	}

	caddToLCD();
	return true;
}

bool HitachiLCD::lcdMoveCursorUp()
{
	if (lcdInitOk() == false)
		return false;

	if (cadd > 16)
		cadd -= 16;
	caddToLCD();

	return true;
}

bool HitachiLCD::lcdMoveCursorDown()
{
	if (lcdInitOk() == false)
		return false;

	if (cadd < 17)
		cadd += 16;
	caddToLCD();

	return true;
}

bool HitachiLCD::lcdMoveCursorRight() {
	if (lcdInitOk() == false)
		return false;
	//NOTA: dado que la instruccion set DDRAM address consume el mismo tiempo que Cursor shift, se opta por la primera, aprovechando el metodo privado caddToLCD
	cadd++;
	if (cadd > 32)
		cadd = 1;
	caddToLCD();

	return true;
}

bool HitachiLCD::lcdMoveCursorLeft()
{
	if (lcdInitOk() == false)
		return false;
	//NOTA: dado que la instruccion set DDRAM address consume el mismo tiempo que Cursor shift, se opta por la primera, aprovechando el metodo privado caddToLCD
	cadd--;
	if (cadd < 1)
		cadd = 32;
	caddToLCD();

	return true;
}

bool HitachiLCD::lcdSetCursorPosition(const cursorPosition pos)
{
	if (lcdInitOk() == false)
		return false;
	if (validatePosition(pos) == false)
		return false;

	cadd = (16 * pos.row) + pos.column + 1;
	caddToLCD();

	return true;
}

cursorPosition HitachiLCD::lcdGetCursorPosition()
{
	cursorPosition pos;
	pos.row = (cadd - 1) / 16;
	pos.column = (cadd - 1) % 16;
	return pos;
}

void HitachiLCD::caddToLCD() {
	if (cadd < 17) //1 a 16
		lcd.lcdWriteIR(LCD_SET_ADD | LCD_FIRSTLINE | ((cadd - 1) % 16));
	else //17 a 32
		lcd.lcdWriteIR(LCD_SET_ADD | LCD_SECONDLINE | ((cadd - 1) % 16));
	Sleep(1);
}

bool HitachiLCD::validatePosition(const cursorPosition pos)
{
	if (pos.column < 0 || pos.column > 15 || pos.row < 0 || pos.row > 1) {
		return false;
	}
	return true;
}