#include <Windows.h>
#define FTD2XX_EXPORTS
#include "ftd2xx.h"

struct cursorPosition { 
	int row; int column; 
};
class basicLCD
{
public:

	/*=====================================================
	* Name: basicLCD
	* Entra: -
	* Resulta: Constructor de la clase. Inicializa el LCD y deja
	*          todo listo comenzar a utilizarlo.
	*
	* cadd =1 (cursor address) (ver NOTA 1)
	*=====================================================*/

	/*=====================================================
	* Name: ~basicLCD
	* Entra: -
	* Resulta: Destructor de la clase. Libera cualquier recurso
	*          que se hubiera tomado de forma de evitar
	*          "resources leak".
	*=====================================================*/

	/*=====================================================
	* Name: lcdInitOk * Entra: -
	* Resulta: No genera ningún cambio en el display.
	* Devuelve en su nombre “true” si el display se inicializó
	* correctamente (el constructor no tuvo errores) o “false
	* en caso contrario.
	*=====================================================*/

	//miren el documento en campus, re pesado copiar todo del PDF:D

	virtual bool lcdInitOk() = 0;

	virtual FT_STATUS lcdGetError() = 0;

	virtual bool lcdClear() = 0;

	virtual bool lcdClearToEOL() = 0;

	virtual basicLCD& operator<<(const unsigned char c) = 0;

	virtual basicLCD& operator<<(const unsigned char* c) = 0;

	virtual bool lcdMoveCursorUp() = 0;

	virtual bool lcdMoveCursorDown() = 0;

	virtual bool lcdMoveCursorRight() = 0;

	virtual bool lcdMoveCursorLeft() = 0;

	virtual bool lcdSetCursorPosition(const cursorPosition pos) = 0;

	virtual cursorPosition lcdGetCursorPosition() = 0;

protected:

	int cadd;

//	void lcdUpdateCursor();

};