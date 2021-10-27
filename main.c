#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "led_on_off.h"
#include "final_cal_total_distance.h"
#include "GPS_Parsing.h"





char message[messageMaxSize];
char latitudeChar[lat_long_length];
char longitudeChar[lat_long_length];
double latitude;
double longitude;
double lat_1 , long_1 , lat_2 , long_2 ;
void ftoa(double n, char* res, int afterpoint) ;
void reverse(char* str, int len);
int integerToString(int x, char str[], int d);



void main(){

  UART5_INIT();
  intial_LCD();



  do{
  get_message(message);
  }while(is_RMC(message)==0 || GPS_Fix(message)=='V' );
  get_lat_long_char(message,latitudeChar,latComma);
  get_lat_long_char(message,longitudeChar,longComma);
  latitude=atof(latitudeChar);
  longitude=atof(longitudeChar);
  lat_1 =DMM_to_DD(latitude);
  long_1 =DMM_to_DD(longitude);


  double sum = 0 ;
  double diff=0 ;





      while (1){

          do{
          get_message(message);
          }while(is_RMC(message)==0 || GPS_Fix(message)=='V' );
          get_lat_long_char(message,latitudeChar,latComma);
          get_lat_long_char(message,longitudeChar,longComma);
          latitude=atof(latitudeChar);
          longitude=atof(longitudeChar);
          lat_2 =DMM_to_DD(latitude);
          long_2 =DMM_to_DD(longitude);

          diff = cal_distance( lat_1, long_1 , lat_2 , long_2 );
          sum = sum + diff ;

          lat_1 = lat_2 ;
          long_1 = long_2 ;

      memset(message,0,messageMaxSize);
      memset(latitudeChar,0,lat_long_length);
      memset(longitudeChar,0,lat_long_length);


      LCD_command(0x01); //clear screen
      char res[20];
      ftoa(sum, res, 4);
      LCD_display_string(res);






     if ( sum >= 100  ) break ;
      }



      RGBLED_Init ();
      led_on();

      LCD_command(0x01); //clear screen
      LCD_display_string("total distance =") ;
      LCD_command(0xC0); //2nd line
      char res[20];
      ftoa(sum, res, 4);
      LCD_display_string(res);



}







void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
int integerToString(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}
void ftoa(double n, char* res, int afterpoint)
{
    int ipart = (int)n;
    double fpart = n - (double)ipart;
    int i = integerToString(ipart, res, 0);
    if (afterpoint != 0) {
        res[i] = '.';

        fpart = fpart * pow(10, afterpoint);

        integerToString((int)fpart, res + i + 1, afterpoint);
    }
}
