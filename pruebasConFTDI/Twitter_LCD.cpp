#include "Twitter_LCD.h"

#include <cstring>

Twitter_LCD::Twitter_LCD() :
	lcd(nullptr),
	lcdReadyToUse(false),
	speed(0),
	error(errorType::NONE),
	status(statusType::WELCOME),
	numberOfTweets(0),
	currentTweetNumber(0),
	newChanges(false)
{
	strcpy(user, "");
	strcpy(tweet, "");
	strcpy(date, "");
}

Twitter_LCD::~Twitter_LCD()
{
}

void Twitter_LCD::attachLCD(basicLCD* lcd)
{
	this->lcd = lcd;
	if (lcd->lcdInitOk() == true)
		lcdReadyToUse = true;
	else
		lcdReadyToUse = false;
}

void Twitter_LCD::detachLCD(void)
{
	this->lcd = nullptr;
	lcdReadyToUse = false;
}

basicLCD* Twitter_LCD::getLCD(void)
{
	return lcd;
}

void Twitter_LCD::update(void* model)
{ //no se comunica aun con el LCD, solo organiza la informacion
	newChanges = true;
	Twitter_Model* Tmodel = (Twitter_Model*)model;



}