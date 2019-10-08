#pragma once
#include "basicLCD.h"
#include "LCDClass.h"
class HitachiLCD :
	public basicLCD
{
public:
	HitachiLCD(int iDevice = 5);
	bool HitachiLCD::lcdInitOk();
	FT_STATUS lcdGetError();
	bool lcdClear();
	void caddToLCD();
	bool lcdClearToEOL();
private:
	LCD lcd;
};

