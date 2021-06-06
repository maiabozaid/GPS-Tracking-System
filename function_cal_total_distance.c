#include "function_cal_total_distance.h"
#define pi  3.14159265358979323846	
int main()
{	float total_distance = 0.0;
 	float distance ;
	while(1){
	distance = cal_distance(12.32, 20.32, 13.15, 21.23);//initional values (these values will take them from GPS but i initionalize them to test the code
	total_distance+=distance ;
	if(total_distance >100)
		break;
	}
	
}


	float cal_distance(float latitude_1, float longitude_1, float latitude_2, float longitude_2) //function has 4 float inputs represent tow points in the coordinates 
	{
		float theta, distance;
		if ((latitude_1 == latitude_2) && (longitude_1 == longitude_2))
			return 0; //this means that you don't move so the total distance equal zero 
		else
		{
			
				theta = longitude_1 - longitude_2;
				distance = sin(convert_deg2rad(latitude_1)) * sin(convert_deg2rad(latitude_2)) + cos(convert_deg2rad(latitude_1)) * cos(convert_deg2rad(latitude_2)) * cos(convert_deg2rad(theta));
				distance = acos(distance);
				distance = convert_rad2deg(distance);
				distance = distance * 60 * 1.1515;
				distance = distance * 1.609344;
				distance = distance * 1.609344 * 1000;
				return distance; //it will return distance (meter)
				
			
		}
	}
	float  convert_deg2rad(float degree)   //function converts from degree to radian
	{
		return (degree * pi / 180);
	}
	float convert_rad2deg(float radian)  //function converts from radian to degree
	{
		return (radian * 180 / pi);
	}
