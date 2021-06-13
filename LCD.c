#include "LCD.h"

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
	delay(100);
	GPIO_PORTC_DATA_R &= ~0x80;	//enable: from 1 to 0
}

void LCD_DATA(char y) {
	GPIO_PORTC_DATA_R = 0X20;	 // Rs =1 , Rw &E = 0 //00100000 =0x20
	GPIO_PORTB_DATA_R = y;
	GPIO_PORTC_DATA_R |= 0x80; //ENABLING 
	delay(50);
	GPIO_PORTC_DATA_R &= ~0x80;  //enable: from 1 to 0
	LCD_command(0x06);	//Increment cursor
}

void LCD_display_string(char* mystring)
{
    int display_position = 0;
   
    while(*(mystring))
    {
        LCD_DATA( *(mystring++) );
        display_position++;
	if ( !(display_position %32) )   // 2 lines are full
                {
                    display_position = 0;
                    delay(300);
                    LCD_command(0x01);  //clear screen
                    LCD_command(0x80);  //move cursor to beginning of first line
                }
                else if (!(display_position % 16))      // first line is full
                {

                        LCD_command(0xC0);  //move cursor to beginning of second line

    }
    }
}

void LCD_number(int x) {

    char y = (char) x+48 ;
     LCD_DATA(y);
     LCD_command(0x06);

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
	

									 // PORT C
	GPIO_PORTC_LOCK_R = 0x4C4F434B;    
	GPIO_PORTC_CR_R |= 0xE0;	// Although they are already = 1 but just to make the code general
	GPIO_PORTC_AMSEL_R &= ~0xE0;
	GPIO_PORTC_AFSEL_R &= ~0xE0;
	GPIO_PORTC_PCTL_R &= 0X000FFFFF;
	GPIO_PORTC_DEN_R |= 0xE0;
	GPIO_PORTC_DIR_R |= 0xE0;

	LCD_command(0x30); //wakeup lcd
	delay(100);
	LCD_command(0x01); //clear screen
	delay(100);
	LCD_command(0x38); //2 lines 8bits 
        delay(100);
	LCD_command(0x80); //Force cursor to beginning of 1st line
	delay(100);
	LCD_command(0x0f); //Display on, cursor blinking
	delay(100);
}
//FOR TESTING:
// int main() {
//     intial_LCD();
//     LCD_display_string("Welcome to our  GPS Project"); // string displaying
//     delay(500);
//     LCD_command(0x01); //clear screen
	
//     LCD_display_string("Number: "); 
//     LCD_number(1) ; // Number displaying
//     delay(500);
//     LCD_command(0x01); //clear screen
	
//     LCD_display_string("Char: ");
//     LCD_DATA('A') ; // Char displaying
//     delay(500);
//     LCD_command(0x01); //clear screen
	
//     LCD_display_string("Hexa values:"); // sending hexa decimal values 
//     LCD_DATA(0x32) ;
//     LCD_DATA(0x26) ;
//     LCD_DATA(0x4D) ;
//     delay(500);
//     LCD_command(0x01); //clear screen
	
//     LCD_display_string("Thanks!");


// }
