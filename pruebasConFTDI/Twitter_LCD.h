#pragma once
#include "MVC_observer.h"
#include "basicLCD.h"

/*
NOTA: dado que el manejo del Display depende del tipo de LCD utilizado (por ejemplo, cantidad de caracteres que pueden mostrarse por vez)
es necesario hacer una clase especifica para el manejo de cada LCD.
	La consigna sugiere emplear un BasicLCD para mayor escalabilidad. De acuerdo con esta logica, existira una funcion---

*/

class Twitter_LCD : 
	public MVC_observer
{
	Twitter_LCD();

	//Setters y Getters del basicLCD contenidos en la clase
	void attachLCD(basicLCD* lcd); //Nota: le tienen q pasar el LCD ya inicializado
	void detachLCD(void);
	basicLCD* getLCD(void);


	virtual void update(void*); //Metodo llamado por el Modelo ante cualquier modificacion del mismo
	// Organiza la informacion para poder mostrarla por el display en STEP

	virtual void step(void); //Metodo llamado desde el Main, para actualizar el display, aun mientras el Modelo no haya sido modificado (colocar junto al cycle del controller, en el loop)
	// Actualiza el display

private:
	basicLCD *lcd;
	bool lcdReadyToUse;
};

