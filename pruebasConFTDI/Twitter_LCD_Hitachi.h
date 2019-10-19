#pragma once
#include "Twitter_LCD.h"
#include <chrono>
#include <ratio>

using namespace std;
using namespace std::chrono;

class Twitter_LCD_Hitachi :
	public Twitter_LCD
{
public:
	Twitter_LCD_Hitachi();
	~Twitter_LCD_Hitachi();

	virtual void step(void);
private:
	string phraseToScroll;
	size_t sizeofPhrase;
	bool scrollPhase;	//La frase es demasiado larga para el display? es decir, es necesario scrollearla?
	bool beginningOfPhrase; //La frase a scrollear se encuentra en su posicion inicial. Es necesario que pase algo de tiempo antes de empezar a scrollearla (mayor al tiempo entre scrolls)
	duration<int, ratio<1, 1000>> timeBetweenScrolls; //Tiempo entre scrolls
	time_point<system_clock> lastScroll;

	//Modo LOADING
	unsigned char currentLoadSymbol; //contador 0 a 11, que hace el siguiente loop:   |{(<({|})>)}|
	time_point<system_clock> loadSymbolTime;





	//MODO SHOW_TWEET
	string formattedCurrent;
	string formattedDate;
	string formattedTweet;

};

