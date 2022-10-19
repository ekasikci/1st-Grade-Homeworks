#include <stdio.h>
#include "hw9_lib.c"

int main()
{
    int cus_n = 0, i, t = 0, choice = 9;
    customer x[50];

    for(i = 0; i < 50; i++)
    {
        (x + i)->label = 9;
    }

    printf("Customer Sequence For a Banking System\n\n");

    while (cus_n < 50  && t == 0)
    {
        printf("\nCurrent Sequence: ");
        sequence(x); /* Prints the current sequence */
        printf("1-Add customer\n");
        printf("2-Process customer\n");
        printf("0-Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 0: printf("\nTerminated\n"); /* Terminates program */
                    t = 1;
                    break;
            case 1: add_customer(&x[cus_n]); /* Ask information about customer and adds it to the sequence */
                    cus_n ++;
                    break;
            case 2: process_customer(x); /* Processes one customer who at the beginning of the sequence */
                    if (cus_n > 0) cus_n --;         
                    break;
            default: printf("Invalid input please enter again\n");
        }
        if (cus_n == 50) /* When reaches limit of the sequence, program asks that either be processed one customer or be ended the program */
        {
            printf("Reached the limit of the sequence. To continue please process customer or exit the program\n");
            while (1)
            {              
                printf("2-Process customer\n");
                printf("0-Exit\n");
                scanf("%d", &choice);
                switch (choice)
                {
                    case 0: printf("\nTerminated\n"); /* Terminates program */
                            t = 1;
                            break;
                    case 2: process_customer(x); /* Processes one customer who at the beginning of the sequence */
                            if (cus_n > 0) cus_n --;         
                            break;
                    default: printf("Invalid input please enter again\n");
                }
                if (choice == 0 || choice == 2) break; /* If user does not terminates program or process customer the program asks again */
            }
            
        }
    }
}

