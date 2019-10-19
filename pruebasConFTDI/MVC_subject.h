#pragma once

#include "MVC_observer.h"
#include <iostream>
#include <list>

// Clase de la cual deberan heredar todos los metodos

class MVC_subject
{
public:
	MVC_subject(){}
	virtual ~MVC_subject(){}
	void attach(MVC_observer* observerPtr);
	void detach(MVC_observer* observerPtr);

protected:
	void notifyAllObservers(void);

private:
	std::list<MVC_observer*> listOfObservers;

};

