#include "tm4c123gh6pm.h" 

void delay(int n);
void LCD_command(char x);
void LCD_DATA(char y);
void LCD_display_string(char* mystring);
void LCD_number(int x) ;
void intial_LCD(void);
void reverse(char* str, int len);
int integerToString(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);
