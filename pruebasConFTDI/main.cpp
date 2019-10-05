#include<cstdio>
#include <iostream>
#include <Windows.h>
#include <chrono>
#define FTD2XX_EXPORTS
#include "ftd2xx.h"

#define MY_LCD_DESCRIPTION "EDA LCD 5 B" // CAMBIAR LA DESCRIPCION SEGUN EL GRUPO

#define CONNECTING_TIME 5 //in seconds

int main()
{
	FT_STATUS status = ! FT_OK;
	FT_HANDLE lcdHandle;
	unsigned char info=0x00;
	DWORD sizeSent=0;

	
	std::chrono::seconds MaxTime( CONNECTING_TIME);/*The display has a settling time after the physical connection so the attempt to connect
	will be done for a few seconds*/
	
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;
	
	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, &lcdHandle);

		if (status == FT_OK)
		{
			UCHAR Mask = 0xFF;	//Selects all FTDI pins.
			UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(lcdHandle, Mask, Mode) == FT_OK)	// Sets LCD as asynch bit mode. Otherwise it doesn't work.
			{

				//Example to write 0xf0 to the display 

				//(E=0, RS=0, D4-D7=f)...
				info = 0xf0;

				//Finally executes the action "write to LCD"...
				if (FT_Write(lcdHandle, &info, 1, &sizeSent) == FT_OK)
				{
					////
					std::cout << "aca hace lo q tiene q hacer..." << std::endl;
					Sleep(1000);
					info = 0x30;
					FT_Write(lcdHandle, &info, 1,&sizeSent);
					info = 0x31;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x30;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(5);

					info = 0x31;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x30;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);

					info = 0x31;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x30;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);

					info = 0x20;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x21;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x20;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);



					info = 0x20;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x21;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x20;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0xC0; //0x80
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0xC1;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0xC0;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);



					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x01;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0x80;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x81;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x80;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);



					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x01;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0x10;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x11;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x10;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(10);



					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x01;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0x60;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x61;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x60;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);


					////
#define MSB(x)	((x)&0xF0)
#define LSB(x)	(((x)&0x0F)<<4)

					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0x01;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0x00;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0xE0;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0xE1;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0xE0;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);


					int it = 0;
					while (1) {

						it++;
						it = it % 8;
						{
							int i, c;

							info = 0x80;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							info = 0x81;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);
							info = 0x80;
							FT_Write(lcdHandle, &info, 1, &sizeSent);

							info = 0x00;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							info = 0x01;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);
							info = 0x00;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);


							for (i = it*0x20, c = 0; c < 16; i++, c++) {
								info = MSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								info = MSB(i) | 0x03;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
								info = MSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);

								info = LSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								info = LSB(i) | 0x03;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
								info = LSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
							}
							info = 0xC0;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							info = 0xC1;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);
							info = 0xC0;
							FT_Write(lcdHandle, &info, 1, &sizeSent);

							info = 0x00;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							info = 0x01;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);
							info = 0x00;
							FT_Write(lcdHandle, &info, 1, &sizeSent);
							Sleep(1);
							for (c = 0; c < 16; i++, c++) {
								info = MSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								info = MSB(i) | 0x03;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
								info = MSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);

								info = LSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								info = LSB(i) | 0x03;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
								info = LSB(i) | 0x02;
								FT_Write(lcdHandle, &info, 1, &sizeSent);
								Sleep(1);
							}
						}
						//Sleep(1000);
					}
					/*
					info = 0xB2;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0xB3;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0xB2;
					FT_Write(lcdHandle, &info, 1, &sizeSent);

					info = 0xC2;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					info = 0xC3;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);
					info = 0xC2;
					FT_Write(lcdHandle, &info, 1, &sizeSent);
					Sleep(1);

					*/



					////
					//If success continue with the program (...)
					std::cout << "done" << std::endl;
				}
				else
					printf("Error writing to the LCD\n");
			}
			else
				printf("Couldn't configure LCD\n");

			FT_Close(lcdHandle);
		}
		current = std::chrono::system_clock::now();
	}

	if(status!=FT_OK)
		printf("Couldn't open LCD\n");
	
	return 0;
}
