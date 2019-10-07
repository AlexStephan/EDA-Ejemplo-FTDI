#pragma once
#include "basicLCD.h"
#include "LCDClass.h"
class HitachiLCD :
	public basicLCD
{
public:
	HitachiLCD(int iDevice = 5);
	bool HitachiLCD::lcdInitOk();
private:
	LCD lcd;
};

