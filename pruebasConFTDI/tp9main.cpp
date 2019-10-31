#include "Twitter_Model.h"
#include "Twitter_Controller.h"
#include "Twitter_LCD_Hitachi.h"
#include "HitachiLCD.h"



int main(void) {


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


	return 0;
}
