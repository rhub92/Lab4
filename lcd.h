#include <msp430.h>

#ifndef LCD_H_
#define LCD_H_

void initSPI();
void lcdClear();
void lcdInitialize();
void displayScreen(char * Message);
void scrollDisplay(char Message[], char Message1[]);
void scrollMessage();
void buttonInitialize();
void buttonSelect();
void writeDataByte(char dataByte);
void writeCommandByte(char commandByte);
//void 1MHZCLOCK();


#endif /* LCD_H_ */
