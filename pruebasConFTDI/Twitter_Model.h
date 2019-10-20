#pragma once
#include "MVC_subject.h"

//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
//
//NOTA: ELIMINAR EN EL ARCHIVO FINAL, SI ALEX AUN NO SE HIZO CARGO
class testingViewerThroughModel;
//



namespace errorType { //Ante un error, se ignora el contenido de Status
	enum errorVar{NONE,CANT_CONNECT,NO_TWEETS_AVAILABLE,NON_EXISTENT_USER};
}
namespace statusType {
	enum statusVar{
		WELCOME,	//Al iniciar el modelo
		LOADING,	//Cargando twits de un usuario (getUser DEBE SER FUNCIONAL)
		FINISHED_LOADING,	//Terminaron de cargarse los Twits. Aun no se selecciono ninguno. (getNumberOfTweets DEBE SER FUNCIONAL)
		STOPPED_LOADING,	//El usuario cancelo la carga de Tweets (getNumberOfTweets DEBE SER FUNCIONAL)
		SHOW_TWEET,	//Mostrar el Tweet en el display (getUser,getTuit, getDate, getSpeed, getNumberOfTweets y getCurrentTweetNumber deben ser funcionales)
		GOODBYE	//Ultimo mensaje antes de apagar el LCD. IDEA: una vez q el ciclo principal del main (controller y viewer.step()) haya acabado, mantener en loop al LCD hasta q el mismo haya finalizado)
	};
}

class Twitter_Model :
	public MVC_subject
{

public:

	//NOTA: pasar las funciones al .cpp, no dejarlas en el .h

	//Getters: necesarios para el viewer que maneja el Display
	const char* getUser() { return user; }; //Cuando no corresponda, puede devolver NULL
	const char* getTuit() { return tuit; }; //Si es mas facil q sea un string, avisar a Alex
	const char* getDate() { return date; }; //lo mismo. No se en q formato lo vas a leer, pero seguro tiene forma "Thu Dec 04 18:51:57 +0000 2008"
	double getSpeed() { return speed; };
	errorType::errorVar getError() { return error; };
	statusType::statusVar getStatus() { return status; };
	unsigned int getNumberOfTweets() { return numberOfTweets; };
	unsigned int getCurrentTweetNumber() { return currentTweetNumber; };

private:
	//NOTA: puede ser mejor utilizar strings. Eso es decision de Tobi, pero en caso de q afecte a los getters, avisar a Alex
	char* user;
	char* tuit;
	char* date;
	double speed;
	errorType::errorVar error;
	statusType::statusVar status;
	unsigned int numberOfTweets;
	unsigned int currentTweetNumber;



//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
//
//NOTA: ELIMINAR EN EL ARCHIVO FINAL, SI ALEX AUN NO SE HIZO CARGO
	friend testingViewerThroughModel;
//





};

