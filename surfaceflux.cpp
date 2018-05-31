#include "illithermfvheaders.h"

float solar(weather weatherObject){
	
	int N1, N2, N3, N;
	float declination, rHour, A, B, coshA, HA, Z, tsunrise, tsunset, time;
	const float d2r = M_PI/180.0; //Conversion factor, deg to rad 
	float qsolar;
	
	/***** Calculate time of sunrise and sunset *****/
	/*Based on the thesis by Prof. Dempsey, 1969*/
	/*ASSUMPTIONS - Solar noon is at 12.0, Earth's orbit is circular*/
	
	//Day of the year
	N1 = floor(275*weatherObject.Month/9);
	N2 = floor((weatherObject.Month+9)/12);
	N3 = (1+floor((weatherObject.Year - 4*floor(weatherObject.Year/4) + 2)/3));
	N = N1 - (N2*N3) + weatherObject.Day - 30;
	
	declination = 23.45*d2r*sin(2*M_PI*(284+N)/365);
	rHour = 15.0*d2r; //One hour (1/15 of a degree) in radians
	
	//Calculate A and B coefficients
	if(declination<0){
		A = -sin(fabs(declination));
		B = cos(fabs(declination));
	}
	else{
		A = sin(declination);
		B = cos(declination);
	}
	
	//Calculate Z
	coshA = -(sin(weatherObject.Lat*d2r)*A)/(cos(weatherObject.Lat*d2r)*B);
	HA = acos(fabs(coshA));
	
	if(coshA<0){
		Z = 180.0*d2r-HA;
	}
	else{
		Z = HA;
	}
	
	//Calculate tsunrise and tsunset
	time = Z/rHour;
	tsunrise = 12.0 - time;
	tsunset = 12.0 + time;
	//Verified that this works - SS 5.30.18
	
	/***** Calculate solar radiation *****/
	/*Following Qin & Hiller (2011), the solar radiation between sunrise and sunset is assumed to be sinusoidal*/
	/*The peak value of the radiation is 1000 W/m2 if sun > 90, 700 W/m2 if sun > 30, and 300 W/m2 otherwise*/
	/*These assumptions for sun are mine, since sunny, partly sunny, and cloudy are not defined in McCollough & Rasmussen (1999)*/
	/*Noe that this does not depend on latitude (but it should) and Dempsey recommends a different formula. This mostly works for CONUS*/
	/*Dempsey (in Customary): ExRad = (24.0 / Math.PI) * 444.7 * 1 * Math.Sin(latitude * d2r) * A * (Z - Math.Tan(Z))*/
	
	if(weatherObject.Sun > 90){qsolar = 1000.0;}
	else if(weatherObject.Sun > 30){qsolar = 700.0;}
	else{qsolar = 300.0;}
	
	if(weatherObject.Hour < tsunrise || weatherObject.Hour > tsunset){
		return 0.0;
	}
	else{
		return qsolar*sin(M_PI*(weatherObject.Hour - tsunrise)/(tsunset - tsunrise));
	}

}