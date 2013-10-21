/*
 * lcd.h
 *
 *  Created on: Oct 20, 2013
 *      Author: c15ryan.hub
 */

#ifndef LCD_H_
#define LCD_H_

void initSPI();
void lcdClear();
void lcdInitialize();
void displayScreen(char * Message);
void scrollDisplay(char * Message);
void scrollMessage();
void buttonInitialize();

#endif /* LCD_H_ */
