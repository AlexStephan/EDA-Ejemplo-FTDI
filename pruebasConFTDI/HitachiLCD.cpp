#include "HitachiLCD.h"

HitachiLCD::HitachiLCD(int iDevice)
	: lcd(iDevice)
{
	cadd = 1;
}

bool HitachiLCD::lcdInitOk() {
	bool rta;
	if (lcd.getHandler() == nullptr) {
		rta = false;
	}
	else {
		rta = true;
	}
	return rta;
}
