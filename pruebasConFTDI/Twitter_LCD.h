#pragma once

#include "MVC_observer.h"
#include "basicLCD.h"
#include "Twitter_Model.h"
#include <string>

//#define MAX_USER_LENGHT	50
//#define MAX_TWEET_LENGH	300
//#define MAX_DATE_LENGHT	50


/*
NOTA: dado que el manejo del Display depende del tipo de LCD utilizado (por ejemplo, cantidad de caracteres que pueden mostrarse por vez)
es necesario hacer una clase especifica para el manejo de cada LCD.
	La consigna sugiere emplear un BasicLCD para mayor escalabilidad. De acuerdo con esta logica, Twitter_LCD contiene todos los metodos
aplicables a cualquier BasicLCD, mientras que clases hijas de esta (por ejemplo, Twitter_LCD_Hitachi) contiene los metodos especificos
para el manejo de cada LCD (en particular, STEP)
	A la hora de implementar un nuevo LCD, solo sera necesario crear una nueva clase hija de BasicLCD, y una clase hija de Twitter_LCD

	El modelo attachea un Twitter_LCD, sin importar si es una clase heredada o no
*/

class Twitter_LCD : 
	public MVC_observer
{
	Twitter_LCD();
	~Twitter_LCD();

	//Setters y Getters del basicLCD contenidos en la clase
	void attachLCD(basicLCD* lcd); //Nota: le tienen q pasar el LCD ya inicializado
	void detachLCD(void);
	basicLCD* getLCD(void);


	virtual void update(void*); //Metodo llamado por el Modelo ante cualquier modificacion del mismo
	// Organiza la informacion para poder mostrarla por el display en STEP

	virtual void step(void) = 0; //Metodo llamado desde el Main, para actualizar el display, aun mientras el Modelo no haya sido modificado (colocar junto al cycle del controller, en el loop)
	// Actualiza el display

private:
	basicLCD *lcd;
	bool lcdReadyToUse;

	bool newChanges;

	std::string user;//[MAX_USER_LENGHT + 1];
	std::string tweet;//[MAX_TWEET_LENGH + 1];
	std::string date;//[MAX_DATE_LENGHT + 1];
	double speed;
	errorType::errorVar error;			//
	statusType::statusVar status;		//
	unsigned int numberOfTweets;
	unsigned int currentTweetNumber;
};

