#include "HitachiLCD.h"

HitachiLCD::HitachiLCD(int iDevice)
	: lcd(iDevice)
{
	cadd = 1;
}

bool HitachiLCD::lcdInitOk() {
	bool rta;
	if (lcd.getStatus() != FT_OK) {
		rta = false;
	}
	else {
		rta = true;
	}
	return rta;
}

FT_STATUS HitachiLCD::lcdGetError() {
	return lcd.getStatus();
}

bool HitachiLCD::lcdClear() {
	if (lcdInitOk() == false) {
		return false;
	}

	lcd.lcdWriteIR(LCD_CLEAR);
	Sleep(1);
	cadd = 1;
	return true;
}
bool HitachiLCD::lcdClearToEOL() {
	int tempcadd = (cadd - 1) % 16;
	for (; tempcadd < 16; tempcadd++)
	{
		lcd.lcdWriteDR(' ');
		Sleep(1);
	}

	caddToLCD();
}

void HitachiLCD::caddToLCD() {
	if (cadd < 17)
	{
		lcd.lcdWriteIR(LCD_SET_ADD | LCD_FIRSTLINE | (cadd - 1) % 16);
	}
	else
		lcd.lcdWriteIR(LCD_SET_ADD | LCD_SECONDLINE | (cadd - 1) % 16);
}