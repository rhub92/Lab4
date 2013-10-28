/*
* Lab 4: An LCD Driver
*
* Author: Ryan Hub
*
* Date: 27 October 2013
*
* Purpose: The purpose of this lab is to take our assembly code from our previous and convert it into the C programming language. Another task
* for this lab that differs from Lab 3 is that we also have to make the scrolling text wrap itself around instead of having the message start at the
* beginning of the screen.
*
*/


#include "lcd.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char * messageDisplay = "Message?";
    char * buttonPress = "Press123";
    char topScroll[] = "ECE382 is my favorite class! ";
    char bottomScroll[] = "And this is the second line! ";

	initSPI();
	lcdInitialize();
	lcdClear();

	displayScreen(messageDisplay);
	goToBottomLine();
	displayScreen(buttonPress);


    buttonInitialize();
    buttonSelect();
    scrollDisplay(topScroll, bottomScroll);

    while(1){};
}
