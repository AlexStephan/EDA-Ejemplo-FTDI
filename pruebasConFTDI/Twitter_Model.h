#pragma once
#include "MVC_subject.h"

namespace errorType {
	enum errorVar{NO_ERROR,CANT_CONNECT,NO_TWEETS_AVAILABLE,NON_EXISTENT_USER};
}
namespace statusType {
	enum statusVar{LOADING,READY,SHUT_DOWN};
}

class Twitter_Model :
	public MVC_subject
{

public:


	//Setters: necesarios para el viewer que maneja el Display
	const char* getUser(); //Cuando no corresponda, puede devolver NULL
	const char* getTuit(); //Si es mas facil q sea un string, avisar a Alex
	const char* getDate(); //lo mismo. No se en q formato lo vas a leer, pero seguro tiene forma "Thu Dec 04 18:51:57 +0000 2008"
	double getSpeed();
	errorType::errorVar getError();
	statusType::statusVar getStatus();
	unsigned int getNumberOfTweets();
	unsigned int getCurrentTweetNumber();
};

