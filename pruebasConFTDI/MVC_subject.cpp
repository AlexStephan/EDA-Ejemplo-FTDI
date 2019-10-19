#include "MVC_subject.h"

void MVC_subject::attach(MVC_observer* observerPtr)
{
	listOfObservers.push_back(observerPtr);
}

void MVC_subject::detach(MVC_observer* observerPtr)
{
	listOfObservers.remove(observerPtr);
}

void MVC_subject::notifyAllObservers(void)
{
	std::list<MVC_observer*>::iterator it;
	for (it = listOfObservers.begin(); it != listOfObservers.end(); it++) {
		(*it)->update(this);
	}
}
