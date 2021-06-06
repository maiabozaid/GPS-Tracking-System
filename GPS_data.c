#include "D:/2nd computer/2nd term/Embedded Systems/tm4c123gh6pm.h"
#include "stdint.h"

uint8_t UART0_InChar()
{
 while ((UART0_FR_R & 0x0010) != 0);        // wait until RXFE isn't empty 
 return ((uint8_t)(UART0_DR_R & 0xff));     // Read UART0 data ,cast to integer
}

