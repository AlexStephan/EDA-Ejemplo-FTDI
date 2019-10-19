#include "Twitter_LCD_Hitachi.h"

Twitter_LCD_Hitachi::Twitter_LCD_Hitachi()
	: Twitter_LCD(),
	formattedTweet()
{
}

Twitter_LCD_Hitachi::~Twitter_LCD_Hitachi()
{
}

void Twitter_LCD_Hitachi::step(void)
{
	if (newChanges == true) {
		newChanges = false;
		switch (status) {
		case statusType::WELCOME:
			cursorPosition start;
			start.row = 0;
			start.column = 0;
			(*lcd).lcdSetCursorPosition(start);
			(*lcd) << (const unsigned char*)"WELCOME TO TP9   TWITTER HITACHI";
			break;
		case statusType::GOODBYE:
			(*lcd).lcdClear();
			break;
		case statusType::FINISHED_LOADING:
			std::string message = "FINISHED LOADINGTweets: ";
			message += std::to_string(numberOfTweets);
			(*lcd) << (unsigned const char*)message.c_str();
			break;
		case statusType::STOPPED_LOADING:
			std::string message = "STOPPED LOADING Tweets: ";
			message += std::to_string(numberOfTweets);
			(*lcd) << (unsigned const char*)message.c_str();
			break;
		}
	}
	else {

	}
}