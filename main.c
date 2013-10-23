#include "lcd.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char * message = "Message?                    ";
    char * press = "Press123                    ";
    char * topScroll = "ECE382 is my favorite class!";

    initSPI();
    lcdInitialize();
    lcdClear();

    displayScreen(press);
    buttonInitialize();
    buttonSelect();
    scrollDisplay(topScroll);

    //scrollDisplay(topScroll);

    //displayScreen(message);
    //displayScreen(press);
    while(1){};
}
