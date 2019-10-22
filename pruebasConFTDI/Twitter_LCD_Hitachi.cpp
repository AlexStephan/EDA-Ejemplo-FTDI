#include "Twitter_LCD_Hitachi.h"

#define BLANK_LINE "                " //Es mas rapido para el programa escribir espacios al final del mensaje, en vez de tener que limpiar por completo la linea y escribir lo correspondiente
										//Notese q lo q hace el programa para borrar una sola linea es, de hecho, escribir espacios

#define LOADING_SIMBOL_INTERVAL 200 //mseg
#define LOADING_NAME_SPEED 3
#define TIME_BEFORE_DATE 2000 //mseg

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
	actualPosition(0),

	currentLoadSymbol(0),
	loadSymbolTime(),

	formattedCurrent(),
	formattedDate(),
	tweetStartTime(),
	alreadySeeingDate(false)


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
	if (error == errorType::NONE) {
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
			phraseToScroll += AtoAscii(user);

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
		case statusType::SHOW_TWEET:
			formattedCurrent = "Tweet ";
			formattedCurrent += to_string(currentTweetNumber);
			formattedCurrent += '/';
			formattedCurrent += to_string(numberOfTweets);

			phraseToScroll = AtoAscii(user);
			phraseToScroll += ": \"";
			phraseToScroll += AtoAscii(tweet);
			phraseToScroll += "\"";

			create_formattedDate();

			alreadySeeingDate = false;
			tweetStartTime = system_clock::now();

			(*lcd) << (unsigned char*)formattedCurrent.c_str();
			set_scrollingPhrase(speed, 1);

			break;

		}
	}
	else if(error == errorType::CANT_CONNECT ||
		error == errorType::NON_EXISTENT_USER){
		(*lcd) << (unsigned char*)"ERROR: CANNOT   CONNECT TO USER";

	}
	else if (error == errorType::NO_TWEETS_AVAILABLE) {
		(*lcd) << (unsigned char*)"ERROR: NO TWEETSAVAILABLE";
	}
}

void Twitter_LCD_Hitachi::control_NoChanges(void)
{
	static const char LOADING_ARRAY[] = "|{(<({|})>)}";
	if (error == errorType::NONE) {
		switch (status) {
		case statusType::LOADING:

			//actualiza simbolo de carga
			if (system_clock::now() >= (loadSymbolTime + interval(LOADING_SIMBOL_INTERVAL))) {
				loadSymbolTime = system_clock::now();
				currentLoadSymbol++;
				currentLoadSymbol %= sizeof(LOADING_ARRAY) - 1;

				cursorPosition lastChar;
				lastChar.row = 1;
				lastChar.column = 15;
				lcd->lcdSetCursorPosition(lastChar);
				(*lcd) << (unsigned char)LOADING_ARRAY[currentLoadSymbol];
			}

			manage_scrollingPhrase(0);

			break;

		case statusType::SHOW_TWEET:
			if ((alreadySeeingDate == false) && (system_clock::now() >= tweetStartTime + interval(TIME_BEFORE_DATE))) {
				alreadySeeingDate = true;

				cursorPosition start;
				start.column = 0;
				start.row = 0;
				lcd->lcdSetCursorPosition(start);

				(*lcd) << (unsigned char*)formattedDate.c_str();
			}

			manage_scrollingPhrase(1);

			break;

		default:
			//Do nothing; el Display se queda mostrando el mensaje actual
			break;
		}
	}// else if(error != NONE) {DO NOTHING}
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

void Twitter_LCD_Hitachi::create_formattedDate(void)
{
	const char MONTH_ABR[12][4]{
		"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
	};

	string day = "01";
	string month = "01";
	string year = "00";

	string hour = "00";
	string minute = "00";

	if (date.size() == 30) {
		day = date.substr(8, 2);
		year = date.substr(28, 2);
		hour = date.substr(11, 2);
		minute = date.substr(14, 2);

		string aux = date.substr(4, 3);
		bool found = false;
		int i;
		for (i = 0; i < 12; i++) {
			if (aux.compare(MONTH_ABR[i]) == 0) {
				found = true;
				break;
			}
		}
		if (found == true) {
			month.clear();
			if (i < 10)
				month += '0';
			month += to_string(i);
		}

	}

	formattedDate = day + '/' + month + '/' + year + " - "
		+ hour + ':' + minute;
}

string Twitter_LCD_Hitachi::AtoAscii(const string& s)
{
	string rta;
	size_t size = s.size();
	char c;
	for (size_t i = 0; i < size; i++) {
		c = s[i];
		switch (c) {
		case 'á':
			c = 'a';
			break;
		case 'é':
			c = 'e';
			break;
		case 'í':
			c = 'i';
			break;
		case 'ó':
			c = 'o';
			break;
		case 'ú':
			c = 'u';
			break;
		case 'ñ':
			c = 'n';
			break;
		default:
			//Do nothing
			break;
		}
		rta += c;
	}

	return rta;
}