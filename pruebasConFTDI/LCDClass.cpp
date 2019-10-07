#include "LCDClass.h"

using namespace std;

LCD::LCD(int iDevice) 
{
	lcdStatus = !FT_OK;
	BYTE info = 0x00;
	DWORD sizeSent = 0;

	char LCDdescription[ID_SIZE];
	snprintf(LCDdescription, ID_SIZE, "EDA LCD %i B", iDevice);

	std::chrono::seconds MaxTime(CONNECTING_TIME);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	bool exit = false;

	while (lcdStatus != FT_OK && ((current - start) < MaxTime) && exit == false)
	{
		lcdStatus = FT_OpenEx((void*)LCDdescription, FT_OPEN_BY_DESCRIPTION, &lcdHandler);
		if (lcdStatus == FT_OK) {
			BYTE Mask = 0xFF;
			BYTE Mode = 1;
			if (FT_SetBitMode(lcdHandler, Mask, Mode) == FT_OK) 
			{
				//Inicializa como debe ser
				BYTE send;

				send = LCD_FUNCTION_SET | LCD_FUN_DATALENGHT_8 | LCD_RS_IR;
				lcdWriteNibble(send | LCD_E_OFF);
				lcdWriteNibble(send | LCD_E_ON);
				Sleep(1);
				lcdWriteNibble(send | LCD_E_OFF);
				Sleep(5);
				cout << "A" << endl;

				lcdWriteNibble(send | LCD_E_ON);
				Sleep(1);
				lcdWriteNibble(send | LCD_E_OFF);
				Sleep(1);
				cout << "B" << endl;


				lcdWriteNibble(send | LCD_E_ON);
				Sleep(1);
				lcdWriteNibble(send | LCD_E_OFF);
				Sleep(1);
				cout << "C" << endl;

				send = LCD_FUNCTION_SET | LCD_FUN_DATALENGHT_4 | LCD_RS_IR;
				lcdWriteNibble(send | LCD_E_OFF);
				lcdWriteNibble(send | LCD_E_ON);
				Sleep(1);
				lcdWriteNibble(send | LCD_E_OFF);
				Sleep(1);
				cout << "D" << endl;

				lcdWriteIR(LCD_FUNCTION_SET | LCD_FUN_DATALENGHT_4 | LCD_FUN_LINES_2 | LCD_FUN_FONT_5x8);
				Sleep(1);
				cout << "E" << endl;
				lcdWriteIR(LCD_CONTROL | LCD_CTRL_DISPLAY_OFF | LCD_CTRL_CURSOR_OFF | LCD_CTRL_BLINK_OFF);
				Sleep(1);
				cout << "F" << endl;
				lcdWriteIR(LCD_CLEAR);
				Sleep(10);
				cout << "G" << endl;
				lcdWriteIR(LCD_ENTRYSET_RIGHT);
				Sleep(1);
				cout << "H" << endl;

				//
				lcdWriteIR(LCD_CONTROL | LCD_CTRL_DISPLAY_ON | LCD_CTRL_CURSOR_ON | LCD_CTRL_BLINK_ON);
				Sleep(1);
				lcdWriteIR(LCD_CONTROL | LCD_CTRL_DISPLAY_OFF | LCD_CTRL_CURSOR_OFF | LCD_CTRL_BLINK_OFF);
				Sleep(1);
				//

				cout << "SET" << endl;
			}
			else {
				// No se pudo configurar :(
				FT_Close(lcdHandler);
				cout << "Couldn't configure" << endl;
				lcdHandler = NULL;
			}
			exit = true;
		}
		current = std::chrono::system_clock::now();
	}
	//controlar si se logro conectar O se acabo el tiempo
	if (lcdStatus != FT_OK) {
		cout << "Couldn't open" << endl;
		//No se pudo abrir el LCD
		lcdHandler = NULL;
	}
}

void LCD::lcdWriteNibble(BYTE valor)
{
	DWORD size_sent = 0;
	FT_Write(lcdHandler, &valor, 1, &size_sent);

	//Debug:
	printf("0x%02X\n", valor);
}

void LCD::lcdWriteByte(BYTE valor, BYTE rs)
{
	BYTE send = 0;

	send = (valor & 0xF0) | rs;
	lcdWriteNibble(send | LCD_E_OFF);
	lcdWriteNibble(send | LCD_E_ON);
	Sleep(1);
	lcdWriteNibble(send | LCD_E_OFF);

	send = ((valor & 0x0F) << 4) | rs;
	lcdWriteNibble(send | LCD_E_OFF);
	lcdWriteNibble(send | LCD_E_ON);
	Sleep(1);
	lcdWriteNibble(send | LCD_E_OFF);
}


void LCD::lcdWriteIR(BYTE valor)
{
	lcdWriteByte(valor, LCD_RS_IR);
}
void LCD::lcdWriteDR(BYTE valor)
{
	lcdWriteByte(valor, LCD_RS_DR);
}

FT_HANDLE LCD::getHandler(void)
{
	return lcdHandler;
}

FT_STATUS LCD::getStatus(void) {
	return lcdStatus;
}