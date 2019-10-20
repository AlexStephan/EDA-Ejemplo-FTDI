#pragma once
#include "MVC_subject.h"
#include "curl/curl.h"
#include "json.hpp"

//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
//
//NOTA: ELIMINAR EN EL ARCHIVO FINAL, SI ALEX AUN NO SE HIZO CARGO
class testingViewerThroughModel;
//



typedef enum errorType {NONE,CANT_CONNECT,NO_TWEETS_AVAILABLE,NON_EXISTENT_USER};
typedef enum statusType{
		WELCOME,	//Al iniciar el modelo
		LOADING,	//Cargando twits de un usuario (getUser DEBE SER FUNCIONAL)
		FINISHED_LOADING,	//Terminaron de cargarse los Twits. Aun no se selecciono ninguno. (getNumberOfTweets DEBE SER FUNCIONAL)
		STOPPED_LOADING,	//El usuario cancelo la carga de Tweets (getNumberOfTweets DEBE SER FUNCIONAL)
		SHOW_TWEET,	//Mostrar el Tweet en el display (getUser,getTuit, getDate, getSpeed, getNumberOfTweets y getCurrentTweetNumber deben ser funcionales)
		GOODBYE	//Ultimo mensaje antes de apagar el LCD. IDEA: una vez q el ciclo principal del main (controller y viewer.step()) haya acabado, mantener en loop al LCD hasta q el mismo haya finalizado)
};

class Twitter_Model :
	public MVC_subject
{

public:

	Twitter_Model();
	void downloadTweets();
	//Getters: necesarios para el viewer que maneja el Display
	const char* getUser(); 
	const char* getTuit();
	const char* getDate(); 
	double getSpeed();
	errorType getError();
	statusType getStatus();
	unsigned int getNumberOfTweets();
	unsigned int getCurrentTweetNumber();

	//Setters: necesarios para que el controlador modifique el modelo segun el input del usuario
	void setUser(const char*);
	void setSpeed(double);
	void setCurrentTweetNumber(unsigned int);
	void setNumberOfTweets(unsigned int);

private:
	std::string user;
	std::string tuit;
	std::string date;
	std::string token;
	double speed;
	errorType error;
	statusType status;
	unsigned int numberOfTweets;
	unsigned int currentTweetNumber;

	//Tweet Downloading
	json tweets;
	std::string tweetsString;
	CURL* curl;

	//Token generation
	void getBearerToken(void);



//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
//
//NOTA: ELIMINAR EN EL ARCHIVO FINAL, SI ALEX AUN NO SE HIZO CARGO
	friend testingViewerThroughModel;
//





};

