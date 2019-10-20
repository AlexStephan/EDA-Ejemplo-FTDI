#pragma once
#include "MVC_observer.h"
#include "Twitter_Model.h"

class Twitter_Controller :
	public MVC_observer
{
public:
	Twitter_Controller(Twitter_Model* m) : model(m){};
	virtual void update(void*) {};
	bool isFinished(void) {};
	void cycle(void) {};
private:
	Twitter_Model* model;
};

