/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3)
{
	
	if(a3>0 && a3!=1) printf("%.1fx^3", a3);
	else if(a3<0 && a3!=-1) printf("%.1fx^3", a3);
	else if(a3 == -1) printf("-x^3");
	else if(a3 == 1) printf("x^3");
	if(a2>0 && a0!=1) printf("+%.1fx^2", a2);
	else if(a2<0 && a0!=-1) printf("%.1fx^2", a2);
	else if(a2 == -1) printf("-x^2");
	else if(a2 == 1) printf("+x^2");
	if(a1>0 && a1!=1) printf("+%.1fx", a1);
	else if(a1<0 && a1!=-1) printf("%.1fx", a1);
	else if(a1 == -1) printf("-x");
	else if(a1 == 1) printf("+x");
	if(a0>0 && a0!=1) printf("+%.1f", a0);
	else if(a0<0 && a0!=-1) printf("%.1f", a0);
	else if(a0 == -1) printf("%.1f", a0);
	else if(a0 == 1) printf("+%.1f", a0);
	printf("\n");

}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
	if(a4>0 && a4!=1) printf("%.1fx^4", a4);
	else if(a4<0 && a4!=-1) printf("%.1fx^3", a4);
	else if(a4 == -1) printf("-x^4");
	else if(a4 == 1) printf("x^4");
	if(a3>0 && a3!=1) printf("+%.1fx^3", a3);
	else if(a3<0 && a3!=-1) printf("%.1fx^3", a3);
	else if(a3 == -1) printf("-x^3");
	else if(a3 == 1) printf("+x^3");
	if(a2>0 && a2!=1) printf("+%.1fx^2", a2);
	else if(a2<0 && a2!=-1) printf("%.1fx^2", a2);
	else if(a2 == -1) printf("-x^2");
	else if(a2 == 1) printf("+x^2");
	if(a1>0 && a1!=1) printf("+%.1fx", a1);
	else if(a1<0 && a1!=-1) printf("%.1fx", a1);
	else if(a1 == -1) printf("-x");
	else if(a1 == 1) printf("+x");
	if(a0>0 && a0!=1) printf("+%.1f", a0);
	else if(a0<0 && a0!=-1) printf("%.1f", a0);
	else if(a0 == -1) printf("%.1f", a0);
	else if(a0 == 1) printf("+%.1f", a0);
	printf("\n");
}
