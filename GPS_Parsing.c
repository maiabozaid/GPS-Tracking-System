#include "D:/2nd computer/2nd term/Embedded Systems/Project/tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"
#include <stdlib.h>
#define messageMaxSize   60
#define lat_length   12
void UART0_INIT(){
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

UART0_CTL_R &= ~ UART_CTL_UARTEN;
UART0_IBRD_R = 104;            // System Clock = 16 MHZ    by default
UART0_FBRD_R = 11;
UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN)  ;
UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
  
GPIO_PORTA_AFSEL_R |= 0x03;
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF)|(GPIO_PCTL_PA1_U0TX|GPIO_PCTL_PA0_U0RX);
GPIO_PORTA_DEN_R |= 0x03;
GPIO_PORTA_AMSEL_R &= ~0x03;  
}

uint8_t UART0_Available(){
  return ((UART0_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}

void UART0_write(char data){
  while((UART0_FR_R & UART_FR_TXFF)==UART_FR_TXFF){};
    UART0_DR_R = data;
}


char UART0_read(){
	 char c;
   while(UART0_Available() !=1){}; 
	
	 c=(char)(UART0_DR_R & 0xFF); 
	 UART0_write(c);               // write the read character on the screen
	 return c;   

    }

void get_message(char* mess){
char m;
uint8_t i=1;
while(1){
m=UART0_read();
if(m=='$')
	break;
}
mess[0]=m;

for(i=1;i<messageMaxSize;i++)
{
m=UART0_read();
if(m=='E' ||m=='W')
  break;
mess[i]=m;
}

}		

uint8_t is_RMC(char* mess){
uint8_t i=0;
char header[6];
for(i=0;i<6;i++){
header[i]=mess[i];
}
if(strcmp(header, "$GPRMC")==0)
return 1;

return 0;
}

uint8_t GPS_Fix(char* mess){
uint8_t i=0;
uint8_t j=0;
for(i=0;i<messageMaxSize;i++){
if(mess[i]==',')
  j++;
if(j==2)
  break;	
}
return mess[i+1];
}




char message[messageMaxSize];
char t;

int main(){
UART0_INIT();
	
do{
get_message(message);
}while(is_RMC(message)==0 || GPS_Fix(message)=='V' );


}
