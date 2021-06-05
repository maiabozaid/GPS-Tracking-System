#include "tm4c123gh6pm.h"

void delay(int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 3180; j++)
		{
		} /* do nothing for 1 ms */
	}
}

void LCD_command(char x) {
	GPIO_PORTC_DATA_R &= ~0xE0;	 // Rs,Rw,E : bins c5 ,c6,c7(1110 0000 = 0XE0)  all = zero 
	GPIO_PORTB_DATA_R = x;
	GPIO_PORTC_DATA_R |= 0x80;  //enable: from 0 to 1
	delay(500);
	GPIO_PORTC_DATA_R &= ~0x80;	//enable: from 1 to 0
}

void LCD_DATA(char y) {
	GPIO_PORTC_DATA_R = 0X20;	 // Rs =1 , Rw &E = 0 
	GPIO_PORTB_DATA_R = y;
	GPIO_PORTC_DATA_R |= 0x80; //ENABLING
	delay(500);
	GPIO_PORTC_DATA_R &= ~0x80;
	LCD_command(0x06);	//Increment cursor
}

void intial_LCD(void)
{

	SYSCTL_RCGCGPIO_R |= 0x06;  //ports b and C are connected to clock - port B is data & port C is control 
	while ((SYSCTL_PRGPIO_R & 0x06) == 0);

	//unlocking pins
	GPIO_PORTB_LOCK_R = 0x4C4F434B;  
	GPIO_PORTB_CR_R = 0xFF; // control all pins
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_DEN_R = 0xFF; 
	GPIO_PORTB_DIR_R = 0xFF; // all are output
	//GPIO_PORTB_DATA_R = 'H';

									 // PORT C
	GPIO_PORTC_LOCK_R = 0x4C4F434B;    // rs : bin 0 ,rw: bin 1 ,enable : bin 2  output  //101
	GPIO_PORTC_CR_R |= 0xE0;	// Although they are already = 1 but just to make the code general
	GPIO_PORTC_AMSEL_R &= ~0xE0;
	GPIO_PORTC_AFSEL_R &= ~0xE0;
	GPIO_PORTC_PCTL_R &= 0X000FFFFF;
	GPIO_PORTC_DEN_R |= 0xE0;
	GPIO_PORTC_DIR_R |= 0xE0;

	LCD_command(0x30); //wakeup lcd
	delay(500);
	LCD_command(0x01); //clear screen
	delay(500);
	LCD_command(0x80); //Force cursor to beginning of 1st line
	delay(500);
	LCD_command(0x0f); //Display on, cursor blinking
	delay(500);
}
