/*
 * lcd.h
 * Author: Ryan Hub
 * Date: 27 October 2013
 * Description: Library to interact with the Geek Box LCD
 */


#include <msp430.h>

#ifndef LCD_H_
#define LCD_H_

void initSPI();
void lcdClear();
void lcdInitialize();
void displayScreen(char * Message);
void scrollDisplay(char Message[], char Message1[]);
void buttonInitialize();
void buttonSelect();
void writeCommandByte(char commandByte);
void goToBottomLine();

#endif
