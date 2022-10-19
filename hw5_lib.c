/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"


void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	double x6 = 0, x5 = 0, x4 = 0, x3 = 0, x2 = 0, x1 = 0, x0 = 0;

	/* These statements determine the operator and implement calculations according it */
	if (op == '+')
	{
		x3 = *a3 + *b3;
		x2 = *a2 + *b2;
		x1 = *a1 + *b1;
		x0 = *a0 + *b0;
	}
	else if (op == '-')
	{
		x3 = *a3 - *b3;
		x2 = *a2 - *b2;
		x1 = *a1 - *b1;
		x0 = *a0 - *b0;
	}
	else if (op == '*')
	{
		x6 = *a3 * *b3;
		x5 = *a3 * *b2 + *a2 * *b3;
		x4 = *a3 * *b1 + *a2 * *b2 + *a1 * *b3;
		x3 = *a3 * *b0 + *a2 * *b1 + *a1 * *b2 + *a0 * *b3;
		x2 = *a2 * *b0 + *a1 * *b1 + *a0 * *b2;
		x1 = *a1 * *b0 + *a0 * *b1;
		x0 = *a0 * *b0;		 
	}
	else /* If the entered values is invalid prints the statement below and doesn't any calculation */
	{
		printf("\n\n\n!!!----Invalid operator----!!!\n\n\n");
	}
	
	*a3 = x6;
	*a2 = x5;
	*a1 = x4;
	*a0 = x3;
	*b3 = x2;
	*b2 = x1;
	*b1 = x0;
}


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	double t0, t1, t2, t3, d0, d1, d2, d3, euclidian_distance;
	int i;

	printf("Please enter a number to determine how many 4D vectors you are going to enter: ");
	scanf("%d", &N);
	printf("\nTo end entering vectors enter 1-1-1-1\n");
	for (i = 0; i < N; i++)
	{
		printf("%d. 4D vector coordinates\n", i);
		scanf("%lf", &d0);
		scanf("%lf", &d1);
		scanf("%lf", &d2);
		scanf("%lf", &d3);

		if (d0 == 1 && d1 == 1 &&  d2 == 1 && d3 == 1) /* Checks if the entered vector is 1-1-1-1 */
		{
			printf("\nVector entering process was terminated!\n\n");
			break;
		}
		
		/* Skips the first cycle (we need two consecutive 4D vectors) */
		if(i > 0)
		{
			distance_between_4d_points (d0 -t0, d1 - t1, d2 - t2, d3 - t3, &euclidian_distance);

			/* İf the new calculated distance between two consecutive 4D vectors is smaller than previous one use previous one */
			if(euclidian_distance > *longest_distance) *longest_distance = euclidian_distance;

		}
		*mean_a0 += d0;
		*mean_a1 += d1;
		*mean_a2 += d2;
		*mean_a3 += d3;

		/* Assigns dimensions of old vector another variables to use them in next cycle */
		t0 = d0;
		t1 = d1;
		t2 = d2;
		t3 = d3;
	}

	/* Calculates the mean values of dimensions */
	*mean_a0 /= N;
	*mean_a1 /= N;
	*mean_a2 /= N;
	*mean_a3 /= N;
		
}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
	/* Takes the root of the sum of the squares of the dimensions to find the distance */
   *euclidian_distance = sqrt(d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3);
}


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int a, b, c, d, e, da = 1, db = 1, dc = 1, dd = 1, de = 1;
	
	printf("Please enter the count of votes of parties\n");
	printf("partyA: ");
	scanf("%d", partyA);
	printf("partyB: ");
	scanf("%d", partyB);
	printf("partyC: ");
	scanf("%d", partyC);
	printf("partyD: ");
	scanf("%d", partyD);
	printf("partyE: ");
	scanf("%d", partyE);
	printf("Please enter the number of seats seats: ");
	scanf("%d", &numberOfSeats);	

	a = *partyA;
	b = *partyB;
	c = *partyC;
	d = *partyD;
	e = *partyE;

	for(numberOfSeats; numberOfSeats > 0; numberOfSeats --) /* The loop laps as many as number of seat to distribute them to the parties */ 
	{
		/* These assignments determine which party is bigger after that increase it's seat number by one and divide the party
		as many as seats they have plus one */
		if((*partyA > *partyB) && (*partyA > *partyC) && (*partyA > *partyD) && (*partyA > *partyE))
		{
			da ++;
			*partyA = a / da;
		}
		else if((*partyB > *partyC) && (*partyB > *partyD) && (*partyB > *partyE))
		{
			db ++;
			*partyB = b / db;
		}
		else if((*partyC > *partyD) && (*partyC > *partyE))
		{
			dc ++;
			*partyC = c / dc;
		}
		else if((*partyD > *partyE))
		{
			dd ++;
			*partyD = d / dd;	
		}
		else
		{
			de ++;
			*partyE = e / de;	
		}
	}
	/* These assignments assign the number of seats to the associated values */
	*partyA = da - 1;
	*partyB = db - 1;
	*partyC = dc - 1;
	*partyD = dd - 1;
	*partyE = de - 1;
}


