#include "lcd.h"

char LCDCON = 0;

#define RS_MASK 0x40

/*
 * Subroutine Name: goToTopLine
 * Author: Ryan Hub
 * Function: Sets the cursor of the LCD screen at the beginning on the top line
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void goToTopLine() {
	writeCommandByte(0x80);
}
/*
 * Subroutine Name: goToBottomLine
 * Author: Ryan Hub
 * Function: Sets the cursor of the LCD screen at the beginning on the bottom line
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void goToBottomLine() {
	writeCommandByte(0xc0);
}
/*
 * Subroutine Name: milliDelay
 * Author: Ryan Hub
 * Function: Executes a delay cycle of 1.65 milliseconds
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void milliDelay() {
	_delay_cycles(0x0238);
}
/*
 * Subroutine Name: milliDelay
 * Author: Ryan Hub
 * Function: Executes a delay cycle of 40.5 microseconds
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void microDelay() {
	_delay_cycles(0x000a);
}
/*
 * Subroutine Name: setSS_HI
 * Author: Ryan Hub
 * Function: Sets the slave select to high
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void setSS_HI() {
	P1OUT |= BIT0;
}
/*
 * Subroutine Name: setSS_HI
 * Author: Ryan Hub
 * Function: Sets the slave select to low
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void setSS_LO() {
	P1OUT &= ~BIT0;
}
/*
 * Subroutine Name: spiSEND
 * Author: Ryan Hub
 * Function: sends the value of inputByte to SPI
 * Inputs: inputByte- The byte being sent to the LCD
 * Outputs: none
 * Subroutines used: setSS_HI, setSS_LO
 */
void spiSEND(char inputByte) {
	char readByte;
	setSS_LO();
	UCB0TXBUF = inputByte;

	while (!(UCB0RXIFG & IFG2)) {
		// wait until you've received a byte
	}

	readByte = UCB0RXBUF;

	setSS_HI();
}
/*
 * Subroutine Name: LCDWRT4
 * Author: Ryan Hub
 * Function: Send 4 bits of data to LCD via SPI
 * Inputs: sendByte- The byte being sent to the LCD
 * Outputs: none
 * Subroutines used: spiSEND, milliDelay
 */
void LCDWRT4(char sendByte) {
	sendByte &= 0x0f;
	sendByte |= LCDCON;
	sendByte &= 0x7f;
	spiSEND(sendByte);
	milliDelay();
	sendByte |= 0x80;
	spiSEND(sendByte);
	milliDelay();
	sendByte &= 0x7f;
	spiSEND(sendByte);
	milliDelay();
}
/*
 * Subroutine Name: LCDWRT8
 * Author: Ryan Hub
 * Function: Send full byte to the LCD
 * Inputs: byteToSend- The byte being sent to the LCD
 * Outputs: none
 * Subroutines used: LCDWRT4
 */
void LCDWRT8(char byteToSend) {
	unsigned char sendByte = byteToSend;
	sendByte &= 0xF0;
	sendByte = sendByte >> 4;
	LCDWRT4(sendByte);
	sendByte = byteToSend;
	sendByte &= 0x0f;
	LCDWRT4(sendByte);
}
/*
 * Subroutine Name: initSPI
 * Author: Ryan Hub
 * Function: Initializes the subsystem
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void initSPI() {

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 |= UCCKPL | UCMSB | UCMST | UCSYNC;
	UCB0CTL1 |= UCSSEL1;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;

	P1DIR |= BIT0;

	UCB0CTL1 &= ~UCSWRST;
}
/*
 * Subroutine Name: writeCommandNibble
 * Author: Ryan Hub
 * Function: Sends a nibble to LCDWRT4
 * Inputs: commandNibble
 * Outputs: none
 * Subroutines used: LCDWRT4, microDelay
 */
void writeCommandNibble(char commandNibble) {
	LCDCON &= ~RS_MASK;
	LCDWRT4(commandNibble);
	microDelay();
}
/*
 * Subroutine Name: writeCommandByte
 * Author: Ryan Hub
 * Function: Sends a command byte to the LCD
 * Inputs: commandByte
 * Outputs: none
 * Subroutines used: LCDWRT8, microDelay
 */
