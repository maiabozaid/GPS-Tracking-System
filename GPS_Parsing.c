#include "D:/2nd computer/2nd term/Embedded Systems/Project/tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"
#include <stdlib.h>
#define messageMaxSize   60
#define lat_long_length   15
#define latComma     3
#define longComma     5
void UART5_INIT(){
SYSCTL_RCGCUART_R |= 0x20 ;       //0000 0000   PORT E
SYSCTL_RCGCGPIO_R |= 0x10 ;
UART5_CTL_R &= ~0x01;
UART5_IBRD_R = 104;            // System Clock = 16 MHZ    by default
UART5_FBRD_R = 11;
UART5_LCRH_R |= 0x70  ;
UART5_CTL_R = 0x0301;
  
GPIO_PORTE_AFSEL_R |= 0x30;
GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R &= ~0x00ff0000)|(0x00110000);
GPIO_PORTE_DEN_R |= 0x30;
GPIO_PORTE_AMSEL_R &= ~0x30;  
}

void UART5_write(char data){
  while((UART5_FR_R & 0x0020)!=0){};
    UART5_DR_R = data;
}
