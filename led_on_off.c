#include"led_on_off.h"
#include "stdint.h"

void SystemInit(){}

void RGBLED_Init ()
{
SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R&0x20) == 0){};
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTF_DIR_R |= 0X0E;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTF_AFSEL_R &=~0x0E;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTF_DATA_R &= ~0x0E;
}

void led_off(){
RGBLED_Init ();
GPIO_PORTF_DATA_R &= ~0x02;

}
void led_on(){
RGBLED_Init ();
GPIO_PORTF_DATA_R |=0x02;


}
