#include "Twitter_LCD.h"

#include <cstring>

Twitter_LCD::Twitter_LCD() :
	lcd(nullptr),
	lcdReadyToUse(false),

	user(),
	tweet(),
	date(),
	speed(0),
	error(errorType::NONE),
	status(statusType::WELCOME),
	numberOfTweets(0),
	currentTweetNumber(0),
	newChanges(false)
{
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

	user.clear();
	tweet.clear();
	date.clear();
	speed = 0;
	status = statusType::WELCOME;
	numberOfTweets = 0;
	currentTweetNumber = 0;

	error = Tmodel->getError();
	if (error == errorType::NONE) {
		status = Tmodel->getStatus();

		switch (status) {
		case statusType::WELCOME:
		case statusType::GOODBYE:
			//No se necesita mas informacion
			break;
		case statusType::LOADING:
			const char* l;
			if ((l = Tmodel->getUser()) != nullptr)
				user = l;
			break;
		case statusType::FINISHED_LOADING:
		case statusType::STOPPED_LOADING:
			numberOfTweets = Tmodel->getNumberOfTweets();
			break;
		case statusType::SHOW_TWEET:
			const char* c;
			if ((c = Tmodel->getUser()) != nullptr)
				user = c;
			if ((c = Tmodel->getTuit()) != nullptr)
				tweet = c;
			if ((c = Tmodel->getDate()) != nullptr)
				date = c;
			speed = Tmodel->getSpeed();
			numberOfTweets = Tmodel->getNumberOfTweets();
			currentTweetNumber = Tmodel->getCurrentTweetNumber();
			break;
		}
	}

}