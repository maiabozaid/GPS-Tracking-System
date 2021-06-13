#include "GPS_Parsing.h"
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

///////////////////////////////////

char UART5_read(){
   while((UART5_FR_R & 0x0010) !=0);  
	 return  (char)(UART5_DR_R & 0xFF);    
}


void get_message(char* mess){
char m;
uint8_t i=1;
while(1){
m=UART5_read();
if(m=='$')
	break;
}
mess[0]=m;

for(i=1;i<messageMaxSize;i++)
{
m=UART5_read();
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
///////////////////////////

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


void get_lat_long_char(char* mess,char* latORlongChar,uint8_t commaNum){
uint8_t i=0;
uint8_t j=0;
for(i=0;i<messageMaxSize;i++){
if(mess[i]==',')
  j++;
if(j==commaNum){
  i++;  
  break;}	
}
j=0;
for(i=i;i<messageMaxSize;i++){
if(mess[i]==',')
  break;	
latORlongChar[j]=mess[i];
j++;
}
}
//////////////////////////

float DMM_to_DD(float DMM){
float DD;
DD=(int)(DMM/100);
DD=DD+((DMM - DD*100)/60);
return DD;
}
