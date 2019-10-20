#include "Twitter_Model.h"
#include "Twitter_Controller.h"
#include "Twitter_LCD_Hitachi.h"
#include "HitachiLCD.h"

//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
// Todo lo q se encuentre debajo de un conejo es temporal
#include "Twitter_Model_TestForViewer_justForAlexXD.h"
void alex_esta_loquito(void);
//


int main(void) {

//	(\ /)		(\ /)		(\ /)		(\ /)
//	( ..)		(.. )		( ..)		(.. )
//	o(")(")	  (")(")o		o(")(")	  (")(")o
// Katri y Tobi: concentrense en el "verdadero main" para organizar sus clases

	// Este es el verdadero main:
	/*
	Twitter_Model model;

	Twitter_Controller controller(&model);

	HitachiLCD lcd(5);
	Twitter_LCD_Hitachi viewer;
	viewer.attachLCD(&lcd);

	model.attach(&controller);
	model.attach(&viewer);


	while (controller.isFinished() == false) {
		controller.cycle(); //getEvent, dispach, llama a metodos del model
		viewer.step();
	}
	*/

	//Este de aqui es mi prueba del LCD, ignoren todo lo q continua a partir de aqui

	alex_esta_loquito();

	return 0;
}

void alex_esta_loquito() {
	Twitter_Model m;
	HitachiLCD lcd(5);
	Twitter_LCD_Hitachi v;
	v.attachLCD(&lcd);
	m.attach(&v);

	testingViewerThroughModel t;
	t.setFriend(&m);



	t.error(errorType::NONE);
	t.status(statusType::WELCOME);
	t.notify();

	for (unsigned long long int i = 0; i < 20000000; i++) {
		v.step();
	}

	t.status(statusType::LOADING);
	t.user("Don Pedro Pedrito");
	t.notify();

	for (unsigned long long int i = 0; i < 3500000; i++) {
		v.step();
	}

	t.status(statusType::FINISHED_LOADING);
	t.number(10);
	t.notify();

	for (unsigned long long int i = 0; i < 20000000; i++) {
		v.step();
	}

	t.tuit("La panaderia del doctor Tito es la mejor del universo");
	t.date("Fri Feb 21 19:24:32 +0000 2012");
	t.speed(5);
	t.current(12);
	t.status(statusType::SHOW_TWEET);
	t.notify();

	for (unsigned long long int i = 0; i < 6000000; i++) {
		v.step();
	}
	
	t.status(statusType::LOADING);
	t.user("El Bromas");
	t.notify();

	for (unsigned long long int i = 0; i < 3000000; i++) {
		v.step();
	}

	t.status(statusType::STOPPED_LOADING);
	t.number(7);
	t.notify();

	for (unsigned long long int i = 0; i < 20000000; i++) {
		v.step();
	}

	t.tuit("Vivir significa que aun no has muerto jajas xD");
	t.date("Mon Jun 15 02:11:19 +0000 2019");
	t.speed(3);
	t.current(3);
	t.status(statusType::SHOW_TWEET);
	t.notify();

	for (unsigned long long int i = 0; i < 12000000; i++) {
		v.step();
	}

	t.status(statusType::GOODBYE);
	t.notify();
	v.step();
}