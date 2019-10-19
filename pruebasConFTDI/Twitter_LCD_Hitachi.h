#pragma once
#include "Twitter_LCD.h"
class Twitter_LCD_Hitachi :
	public Twitter_LCD
{
public:
	Twitter_LCD_Hitachi();
	~Twitter_LCD_Hitachi();

	virtual void step(void);
private:
	std::string formattedTweet;


};

