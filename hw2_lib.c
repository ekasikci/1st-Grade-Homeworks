/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include <math.h>
#include "hw2_lib.h"


int find_weekday_of_data(int day, int month, int year)
{
    
    int m_number, result;
    
    /* This statement checks the input whether is valid date or not */
    if (month > 12 || month < 1 || day > 31 || day < 1 || year < 0)
    { 
     	printf("\n!!! Invalid date !!!\n");
    	return 0;
    }
    
    /* This statements calculate the number of days corresponding month */        
    switch (month) {
    case 1: month = 0;
    break;
    case 2: month = 31;
    break;
    case 3: month = 59;
    break;
    case 4: month = 90;
    break;
    case 5: month = 120;
    break;
    case 6: month = 151;
    break;
    case 7: month = 181;
    break;
    case 8: month = 212;
    break;
    case 9: month = 243;
    break;
    case 10: month = 273;
    break;
    case 11: month = 304;
    break;
    case 12: month = 334;
    }
    
    /* This part of the code finds the total days of the corresponding date and calculates which day of the week it is. */
    result = (((year * 365) + (year / 4) + (year / 400) - (year / 100)) + month + day) -1; 
    result = result % 7;
    
    if (result == 0) result = 7;
    
    if((year % 4 == 0) && (month == 0 || month == 31)) result = result -1 ;
    
    if (result == 0) result = 7;
    
    return result;
}


int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    
    int endmonthdays, startmonthdays, result, end, start;
    
    /* This statement checks the input whether is valid date or not */
    if (start_month > 12 || start_month < 1 || start_day > 31 || start_day < 1 || end_month > 12 || end_month < 1 || end_day > 31 || end_day < 1 || start_year < 0 || end_year < 0)
    { 
     	printf("\n!!! Invalid date !!!\n");
    	return 0;
    }
     
    /* This statements calculate the number of days corresponding month */        
    switch (start_month) {
    case 1: startmonthdays = 0;
    break;
    case 2: startmonthdays = 31;
    break;
    case 3: startmonthdays = 59;
    break;
    case 4: startmonthdays = 90;
    break;
    case 5: startmonthdays = 120;
    break;
    case 6: startmonthdays = 151;
    break;
    case 7: startmonthdays = 181;
    break;
    case 8: startmonthdays = 212;
    break;
    case 9: startmonthdays = 243;
    break;
    case 10: startmonthdays = 273;
    break;
    case 11: startmonthdays = 304;
    break;
    case 12: startmonthdays = 334;
    }
    
    switch (end_month) {
    case 1: endmonthdays = 0;
    break;
    case 2: endmonthdays = 31;
    break;
    case 3: endmonthdays = 59;
    break;
    case 4: endmonthdays = 90;
    break;
    case 5: endmonthdays = 120;
    break;
    case 6: endmonthdays = 151;
    break;
    case 7: endmonthdays = 181;
    break;
    case 8: endmonthdays = 212;
    break;
    case 9: endmonthdays = 243;
    break;
    case 10: endmonthdays = 273;
    break;
    case 11: endmonthdays = 304;
    break;
    case 12: endmonthdays = 334;
    }
  
    /* This part of the code finds the total days of the corresponding dates and subtracts them from each other to calculate the range. */
    end = (((end_year * 365) + (end_year / 4) + (end_year / 400) - (end_year / 100)) + endmonthdays + end_day);
    start =  (((start_year*365) + (start_year / 4) + (start_year / 400) - (start_year / 100)) + startmonthdays + start_day);
    
    if (start > end) printf("\n!!! Start date is after than end date !!!\n");
    else if (start == end) printf("\n!!! The dates are same !!!\n");
    
    if((end_year % 4 == 0) && (endmonthdays > 31)) end = end + 1;
    if((start_year % 4 == 0) && (startmonthdays > 31)) start = start + 1;
    result = end - start;
               
    return result;
}


double find_angle(double a, double b, double c)
{
    double va, vb, vc, cosa1, cosa2, angle1, angle2;
    
    /* This statement checks if the inputs are valid for a triangle */
    if ((a + b) <= c || (a + c) <= b || (b + c) <= a || a <= 0 || b <= 0 || c <=0)
    {
    	printf("\n!!! Invalid triangle !!!\n");
    	return 0;
    }
        
    va = ((b*b) + (c*c) - (a*a/2)) / 2; /* This parts of the code calculates the square of medians of the triangle. */
    vb = ((a*a) + (c*c) - (b*b/2)) / 2;
    vc = ((a*a) + (b*b) - (c*c/2)) / 2;
    
    va = sqrt(va); /* Where medians are square rooted. */
    vb = sqrt(vb);
    vc = sqrt(vc);  
   
    /* In here the formula which calculates the cosine of the angle by using edges of triangle is applied. */
    cosa1 = ((a / 2)*(a / 2) - (va / 3)*(va / 3) - ((vc * 2) / 3)*((vc * 2) / 3)) / (-2 * (va / 3) * ((vc * 2) / 3));
    cosa2 = ((a / 2)*(a / 2) - (va / 3)*(va / 3) - ((vb * 2) / 3)*((vb * 2) / 3)) / (-2 * (va / 3) * ((vb * 2) / 3)); 
    
    angle1 = acos(cosa1); /* The angles converted to radian values from cosine values. */
    angle2 = acos(cosa2);
    
    return angle1 + angle2;
}


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
    /* This part of code makes table with simple logic */                     
{
    printf("┌------------------------------------------------┐");
    printf("\n|   Row 101   |");
    printf("   Row ABCDEFG   |");
    printf("   Row XYZ123   |\n");    
    printf("├------------------------------------------------┤");
    printf("\n|  %5d      |", r11);
    printf(" %-10.3g      |", r12);
    printf(" %-6d         |\n", r13);
    printf("├------------------------------------------------┤");
    printf("\n|  %5d      |", r21);
    printf(" %-10.3g      |", r22);
    printf(" %-6d         |\n", r23);
    printf("├------------------------------------------------┤");
    printf("\n|  %5d      |", r31);
    printf(" %-10.3g      |", r32);
    printf(" %-6d         |\n", r33);
    printf("└------------------------------------------------┘");
    printf("\n");

}
