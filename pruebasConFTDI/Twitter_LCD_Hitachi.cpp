#include "Twitter_LCD_Hitachi.h"

#define BLANK_LINE "                " //Es mas rapido para el programa escribir espacios al final del mensaje, en vez de tener que limpiar por completo la linea y escribir lo correspondiente
										//Notese q lo q hace el programa para borrar una sola linea es, de hecho, escribir espacios

static const char LoadingArray[] = "|{(<({|})>)}";
#define LOADING_SIMBOL_INTERVAL 4 //mseg
#define LOADING_NAME_SPEED 3

using namespace std;
using namespace std::chrono;

Twitter_LCD_Hitachi::Twitter_LCD_Hitachi()
	: Twitter_LCD(),

	phraseToScroll(),
	sizeofPhrase(0),
	scrollPhrase(false),
	beginningOfPhrase(false),
	timeBetweenScrolls(),
	lastScroll(),

	currentLoadSymbol(0),
	loadSymbolTime()

{
}

Twitter_LCD_Hitachi::~Twitter_LCD_Hitachi()
{
}

void Twitter_LCD_Hitachi::step(void)
{
	if (lcdReadyToUse == true) {
		if (newChanges == true) {
			control_NewChanges();
		}
		else {
			control_NoChanges();
		}
	}
}

void Twitter_LCD_Hitachi::control_NewChanges(void)
{
	newChanges = false;
	(*lcd).lcdClear();
	string message;
	switch (status) {
	case statusType::WELCOME:
		(*lcd) << (const unsigned char*)"WELCOME TO TP9   TWITTER HITACHI";
		break;
	case statusType::GOODBYE:
		//El LCD ya esta en blanco
		break;
	case statusType::FINISHED_LOADING:
		message = "FINISHED LOADINGTweets: ";
		message += std::to_string(numberOfTweets);
		(*lcd) << (unsigned const char*)message.c_str();
		break;
	case statusType::STOPPED_LOADING:
		message = "STOPPED LOADING Tweets: ";
		message += std::to_string(numberOfTweets);
		(*lcd) << (unsigned const char*)message.c_str();
		break;
	case statusType::LOADING:
		phraseToScroll = '@';
		phraseToScroll += user;

		set_scrollingPhrase(LOADING_NAME_SPEED, 0);

		cursorPosition secLine;
		secLine.row = 1;
		secLine.column = 0;
		lcd->lcdSetCursorPosition(secLine);

		(*lcd) << (unsigned char*) "LOADING";
		cursorPosition lastChar;
		lastChar.row = 1;
		lastChar.column = 15;
		lcd->lcdSetCursorPosition(lastChar);
		(*lcd) << '|';
		currentLoadSymbol = 0;
		loadSymbolTime = system_clock::now();
		break;

	}
}

void Twitter_LCD_Hitachi::control_NoChanges(void)
{
	switch (status) {
	case statusType::LOADING:
		//actualiza simbolo de carga
		if (system_clock::now() >= (loadSymbolTime + interval(LOADING_SIMBOL_INTERVAL))) {
			loadSymbolTime = system_clock::now();
			currentLoadSymbol++;
			currentLoadSymbol %= sizeof(LoadingArray) - 1;

			cursorPosition lastChar;
			lastChar.row = 1;
			lastChar.column = 15;
			lcd->lcdSetCursorPosition(lastChar);
			(*lcd) << (unsigned char)LoadingArray[currentLoadSymbol];
		}

		manage_scrollingPhrase(0);

		break;

	default:
		//Do nothing; el Display se queda mostrando el mensaje actual
		break;
	}
}

void Twitter_LCD_Hitachi::set_scrollingPhrase(double setspeed, unsigned int line)
{
	if (setspeed <= 0)
		setspeed = 1;

	cursorPosition pos;
	pos.column = 0;
	pos.row = line;
	lcd->lcdSetCursorPosition(pos);

	if ((sizeofPhrase = phraseToScroll.size()) > 16) {
		scrollPhrase = true;
		phraseToScroll += BLANK_LINE;
		beginningOfPhrase = true;
		timeBetweenScrolls = interval((time_interval_type)(1000. / setspeed));
		lastScroll = system_clock::now();
		actualPosition = 0;

		//Imprime por primera vez el nombre
		char c[17];
		phraseToScroll.copy(c, 16);
		c[16] = '\0';
		(*lcd) << (unsigned char*)c;
	}
	else {
		scrollPhrase = false;
		beginningOfPhrase = false;
		timeBetweenScrolls = interval(0);
		lastScroll = system_clock::now();
		actualPosition = 0;

		//Impresion unica del nombre
		(*lcd) << (unsigned char*)phraseToScroll.c_str();
	}
}

void Twitter_LCD_Hitachi::manage_scrollingPhrase(unsigned int line)
{
	if (scrollPhrase == true) {
		interval wait;
		if (beginningOfPhrase == true)
			wait = 5 * timeBetweenScrolls;
		else
			wait = timeBetweenScrolls;

		if (system_clock::now() >= lastScroll + wait) {
			lastScroll = system_clock::now();

			actualPosition++;
			actualPosition %= (sizeofPhrase + 1);
			if (actualPosition == 0)
				beginningOfPhrase = true;
			else
				beginningOfPhrase = false;

			cursorPosition pos;
			pos.column = 0;
			pos.row = line;
			lcd->lcdSetCursorPosition(pos);

			char c[17];
			size_t terminator = phraseToScroll.copy(c, 16,actualPosition);
			c[terminator] = '\0';
			(*lcd) << (unsigned char*)c;


		}//else {DO NOTHING (not ready to scroll yet)}

	} //else (scrollPhrase == false) { DO NOTHING }

	/*
	if (scrollPhase == true && system_clock::now() >= lastScroll + timeBetweenScrolls) {
		lastScroll = system_clock::now();
		actualPosition++;
		if (actualPosition <= sizeofPhrase) {

		}
		else {
			actualPosition = 0;

		}
	}
	*/
}