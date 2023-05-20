#include <stdio.h>
#include <math.h>

void polynomial (int a);

void armstrong_polindrom (int a);

void total_prime_betweeen (int a, int b);

int main ()
{
    int a, b;
    
    printf("Please enter degree of polynomial: ");
    scanf("%d", &a);

    polynomial (a);

    printf("\n\n*****************************************\n\n");

    printf("Please enter an integer to find out if this is a palindrome number and armstrong number: ");
    scanf("%d", &a);

    armstrong_polindrom (a);

    printf("\n\n*****************************************\n\n");

    printf("Please enter two integer to get sum of prime numbers between them\n");
    printf("First integer number :");
    scanf("%d", &a);
    printf("Second integer number :");
    scanf("%d", &b); 

    total_prime_betweeen (a, b);
}

void polynomial (int a)
{
    float coefficient;
    int i;

    for (i = a; i >= 0; i--)
    {
        printf("\nPlease enter %d. coefficient: ", i);
        scanf("%f", &coefficient);

        /* These conditions prints polynomial in expected way */
        if ((coefficient > -0.05) && (coefficient < 0.05));
        else if (i == 0 && coefficient > 0 && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("+%.0f", coefficient);
        else if (i == 0 && coefficient < 0 && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("%.0f", coefficient);
        else if (i == 0 && coefficient > 0) printf("+%.1f", coefficient);
        else if (i == 0 && coefficient < 0) printf("%.1f", coefficient);
        else if (coefficient > 0 && i == a && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("%.0fx^%d ", coefficient, i);
        else if (coefficient < 0 && i == a && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("%.0fx^%d ", coefficient, i);
        else if (coefficient > 0 && i == a) printf("%.1fx^%d ", coefficient, i);
        else if (coefficient > 0 && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("+%.0fx^%d ", coefficient, i); 
        else if (coefficient > 0) printf("+%.1fx^%d ", coefficient, i);    
        else if (coefficient < 0 && (coefficient - (int)coefficient < 0.05 && coefficient - (int)coefficient > -0.05)) printf("%.0fx^%d ", coefficient, i);
        else printf("%.1fx^%d", coefficient, i);
    }
}

void armstrong_polindrom (int a)
{
    int t1, t2, digit, sod = 0, sord = 0,digitnum = 0;

    while (1) /* This loop keep asks for positive value until it gets */
    {
        if (a < 1)
        {
            printf("\n!!!Please enter a positive value!!!\n\n");
            scanf("%d", &a);
            continue;   
        }
        
        break;
    }

    t1 = a;

    while(t1 > 0) /* This loop find the number of digits of entered number */ 
    {
        t1 /= 10;
        digitnum ++;
    }

    t1 = a;
    

    while (t1 > 0) /* This loop finds the digits of the entered number than finds the sum of the cubes of digits and reverse of entered number */
    {
        t2 = t1;
        t1 /= 10;
        digit = t2 - t1 * 10;

        
        sod += pow(digit, digitnum); /* Finds the sum of digits with powers as many as the number of digits. */ 

        sord += digit * pow (10 , --digitnum ); /* Finds reverse of entered number */
    }

    if ((sod == a) && (sord == a)) printf("\nThis number is both Palindrome and Armstrong number.\n");
    else if (sod == a) printf("\nThis number is only Armstrong number.\n");
    else if (sord == a) printf("\nThis number is only Palindrome number.\n");
    else printf("\nThis number does not satisfy any special cases.\n");
}

void total_prime_betweeen (int a, int b)
{
    int i, k, sum = 0, t;

    while (1) /* This loop keep asks for different positive values from each other until it gets */
    {
        if (a < 1 || b < 1) /* This condition checks if the values are positive */
        {
            printf("\n!!!Please enter positive values!!!\n\n");
            printf("First integer number :");
            scanf("%d", &a);
            printf("Second integer number :");
            scanf("%d", &b);
            continue;
        }

        if (a == b) /* This condition checks if the values are different from each other */
        {
            printf("\n!!!Please enter different values from each other!!!\n\n");
            printf("First integer number :");
            scanf("%d", &a);
            printf("Second integer number :");
            scanf("%d", &b);
            continue;
        }

        break;
    }

    /* If a bigger than b this statement changes their values to find correct result */
    if (a > b)
    {
        t = a;
        a = b;
        b = t;
    }

    /* Adds 2 to sum to find correct result if a less than 2 and b bigger than 2 (even numbers are removed because they aren't prime except 2)*/
    if (a < 2 && b > 2) sum = 2;

    for (i = a + 1; i < b; i++) /* This loop finds the sum of prime numbers between a and b */
    {
        if ((i % 2) != 0) /* Eliminates even numbers for efficiency */
        {
            for (k = 2; k < (i + 1) / 2 ; k++) /* Checks the numbers until half of the current number for efficiency */
            {
                if ((i % k) == 0) break; 
            }

            
            if (k == (i + 1) / 2){
                sum += i; /* If k equals (i + 1)/2 then no number could divide the current number without remaining which means number is prime */
            }
        }
    }
    printf("\nSum of the prime number between %d - %d is: %d\n", a, b, sum);
}
