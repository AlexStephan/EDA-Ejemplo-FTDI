#pragma once
#include "Twitter_LCD.h"
#include <chrono>
#include <ratio>



typedef unsigned int time_interval_type;
typedef std::chrono::duration<time_interval_type, std::ratio<1, 1000>> interval;


class Twitter_LCD_Hitachi :
	public Twitter_LCD
{
public:
	Twitter_LCD_Hitachi();
	~Twitter_LCD_Hitachi();

	virtual void step(void);
private:
	std::string phraseToScroll;
	size_t sizeofPhrase;
	bool scrollPhrase;	//La frase es demasiado larga para el display? es decir, es necesario scrollearla?
	bool beginningOfPhrase; //La frase a scrollear se encuentra en su posicion inicial. Es necesario que pase algo de tiempo antes de empezar a scrollearla (mayor al tiempo entre scrolls)
	interval timeBetweenScrolls; //Tiempo entre scrolls
	std::chrono::time_point<std::chrono::system_clock> lastScroll;
	size_t actualPosition;


	//Modo LOADING
	unsigned char currentLoadSymbol; //contador 0 a 11, que hace el siguiente loop:   |{(<({|})>)}|
	std::chrono::time_point<std::chrono::system_clock> loadSymbolTime;


	//MODO SHOW_TWEET
	std::string formattedCurrent;
	std::string formattedDate;
	std::chrono::time_point<std::chrono::system_clock> tweetStartTime;
	bool alreadySeeingDate;


	void control_NewChanges(void);
	void control_NoChanges(void);

	//llamar con set_scrollingPhrase conteniendo el "mensaje crudo" (sin espacios adicionales al final)
	void set_scrollingPhrase(double setspeed, unsigned int line);
	void manage_scrollingPhrase(unsigned int line);
};

