#include "lcd.h"

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer



    initSPI();
    lcdInitialize();
    lcdClear();

}
