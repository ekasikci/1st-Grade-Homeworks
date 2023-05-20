#include<stdio.h>

void calculate_fibonacci_sequence(int a);

void decide_perfect_harmonic_number(int a);

void difference_max_min (double a, double b, double c, double d, double e);

void bmi_calculation (double heigth, double weight);

int main()
{
    double a, b, c, d, e;
    int x;
    char tchar, tchar2;

    printf("Please enter term(s) number (to terminate enter '*')\n");

    /* This loop takes numbers and returns fibonacci terms as many as that number */
    while (1)
    {
        scanf("%d", &x);
        scanf("%c", &tchar); /* In this line entered value for the x assigns also the tchar variable so we can check the tchar if it is equals '*' character */

        if (tchar == '*') /* This statement checks whether the input value is a '*' character. If so, the loop terminates */
        {
            printf("\nTerminated\n\n");
            break;
        }
        else if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, input is asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }  
        else if (x < 1) /* This statement checks whether the input value is a positive number. If not, input is asked again */
        {
            printf("\n!!!Please enter positive term(s) number!!!\n\n");
            continue;
        }
        else /* This statement calls the function because all requirements are satisfied */
        {
            calculate_fibonacci_sequence (x);
            printf("\nPlease enter term(s) number (to terminate enter '*')\n");
        }
          
    }

    printf("\n******************************************************************************\n\n");
    printf("Please enter input number to find out is it perfect number and harmonic divisor number (to terminate enter '*')\n"); 

    /* This loop takes a number and finds whether the number is perfect and harmonic number. */
    while (1)
    {
        scanf("%d", &x);
        scanf("%c", &tchar); /* In this line entered value for the x assigns also the tchar variable so we can check the tchar if it is equals '*' character */

        if (tchar == '*')  /* This statement checks whether the input value is a '*' character. If so, the loop terminates */
        {
            printf("\nTerminated\n\n");
            break;
        }
        else if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, input is asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }  
        else if (x < 1) /* This statement checks whether the input value is a positive number. If not, input is asked again */
        {
            printf("\n!!!Please enter positive term(s) number!!!\n\n");
            continue;
        }
        else /* This statement calls the function because all requirements are satisfied */
        {
            decide_perfect_harmonic_number (x);
            printf("\nPlease enter input number (to terminate enter '*')\n");
        }
          
    }

    printf("\n******************************************************************************\n\n");

    /* This loop call sort the entered 5 numbers in ascending order */
    while(1)
    {
        printf("Please enter 5 numbers\n");
        scanf("%lf", &a);
        scanf("%c", &tchar);
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, inputs are asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }
        scanf("%lf", &b);
        scanf("%c", &tchar);
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, inputs are asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }
        scanf("%lf", &c);
        scanf("%c", &tchar);
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, inputs are asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }
        scanf("%lf", &d);
        scanf("%c", &tchar);
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, inputs are asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }
        scanf("%lf", &e);
        scanf("%c", &tchar);
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126))) /* This statement checks whether the input value is a numeric character. If not, inputs are asked again */
        {
            printf("\n!!!Please enter numeric values(s)!!!\n");
            continue;
        }

        difference_max_min (a, b, c, d, e);
        break;
    }  

    printf("\n******************************************************************************\n\n");
    
    /* This loop takes takes your weight and height and prints your BMI (body mass index) and tells how fat you are */
    while (1)
    {
        printf("Please enter weight(kg)\n");
        scanf("%lf", &a);
        scanf("%c", &tchar);
        printf("Please enter height(m)(kg)\n");
        scanf("%lf", &b);
        scanf("%c", &tchar2);

        /* This statement checks whether the input values are numeric characters. If not, inputs are asked again */
        if ((tchar >= 33 && tchar <= 47) || ((tchar >= 58 && tchar <= 126)) || (tchar2 >= 33 && tchar2 <= 47) || ((tchar2 >= 58 && tchar2 <= 126)))
        {
            printf("\n!!!Please enter numeric values(s)!!!\n\n");
            continue;
        }  
        else if (a < 0 && b < 0) printf("\n!!!Invalid weight and invalid height, please enter positive value!!!\n\n");
        else if (a < 0) printf("\n!!!Invalid weight, please enter positive value!!!\n\n");
        else if (b < 0) printf("\n!!!Invalid height, please enter positive value!!!\n\n");
        else /* This statement calls the function because all requirements are satisfied */
        {
            bmi_calculation (b, a); /* This function call takes your weight and height and prints BMI (how fat you are) */
            break;
        }  
    }
    
    return 0;
}

void calculate_fibonacci_sequence(int a)
{
    int b = 1, s = 0, t;
    printf("\nFibonacci Sequence\n");

    /* This loop prints the fibonacci serial terms as many as the input value entered */
    for (a;a>0;a--)
    {
        printf("%d\n",b);
        t = b;
        b = s + b;
        s = t;
    }
}

void decide_perfect_harmonic_number(int a)
{
    int i, sum = 0, k = 1, check;
    double hmean = 0, hresult;
    
    /* This loop finds the divisors of the entered value and sum them */
    printf("\nNatural number divisiors :");
    for (i = 1; i < a; ++i)
    {
        if (a % i == 0)
        {
            k++;
            printf("%d ", i);
            sum = sum + i;
            hmean = hmean + 1.0/i;
        }
    }
    
    /* This line is for adding the last divisor (itself) of the entered value to the harmonic mean */
    hmean = hmean + 1.0/a;

    /* This statement determines whether the entered value is perfect number or not */
    if (sum == a) printf("\nIs perfect number ?: Yes\n");
    else printf("\nIs perfect number ?: No\n");

    /* This statements determines whether the entered value is harmonic divisior number or not */
    hresult = k / hmean;
    check = hresult;

    if (check == hresult) printf("Is harmonic divisior number ?: Yes\n");
    else printf("Is harmonic divisior number ?: No\n");
}

void difference_max_min (double a, double b, double c, double d, double e)
{
    double t;
    
    /* This loop sorts the inputs smaller to bigger */
    while (1)
    {
        if (a > b)
        {
            t = a;
            a = b;
            b = t;
        }
        if (b > c)
        {
            t = b;
            b = c;
            c = t;
        }
        if (c > d)
        {
            t = c;
            c = d;
            d = t;
        }
        if (d > e)
        {
            t = d;
            d = e;
            e = t;
        }
        if (a <= b && b <= c && c <= d && d <= e) break;
    }

    printf("The numbers in ascending order: %g, %g, %g, %g, %g\n", a, b, c, d, e);
    printf ("Maximum number is: %f\n",e);
    printf ("Minimum number is: %f\n", a);
    printf ("Difference between maximum and minimum is: %f\n", e - a);
}

void bmi_calculation (double heigth, double weight)
{
    double bmi;

    /* This part of of code calculates the BMI*/
    bmi = weight / (heigth * heigth);

    if (bmi < 16.0) printf("Your category: Severely Underweight\n");
    else if (bmi >= 16.0 && bmi <= 18.4) printf("Your category: Underweight\n");
    else if (bmi >= 18.5 && bmi <= 24.9) printf("Your category: Normal\n");
    else if (bmi >= 25.0 && bmi <= 29.9) printf("Your category: Owerweight\n");
    else printf("Your category: Obese\n");
}