void writeCommandByte(char commandByte) {
	LCDCON &= ~RS_MASK;
	LCDWRT8(commandByte);
	microDelay();
}
/*
 * Subroutine Name: writeDataByte
 * Author: Ryan Hub
 * Function: Sends a character to the LCD screen
 * Inputs: dataByte
 * Outputs: none
 * Subroutines used: LCDWRT8, milliDelay
 */
void writeDataByte(char dataByte) {
	LCDCON |= RS_MASK;
	LCDWRT8(dataByte);
	milliDelay();
}
/*
 * Subroutine Name: lcdClear
 * Author: Ryan Hub
 * Function: clears the LCD screen
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void lcdClear() {
	writeCommandByte(1);
}
/*
 * Subroutine Name: lcdInitialize
 * Author: Ryan Hub
 * Function: Initializes the LCD on the geek box
 * Inputs: none
 * Outputs: none
 * Subroutines used: spiSEND, microDelay, writeCommandNibble, writeCommandByte
 */
void lcdInitialize() {
	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x02);

	writeCommandByte(0x28);

	writeCommandByte(0x0C);

	writeCommandByte(0x01);

	writeCommandByte(0x06);

	writeCommandByte(0x01);

	writeCommandByte(0x02);

	spiSEND(0x0);
	microDelay();
}
/*
 * Subroutine Name: displayScreen
 * Author: Ryan Hub
 * Function: Displays a string of 8 characters to the LCD display
 * Inputs: message- the String to be outputed to the display screen
 * Outputs: none
 * Subroutines used: writeDataByte
 */
void displayScreen(char * message) {
	int lineLength = 8;
	int i;
	for (i = 0; i <= lineLength; i++) {
		writeDataByte(message[i]);
	}
}
/*
 * Subroutine Name: rotateString
 * Author: Ryan Hub
 * Function: Rotates the string
 * Inputs: stringToRotate- the message that is being rotated on the screen
 * 		  stringLength- the length of the string
 * Outputs: none
 * Subroutines used: writeDataByte
 */
void rotateString(char * stringToRotate, int stringLength) {
	char firstChar = *stringToRotate;
	int i;
	for (i = 0; i < stringLength; i++) {
		stringToRotate[i] = stringToRotate[i + 1];
	}

	stringToRotate[stringLength] = firstChar;
}
/*
 * Subroutine Name: scrollDisplay
 * Author: Ryan Hub
 * Function: Scrolls the message on the LCD screen
 * Inputs: message- the String to be outputed to the display screen
 * Outputs: none
 * Subroutines used: writeDataByte
 */
void scrollDisplay(char topMessage[], char bottomMessage[]) {
	lcdClear();
	while (1) {

		goToTopLine();
		displayScreen(topMessage);
		rotateString(topMessage, 28);
		_delay_cycles(0xf00f); //How fast the message is being scrolled through

		goToBottomLine();
		displayScreen(bottomMessage);
		rotateString(bottomMessage, 28);
		_delay_cycles(0xf00f);
	}
}
/*
 * Subroutine Name: buttonInitialize
 * Author: Ryan Hub
 * Function: Initializes the buttons on the geek box
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void buttonInitialize() {
	P1OUT |= BIT1;
	P1REN |= BIT1;
	P1DIR &= ~BIT1;

	P1OUT |= BIT2;
	P1REN |= BIT2;
	P1DIR &= ~BIT2;

	P1OUT |= BIT3;
	P1REN |= BIT3;
	P1DIR &= ~BIT3;
}
/*
 * Subroutine Name: buttonSelect
 * Author: Ryan Hub
 * Function: Waits for a button to be pressed on the geek box
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */
void buttonSelect() {
	while ((BIT1 & P1IN) && (BIT2 & P1IN) && (BIT3 & P1IN)) {
		// does nothing until a button is pressed
	}
}


