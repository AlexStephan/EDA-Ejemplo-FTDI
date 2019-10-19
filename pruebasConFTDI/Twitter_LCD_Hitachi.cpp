#include "Twitter_LCD_Hitachi.h"

#define BLANK_LINE "                " //Es mas rapido para el programa escribir espacios al final del mensaje, en vez de tener que limpiar por completo la linea y escribir lo correspondiente
										//Notese q lo q hace el programa para borrar una sola linea es, de hecho, escribir espacios

static const char LoadingArray[] = "|{(<({|})>)}";
#define LOADING_INTERVAL 250 //mseg

using namespace std;
using namespace std::chrono;

Twitter_LCD_Hitachi::Twitter_LCD_Hitachi()
	: Twitter_LCD(),

	phraseToScroll(),
	sizeofPhrase(0),
	scrollPhase(false),
	beginningOfPhrase(false),
	timeBetweenScrolls(),
	lastScroll(),

	currentLoadSymbol(0),
	loadSymbolTime(),

{
}

Twitter_LCD_Hitachi::~Twitter_LCD_Hitachi()
{
}

void Twitter_LCD_Hitachi::step(void)
{
	if (lcdReadyToUse) {
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
		if ((sizeofPhrase = phraseToScroll.size()) > 16) {
			scrollPhase = true;
			phraseToScroll += BLANK_LINE;
			beginningOfPhrase = true;
			timeBetweenScrolls = interval((time_interval_type)(1000. / speed));
			lastScroll = system_clock::now();
			actualPosition = 0;
			//Imprime por primera vez el nombre
			char c[17];
			phraseToScroll.copy(c, 16);
			c[16] = '\0';
			(*lcd) << (unsigned char*)c;
		}
		else {
			scrollPhase = false;
			beginningOfPhrase = false;
			timeBetweenScrolls = interval(0);
			lastScroll = system_clock::now();
			actualPosition = 0;

			//Impresion unica del nombre
			(*lcd) << (unsigned char*)phraseToScroll.c_str();
			cursorPosition secLine;
			secLine.row = 1;
			secLine.column = 0;
			lcd->lcdSetCursorPosition(secLine);

		}
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
		if (system_clock::now() >= (loadSymbolTime + interval(LOADING_INTERVAL))) {
			loadSymbolTime = system_clock::now();
			currentLoadSymbol++;
			currentLoadSymbol %= sizeof(LoadingArray) - 1;

			cursorPosition lastChar;
			lastChar.row = 1;
			lastChar.column = 15;
			lcd->lcdSetCursorPosition(lastChar);
			(*lcd) << (unsigned char)LoadingArray[currentLoadSymbol];
		}

		if (scrollPhase == true && system_clock::now() >= lastScroll + timeBetweenScrolls) {
			lastScroll = system_clock::now();
			actualPosition++;
			if (actualPosition <= sizeofPhrase) {

			}
			else {
				actualPosition = 0;

			}
		}



		break;
	default:
		//Do nothing; el Display se queda mostrando el mensaje actual
		break;
	}
}