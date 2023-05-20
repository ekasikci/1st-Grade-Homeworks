/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials ()
{
	double a3, a2, a1, a0, b3, b2, b1, b0, va3, va2, va1, va0, vb3, vb2, vb1, vb0;
	int ae3, ae2, ae1, ae0, be3, be2, be1, be0;
	char op;

	printf("Please enter two polynomials (they must be entered as this syntax (3, a), (2, b), (1, c), (0, d) (letters are coefficients number are exponents).)");
	printf("1. polynomial: ");
	scanf(" (%d, %lf), (%d, %lf), (%d, %lf), (%d, %lf)", &ae3, &va3, &ae2, &va2, &ae1, &va1, &ae0, &va0);
	printf("2. polynomial: ");
	scanf(" (%d, %lf), (%d, %lf), (%d, %lf), (%d, %lf)", &be3, &vb3, &be2, &vb2, &be1, &vb1, &be0, &vb0);
	printf("Please enter a operator (allowed operators are addition, subtraction, and multiplication)");
	scanf(" %c", &op);

	/* All these statements assigns the values in correct variables according their exponent values */
	if (ae3 == 3) a3 = va3;
	else if (ae3 == 2) a2 = va3;
	else if (ae3 == 1) a1 = va3;
	else a0 = va3;

	if (ae2 == 3) a3 = va2;
	else if (ae2 == 2) a2 = va2;
	else if (ae2 == 1) a1 = va2;
	else a0 = va2;

	if (ae1 == 3) a3 = va1;
	else if (ae1 == 2) a2 = va1;
	else if (ae1 == 1) a1 = va1;
	else  a0 = va1;

	if (ae0 == 3) a3 = va0;
	else if (ae0 == 2) a2 = va0;
	else if (ae0 == 1) a1 = va0;
	else a0 = va0;

	if (be3 == 3) b3 = vb3;
	else if (be3 == 2) b2 = vb3;
	else if (be3 == 1) b1 = vb3;
	else b0 = vb3;

	if (be2 == 3) b3 = vb2;
	else if (be2 == 2) b2 = vb2;
	else if (be2 == 1) b1 = vb2;
	else b0 = vb2;

	if (be1 == 3) b3 = vb1;
	else if (be1 == 2) b2 = vb1;
	else if (be1 == 1) b1 = vb1;
	else b0 = vb1;

	if (be0 == 3) b3 = vb0;
	else if (be0 == 2) b2 = vb0;
	else if (be0 == 1) b1 = vb0;
	else b0 = vb0;


	operate_polynomials  (&a3, &a2, &a1, &a0, &b3, &b2, &b1, &b0, op); /* Entered values into the function were ordered according their exponent values */

	if (op == '+' || op == '-' || op == '*') /* Checks if the entered operator is true */
	{
	/* Output of the function */
	printf("\nCoefficients:\n\nx^6: %0.1f\nx^5: %0.1f\nx^4: %0.1f\nx^3: %0.1f\nx^2: %0.1f\nx^1: %0.1f\nx^0: %0.1f\n\n", a3, a2, a1, a0, b3, b2, b1);
	}
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number='t';
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
