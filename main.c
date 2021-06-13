#include "tm4c123gh6pm.h" 
#include "LCD.h"
#include "led_on_off.h";
#include "final_cal_total_distance.h"





char message[messageMaxSize];
char latitudeChar[lat_long_length];
char longitudeChar[lat_long_length];
float latitude;
float longitude;
float lat_1 , long_1 , lat_2 , long_2 ;


void main(){

  UART0_INIT();
  
 
  do{
  get_message(message);
  }while(is_RMC(message)==0 || GPS_Fix(message)=='V' );
  get_lat_long_char(message,latitudeChar,latComma);
  get_lat_long_char(message,longitudeChar,longComma);
  latitude=atof(latitudeChar);
  longitude=atof(longitudeChar);
  lat_1 =DMM_to_DD(latitude);  
  long_1 =DMM_to_DD(longitude);
  

  float sum = 0 ;
  float diff ;





      do{

          
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
          
          
          
          
          

     
          //LCD print total ( print float )
      

      }while( sum < 100   );
      RGBLED_Init ();
      void led_on();
      
      // turn led on
      LCD_display_string("Finished") ;
      

}