void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	double s1, s2, s3, area1, area2, area3, tx1, tx2, tx3, ty1, ty2, ty3;

	tx1 = *x1;
	tx2 = *x2;
	tx3 = *x3;
	ty1 = *y1;
	ty2 = *y2;
	ty3 = *y3;

	/* All these conditions below determine areas of points to sort them in counter-clockwise 
	(less field value means it came earlier in counter-clockwise direction ) */

	/* These conditions uses slope values to determine values of area of points. */
	if (*x1 != 0) s1 = *y1 / *x1;	
	else
	{
		if (*y1 > 0) area1 = 1.99999;
		else if (*y1 == 0) area1 = 0;
		else area1 = 3.99999;
	}
	if (*x2 != 0) s2 = *y2 / *x2;
	else
	{
		if (*y2 > 0) area2 = 1.99999;
		else if (*y2 == 0) area2 = 0;
		else area2 = 3.99999;
	}
	if (*x3 != 0) s3 = *y3 / *x3;
	else
	{
		if (*y3 > 0) area3 = 1.99999;
		else if (*y3 == 0) area3 = 0;
		else area3 = 3.99999;
	}

	if (s1 > 0 && *x1 > 0) area1 = 1;
	else if (s1 > 0 && *x1 < 0) area1 = 3;
	else if (s1 < 0 && *x1 < 0) area1 = 2;
	else if (s1 < 0 && *x1 > 0) area1 = 4;
	else if (s1 == 0 && *x1 < 0) area1 = 2.99999;
	else if (s1 == 0 && *x1 > 0) area1 = 0.99999;

	if (s2 > 0 && *x2 > 0) area2 = 1;
	else if (s2 > 0 && *x2 < 0) area2 = 3;
	else if (s2 < 0 && *x2 > 0) area2 = 2;
	else if (s2 < 0 && *x2 < 0) area2 = 4;
	else if (s2 == 0 && *x2 < 0) area2 = 2.99999;
	else if (s2 == 0 && *x2 > 0) area2 = 0.99999;

	if (s3 > 0 && *x3 > 0) area3 = 1;
	else if (s3 > 0 && *x3 < 0) area3 = 3;
	else if (s3 < 0 && *x3 < 0) area3 = 2;
	else if (s3 < 0 && *x3 > 0) area3 = 4;
	else if (s3 == 0 && *x3 < 0) area3 = 2.99999;
	else if (s3 == 0 && *x3 > 0) area3 = 0.99999;

	/* These conditions below does calculations to determine area values. To do that uses slope values. These values are used different ways in different
	areas. */
	if (area1 == 1 || area1 == 3) area1 = area1 + s1 / 9999;
	else if (area1 == 2 || area1 == 4) area1 = area1 + 1 / (-s1+1);

	if (area2 == 1 || area2 == 3) area2 = area2 + s2 / 9999;
	else if (area2 == 2 || area2 == 4) area2 = area2 + 1 / (-s2+1);

	if (area3 == 1 || area3 == 3) area3 = area3 + s3 / 9999;
	else if (area3 == 2 || area3 == 4) area3 = area3 + 1 / (-s3+1);
	printf("\n%f\n%f\n%f\n", area1, area2, area3);

	/* These conditions below does extra calculations if are values are same.
	If the area values are equal, the one that is closer to the origin point takes priority.
	If the points are the same, gives priority to what is written first and prints a message that the points are the same. */
	if (area1 == area2 && area1 == area3)
	{
		if ((sqrt(*x1 * *x1 + *y1 * *y1) > sqrt(*x2 * *x2 + *y2 * *y2)) && (sqrt(*x1 * *x1 + *y1 * *y1) > sqrt(*x3 * *x3 + *y3 * *y3))) area1 += 0.000001;
		else if ((sqrt(*x1 * *x1 + *y1 * *y1) < sqrt(*x2 * *x2 + *y2 * *y2)) && (sqrt(*x2 * *x2 + *y2 * *y2) > sqrt(*x3 * *x3 + *y3 * *y3))) area2 += 0.000001;
		else if ((sqrt(*x1 * *x1 + *y1 * *y1) < sqrt(*x3 * *x3 + *y3 * *y3)) && (sqrt(*x2 * *x2 + *y2 * *y2) < sqrt(*x3 * *x3 + *y3 * *y3))) area3 += 0.000001;
		else if ((*x1 == *x2) && (*x1 == *x3) && (*y1 == *y2) && (*y1 == *y3))
		{
			printf("\n\n\n!!! All points are same !!!\n\n\n");
			area3 += 0.000002;
			area2 += 0.000001;
		}
	}	
	if (area1 == area2)
	{
		if (sqrt(*x1 * *x1 + *y1 * *y1) > sqrt(*x2 * *x2 + *y2 * *y2)) area1 += 0.000001;
		else if (sqrt(*x1 * *x1 + *y1 * *y1) < sqrt(*x2 * *x2 + *y2 * *y2)) area2 += 0.000001;
		else
		{
			printf("\n\n\n!!! 1. point and 2.point are same !!!\n\n\n");
			area2 += 0.000001;
		}
	}
	if (area1 == area3)
	{
		if (sqrt(*x1 * *x1 + *y1 * *y1) > sqrt(*x3 * *x3 + *y3 * *y3)) area1 += 0.000001;
		else if (sqrt(*x1 * *x1 + *y1 * *y1) < sqrt(*x3 * *x3 + *y3 * *y3)) area3 += 0.000001;
		else
		{
			printf("\n\n\n!!! 1. point and 3.point are same !!!\n\n\n");
			area3 += 0.000001;
		}
	}
	if (area2 == area3)
	{
		if (sqrt(*x2 * *x2 + *y2 * *y2) > sqrt(*x3 * *x3 + *y3 * *y3)) area2 += 0.000001;
		else if (sqrt(*x2 * *x2 + *y2 * *y2) < sqrt(*x3 * *x3 + *y3 * *y3)) area3 += 0.000001;
		else
		{
			printf("\n\n\n!!! 2. point and 3.point are same !!!\n\n\n");
			area3 += 0.000001;
		}
	}

	/* These conditions below sort points in counter-clockwise directions according their area value */
	if (area1 < area2 && area1 < area3)
	{
		if (area3 < area2)
		{
			*x2 = tx3;
			*y2 = ty3;
			*x3 = tx2;
			*y3 = ty2;
		}
	}
	else if (area1 < area2 && area1 > area3)
	{
		*x1 =  tx3;
		*x2 =  tx1;
		*x3 =  tx2;
		*y1 =  ty3;
		*y2 =  ty1;
		*y3 =  ty2;
	}
	else if (area1 > area2 && area1 < area3)
	{
		*x1 =  tx2;
		*x2 =  tx1;
		*y1 =  ty2;
		*y2 =  ty1;
	}
	else if (area1 > area2 && area1 > area3)
	{
		if (area2 < area3)
		{
			*x1 =  tx2;
			*x2 =  tx3;
			*x3 =  tx1;
			*y1 =  ty2;
			*y2 =  ty3;
			*y3 =  ty1;
		}
		else
		{
			*x1 =  tx3;
			*x3 =  tx1;
			*y1 =  ty3;
			*y3 =  ty1;
		}
	}

}


