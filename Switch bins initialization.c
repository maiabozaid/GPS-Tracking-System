void PortF_Init (void){ 
SYSCTL_RCGCGPIO_R |= 0x20;  // activate clock for port F  
while ((SYSCTL_PRGPIO_R & 0x20) == 0){};  // Wait for stabilization
GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock GPIO port F
GPIO_PORTF_CR_R |= 0x11; // Allow changes to PF4 and PF0
GPIO_PORTF_AMSEL_R &= ~0x11; // Disable analog on PF
GPIO_PORTF_PCTL_R &= ~0x000F000F; // PTCL GPIO on PF4 and PF0
GPIO_PORTF_DIR_R &= ~0x11; // PF4 and PF0 inputs
GPIO_PORTF_AFSEL_R &= ~0x11; // Disable alt function on PF4-0
GPIO_PORTF_DEN_R |= 0x11; // Enable digital input on PF4 and PF0

GPIO_PORTF_PUR_R |= 0x11;// Enable pull up on PF4 and PF0 for SW 
}
