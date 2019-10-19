#pragma once

// Clase de la que deberan heredar todos los viewers y controllers

class MVC_observer {
public:
	MVC_observer() {};
	virtual ~MVC_observer() {};
	virtual void update(void*) = 0; //recibe 'this'
};