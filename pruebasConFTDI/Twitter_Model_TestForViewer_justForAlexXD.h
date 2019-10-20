#pragma once
//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
//
// TODO ESTE PROGRAMA ES UNA BASOFIA bajo los terminos de EDA, claro esta
// es simplemente una clase de debug
// Agustin, si lees esto, no me mates, solo soy un simple electronico, con suenos y esperanzas (aun)
#include "Twitter_Model.h"

class testingViewerThroughModel {
public:
	testingViewerThroughModel() :buddy(nullptr){}
	~testingViewerThroughModel(){}
	void setFriend(Twitter_Model* b) { buddy = b; }
	void notify(void) { buddy->notifyAllObservers(); }
	void user(char* u) { buddy->user = u; }
	void tuit(char* t) { buddy->tuit = t; }
	void date(char* d) { buddy->date = d; }
	void speed(double s) { buddy->speed = s; }
	void error(errorType::errorVar e) { buddy->error = e; }
	void status(statusType::statusVar s) { buddy->status = s; }
	void number(unsigned int n) { buddy->numberOfTweets = n; }
	void current(unsigned int c) { buddy->currentTweetNumber = c; }


private:
	Twitter_Model* buddy;
};