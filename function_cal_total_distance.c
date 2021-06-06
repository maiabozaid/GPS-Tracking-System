#include "stdint.h"
#include <math.h>
#define pi  3.14159265358979323846	
float convert_deg2rad(float degree);
float convert_rad2deg(float radian);
float cal_distance(float latitude_1, float longitude_1, float latitude_2, float longitude_2);
int main()
{
	cal_distance(12.32, 20.32, 13.15, 21.23);//initional values


}
float total_distance = 0;
while(1){
	float cal_distance(float latitude_1, float longitude_1, float latitude_2, float longitude_2) //function has 4 float inputs represent tow points in the coordinates and char select to select  units which show data
	{
		float theta, distance;
		if ((latitude_1 == latitude_2) && (longitude_1 == longitude_2))
			return 0; //this means that you didn't move so the total distance equal zero 
		else
		{
			
				theta = longitude_1 - longitude_2;
				distance = sin(convert_deg2rad(latitude_1)) * sin(convert_deg2rad(latitude_2)) + cos(convert_deg2rad(latitude_1)) * cos(convert_deg2rad(latitude_2)) * cos(convert_deg2rad(theta));
				distance = acos(distance);
				distance = convert_rad2deg(distance);
				distance = distance * 60 * 1.1515;
				distance = distance * 1.609344;
				distance = distance * 1.609344 * 1000;
				total_distance += distance;
				return total_distance; //it will return total distance (meter)
				latitude_1 = latitude_2;
				longitude_1 = longitude_2;
			
		}
	}
	float  convert_deg2rad(float degree)   //function converts from degree to radian;;;; 
	{
		return (degree * pi / 180);
	}
	float convert_rad2deg(float radian)  //function converts from radian to degree
	{
		return (radian * 180 / pi);
	}