void number_encrypt (unsigned char* number)
{
	char b7='0', b6='0', b5='0', b4='0', b3='0', b2='0', b1='0', b0='0';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	int dec_number;
	dec_number = (int) number;
	printf("Entered number: %d\n", dec_number);

	/* These conditions assigns numbers to the binary digits according to char entered */
	if (dec_number % 2 == 1) *b0 = '1';
	else *b0 = '0';
	dec_number /= 2;
	if (dec_number == 1) *b1 = '1';
	else
	{
		if (dec_number % 2 == 1) *b1 = '1';
		else *b1 = '0';
		dec_number /= 2;
		if (dec_number == 1) *b2 = '1';
		else
		{
			if (dec_number % 2 == 1) *b2 = '1';
			else *b2 = '0';
			dec_number /= 2;
			if (dec_number == 1) *b3 = '1';
			else
			{
				if (dec_number % 2 == 1) *b3 = '1';
				else *b3 = '0';
				dec_number /= 2;
				if (dec_number == 1) *b4 = '1';
				else
				{
					if (dec_number % 2 == 1) *b4 = '1';
					else *b4 = '0';
					dec_number /= 2;
					if (dec_number == 1) *b5 = '1';
					else
					{
						if (dec_number % 2 == 1) *b5 = '1';
						else *b5 = '0';
						dec_number /= 2;
						if (dec_number == 1) *b6 = '1';
						else
						{
							if (dec_number % 2 == 1) *b6 = '1';
							else *b6 = '0';
							dec_number /= 2;
							if (dec_number == 1) *b7 = '1';
						}
					}				
				}
			}
		}
	}
	printf("Bits of entered char -> %c%c%c%c%c%c%c%c\n", *b7, *b6, *b5, *b4, *b3, *b2, *b1, *b0);
}


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	char new_char;
	int char_num;

	printf("Bits of encrypted char -> %c%c%c%c%c%c%c%c\n", b0, b1, b6, b7, b4, b5, b2, b3);

	/* These calculation changes b7 with b2, b6 with b3, b5 with b0, b4 with b1 (7 6 5 4 3 2 1 0 --> 2 3 0 1 6 7 4 5) and also does two circular left shift 
	(2 3 0 1 6 7 4 5 --> 0 1 6 7 4 5 2 3). According to new values creates new binary number and converts it to decimal number */
	char_num = ((int) b3 - 48) + 2 * ((int) b2 - 48) + pow(2, 2) * ((int) b5 - 48) + pow(2, 3) * ((int) b4 - 48) + pow(2, 4) * ((int) b7 - 48) + 
	pow(2, 5) * ((int) b6 - 48) + pow(2, 6) * ((int) b1 - 48) + pow(2, 7) * ((int) b0 - 48);

	*number = char_num;

	printf("\nEncrypted character -> %c\n", char_num); /* New character which obtained */

}
