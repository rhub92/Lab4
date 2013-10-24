#include "lcd.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char * message = "Message?";
    char * press = "Press123";
    char topScroll[] = "ECE382 is my favorite class!";
    char bottomScroll[] = "And this is the second line!";

    initSPI();
    lcdInitialize();
    lcdClear();

    displayScreen(message);
    writeCommandByte(0xc0);
    displayScreen(press);


    buttonInitialize();
    buttonSelect();
    scrollDisplay(topScroll, bottomScroll);


    //scrollDisplay(topScroll);

    //displayScreen(message);
    //displayScreen(press);
    while(1){};
}
