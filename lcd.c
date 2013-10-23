#include "lcd.h"

char LCDCON = 0;

#define RS_MASK 0x40


void setSS_HI() {
	P1OUT |= BIT0;
}

void setSS_LO() {
	P1OUT &= ~BIT0;
}


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

void LCDWRT4 (char sendByte) {
	sendByte &= 0x0f;
	sendByte |= LCDCON;
	sendByte &= 0x7f;
	spiSEND(sendByte);
	_delay_cycles(0x0238);
	sendByte |= 0x80;
	spiSEND(sendByte);
	_delay_cycles(0x0238);
	sendByte &= 0x7f;
	spiSEND(sendByte);
	_delay_cycles(0x0238);
}

void LCDWRT8(char byteToSend) {
	unsigned char sendByte = byteToSend;
	sendByte &= 0xF0;
	sendByte = sendByte >> 4;
	LCDWRT4(sendByte);
	sendByte = byteToSend;
	sendByte &= 0x0f;
	LCDWRT4(sendByte);
}

void initSPI() {

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;
	UCB0CTL1 |= UCSSEL1;
	//UCB0STAT |= UCLISTEN;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;

	P1DIR |= BIT0;

	UCB0CTL1 &= ~UCSWRST;
}

void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCDWRT4(commandNibble);
    _delay_cycles(0x000a);
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCDWRT8(commandByte);
    _delay_cycles(0x000a);
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCDWRT8(dataByte);
    _delay_cycles(0xeeee);
}

void lcdClear() {
	writeCommandByte(1);
}

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
	_delay_cycles(0x000a);
}

void displayScreen(char * message) {
	int length = 29;
	int i;
	for (i = 0; i <= length; i++) {
		writeDataByte(message[i]);
	}
}


void scrollDisplay( char * message) {
	lcdClear();
	char * originalMessage = message;
	int i;
	int j = 0;
	while(1) {
	for(i = 0; i < 8; i++) {
		writeDataByte(message[i+j]);
		if(message[i+j] == '!') {
			scrollDisplay(originalMessage);
		}
	}
	lcdClear();
	j++;
	}

}
