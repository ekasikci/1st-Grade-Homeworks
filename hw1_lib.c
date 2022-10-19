/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include "hw1_lib.h"



double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{

	double first,second,result = 0, sum = 0;
	
	first = xs + delta;
	
	for(second = xs;second < xe;second = second + delta){ /* this for loop will find the integral by applying the trapezoidal rule */
		result = (first-second) * (((((a3*first + a2)*first + a1)*first + a0) +(((a3*second + a2)*second + a1)*second + a0)) / 2);
		first = first + delta;
		sum = result + sum;
	}
	
	return sum;
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{

	double first,second,result = 0, sum = 0;
	
	first = xs + delta;
	
	for(second = xs;second < xe;second = second + delta){ /* this for loop will find the integral by applying the trapezoidal rule */
		result = (first - second) * ((((((a4*first + a3)*first + a2)*first + a1)*first + a0) + ((((a4*second + a3)*second + a2)*second + a1)*second + a0)) / 2);
		first = first + delta;
		sum = result + sum;
	}
	
	return sum;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{

	double root;
	
	/* this for loop will find the root by increasing the xs by 0.001 until reaching the xe and <,> punctuations will avoid the overflow.*/		
	for(root = xs;root < xe;root = root + 0.001){  
	
		if ((((a3*root + a2)*root + a1)*root + a0) < 0.001 && (((a3*root + a2)*root + a1)*root + a0) > -0.001 ){ 
			
			break;
		}
	}
	
	return root;
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{

	double root;
	
	/* this for loop will find the root by increasing the xs by 0.001 until reaching the xe and <,> punctuations will avoid the overflow.*/
	for(root = xs;root < xe;root = root + 0.001){
		if(((((a4*root + a3)*root + a2)*root + a1)*root + a0) < 0.001 && ((((a4*root + a3)*root + a2)*root + a1)*root + a0) > -0.001){
			
			break;
		}
	}
	
	return root;
}
