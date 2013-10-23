#include "lcd.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char * message = "Message?                        ";
    char * press = "Press123                    ";

    initSPI();
    lcdInitialize();
    lcdClear();

    displayScreen(message);
    displayScreen(press);
    while(1){};
}
