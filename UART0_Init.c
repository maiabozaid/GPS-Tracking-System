#include "tm4c123gh6pm.h"

void A_UART0_Init()
{
SYSCTL_RCGCUART_R |= 0x0001    ;        // Activate UART0
SYSCTL_RCGCGPIO_R |= 0x0001    ;        // Activate port A
UART0_CTL_R       &= ~0x0001   ;        // disable UART0 (to avoid sending data during Configuration)
UART0_IBRD_R       = 0x0208    ;
UART0_FBRD_R       = 0x0035    ; 
UART0_LCRH_R       = 0x0070    ;        // Enable FIFO and 8-bit word lengh
UART0_CTL_R        = 0x0301    ;        // Enable UART , RXE and TXE 
GPIO_PORTA_AFSEL_R|= 0x03      ;        // Enable alternate function for PAO and PA1
GPIO_PORTA_PCTL_R  =(GPIO_PORTA_PCTL_R & ~0x000000ff)|0x00000011;  // clear the old 8-bits corresponding to PAO and PA1 .set the bits that enable UART0
GPIO_PORTA_DEN_R  |= 0x03      ;        // Enable digital for PAO and PA1 
GPIO_PORTA_AMSEL_R&= 0x03      ;        // disable analog for PAO and PA1 
}
