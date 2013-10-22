#include "lcd.h"

char LCDCON, LCDSEND, LCDDATA;

char r4;

void setSS_HI() {
	P1OUT |= BIT0;
}

void setSS_LO() {
	P1OUT &= ~BIT0;
}


void spiSEND(char inputByte) {
	setSS_LO();
	UCB0TXBUF = inputByte;

	while (UCB0RXIFG == IFG2) {
		IFG2 = UCB0RXIFG;
	}
		r4 = UCB0TXBUF;

	setSS_HI();
}




void LCDWRT4 (char LCDCON, char LCDDATA) {
	char tempR5;
	tempR5 = LCDDATA;
	tempR5 &= 0x0f;
	tempR5 |= LCDCON;
	spiSEND(0x0);
	_delay_cycles(0x0238);
	tempR5 |= 0x80;
	spiSEND(0x0);
	_delay_cycles(0x0238);
	tempR5 &= 0x7f;
	spiSEND(0x0);
	_delay_cycles(0x0238);

}

void LCDWRT8(char LCDSEND) {
	char tempR5;
	tempR5 = LCDSEND;
	tempR5 &= 0xf0;
	tempR5 >> 4;
	LCDDATA = tempR5;
	LCDWRT4(0, LCDDATA);
	tempR5 = LCDSEND;
	tempR5 &= 0x0f;
	LCDDATA = tempR5;
	LCDWRT4(LCDCON,LCDDATA);
}

void initSPI() {

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 |= UCCKPL|UCMSB|UCMST|UCSYNC;
	UCB0CTL1 |= UCSSEL1;
	UCB0STAT |= UCLISTEN;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;

	P1DIR |= BIT0;

	UCB0CTL1 &= ~UCSWRST;
}




void lcdClear() {
	LCDCON = 0x0;
	LCDSEND = 0x1;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);
	LCDCON = 0x40;
	_delay_cycles(0x000a);
}


void lcdInitialize() {
	setSS_HI();
	LCDCON = 0x0;
	LCDDATA = 0x3;
	LCDWRT4(LCDCON, LCDDATA);
	_delay_cycles(0x0238);

	LCDDATA = 0x3;
	LCDWRT4(LCDCON, LCDDATA);
	_delay_cycles(0x000a);

	LCDDATA = 0x3;
	LCDWRT4(LCDCON, LCDDATA);
	_delay_cycles(0x000a);

	LCDDATA = 0x2;
	LCDWRT4(LCDCON, LCDDATA);
	_delay_cycles(0x000a);


	LCDSEND = 0x28;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);

	LCDSEND = 0x0c;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);

	LCDSEND = 0x01;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x000a);

	LCDSEND = 0x06;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);

	LCDSEND = 0x01;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);

	LCDSEND = 0x02;
	LCDWRT8(LCDSEND);
	_delay_cycles(0x0238);

	spiSEND(0x0);
	_delay_cycles(0x000a);
}



