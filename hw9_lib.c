typedef struct
{
    char name[20];
    int age;
    unsigned label;
}customer;

void arrange_sequence_2(customer x[50], int a, int z)
{
    int i, j, k, flag = 0, c_1 = 0, c_2 = 0, c_3 = 0, c_4 = 0, f_0 = 0, f_1 = 0, f_2 = 0, f_3 = 0, f_4 = 0;

    customer y[50];
    
    switch (a) /* Checks if the selected number complies with the rule */
    {
        case 0: for (i = 0; i < 5; i++) /* checks number 0 */
                {
                    if ((x + i)->label != 0 && (x + i)->label != 9)
                    {
                        for (j = 48 - z; j >= i; j--)
                            {
                                /* Turns last valid number into the invalid because it will inserted somewhere beginning in the array */
                                if ((x + j)->label != 9 && flag == 0)
                                {
                                    k = j;
                                    y[k] = x[k]; /* Keeps customer informations in the another customer array to insert it to the actual array later */
                                    (x + k)->label = 9;
                                    flag = 1;
                                }
                                x[j+1] = x[j];
                                
                            }
                            x[i] = y[k]; /* Inserts the customer to the location where it should be */
                            break;
                    } 
                }
                break;
        case 1: for (i = 0; i < 8; i++) /* checks number 1 */
                {
                    if ((x + i)->label == 1) c_1 ++;
                    else if((c_1 >= 0) && (c_1 < 3) && (x + i)->label != 9)
                    {
                        for (j = 0; j < i; j++)
                        {
                            if ((x + j)->label == 0 && f_0 < 5) f_0 ++;
                        }

                        if (f_0 < 5 && (x + j)->label == 0);
                        else
                        {
                            for (j = 48 - z; j >= i; j--)
                            {
                                /* Turns last valid number into the invalid because it will inserted somewhere beginning in the array */
                                if ((x + j)->label != 9 && flag == 0)
                                {
                                    k = j;
                                    y[k] = x[k]; /* Keeps customer informations in the another customer array to insert it to the actual array later */
                                    (x + k)->label = 9;
                                    flag = 1;
                                }
                                x[j+1] = x[j]; /* Inserts the customer to the location where it should be */
                                
                            }
                            x[i] = y[k];
                            break;
                        }
                        f_0 = 0;
                    } 
                }
                break;
        case 2: for (i = 0; i < 11; i++) /* checks number 2 */
                {
                    if ((x + i)->label == 2) c_2 ++;
                    else if((c_2 >= 0) && (c_2 < 2) && (x + i)->label != 9)
                    {
                        for (j = 0; j < i; j++)
                        {
                            if ((x + j)->label == 0 && f_0 < 5) f_0 ++;
                            else if((x + j)->label == 1 && f_1 < 3) f_1 ++;
                        }

                        if (f_0 < 5 && (x + j)->label == 0);
                        else if(f_1 < 3 && (x + j)->label == 1);
                        else
                        {
                            for (j = 48 - z; j >= i; j--)
                            {
                                /* Turns last valid number into the invalid because it will inserted somewhere beginning in the array */
                                if ((x + j)->label != 9 && flag == 0)
                                {
                                    k = j;
                                    y[k] = x[k]; /* Keeps customer informations in the another customer array to insert it to the actual array later */
                                    (x + k)->label = 9;
                                    flag = 1;
                                }
                                x[j+1] = x[j];
                                
                            }
                            x[i] = y[k]; /* Inserts the customer to the location where it should be */
                            break;
                        }
                        f_0 = 0;
                        f_1 = 0;
                    } 
                }
                break;
        case 3: for (i = 0; i < 13; i++) /* checks number 3 */
                {
                    if ((x + i)->label == 3) c_3 ++;
                    else if((c_3 >= 0) && (c_3 < 2) && (x + i)->label != 9)
                    {
                        for (j = 0; j < i; j++)
                        {
                            if ((x + j)->label == 0 && f_0 < 5) f_0 ++;
                            else if((x + j)->label == 1 && f_1 < 3) f_1 ++;
                            else if((x + j)->label == 2 && f_2 < 3) f_2 ++;
                        }

                        if (f_0 < 5 && (x + j)->label == 0);
                        else if(f_1 < 3 && (x + j)->label == 1);
                        else if(f_2 < 3 && (x + j)->label == 2);
                        else
                        {
                            for (j = 48 - z; j >= i; j--)
                            {
                                /* Turns last valid number into the invalid because it will inserted somewhere beginning in the array */
                                if ((x + j)->label != 9 && flag == 0)
                                {
                                    k = j;
                                    y[k] = x[k]; /* Keeps customer informations in the another customer array to insert it to the actual array later */
                                    (x + k)->label = 9;
                                    flag = 1;
                                }
                                x[j+1] = x[j];
                                
                            }
                            x[i] = y[k]; /* Inserts the customer to the location where it should be */
                            break;
                        }
                        f_0 = 0;
                        f_1 = 0;
                        f_2 = 0;
                    } 
                }
                break;
        case 4: for (i = 0; i < 15; i++) /* checks number 4 */
                {
                    if ((x + i)->label == 4) c_4 ++;
                    else if((c_4 >= 0) && (c_4 < 2) && (x + i)->label != 9)
                    {
                        for (j = 0; j < i; j++)
                        {
                            if ((x + j)->label == 0 && f_0 < 5) f_0 ++;
                            else if((x + j)->label == 1 && f_1 < 3) f_1 ++;
                            else if((x + j)->label == 2 && f_2 < 3) f_2 ++;
                            else if((x + j)->label == 3 && f_3 < 2) f_3 ++;
                        }

                        if (f_0 < 5 && (x + j)->label == 0);
                        else if(f_1 < 3 && (x + j)->label == 1);
                        else if(f_2 < 3 && (x + j)->label == 2);
                        else if(f_3 < 2 && (x + j)->label == 3);
                        else
                        {
                            for (j = 48 - z; j >= i; j--)
                            {
                                /* Turns last valid number into the invalid because it will inserted somewhere beginning in the array */
                                if ((x + j)->label != 9 && flag == 0)
                                {
                                    k = j;
                                    y[k] = x[k]; /* Keeps customer informations in the another customer array to insert it to the actual array later */
                                    (x + k)->label = 9;
                                    flag = 1;
                                }
                                x[j+1] = x[j];
                                
                            }
                            x[i] = y[k]; /* Inserts the customer to the location where it should be */
                            break;
                        }
                        f_0 = 0;
                        f_1 = 0;
                        f_2 = 0;
                        f_3 = 0;
                    } 
                }
                break;
    }
    if (flag == 0)
    {
        i = 0;
        while (i < 50)
        {
            if ((x + i + 1)->label == 9) break;
            if((x + i)->label > (x + i +1)->label)
            {
                /* This part of the program has recursive property. If there is no change before in this function and there is a bigger label precedes 
                the smaller one in the array, the program checks the rest of the elements of the array to see if there is need to change in the array */
                arrange_sequence_2(&x[i+1], a, z + i + 1);
                break;
            }
            i++;
        }
    }
}

void arrange_sequence(customer x[50])
{
    int i, j, a = -1, c_1 = 0, c_2 = 0, c_3 = 0, c_4 = 0, f_0 = 0, f_1 = 0, f_2 = 0, f_3 = 0, f_4 = 0, flag = 0, z = 0;

    for (i = 49; i > 0; i--)
    {
        if ((x + i)->label != 9) /* Selects the last valid number in the array (9 is invalid number for this program and it's omitted) */
        {
            a = (x + i)->label;
            break;
        }
    }
    arrange_sequence_2(x, a, z);
}

void sequence(customer x[50])
{
    int i = 0;

    arrange_sequence(x);

    if ((x + i)->label != 9) printf("%u", (x + i)->label); /* Prints the current sequence */
    
    for(i = 1; i < 50; i++)
        {
            if ((x + i)->label == 9) break;
            printf("-%u", (x + i)->label);
        }
    printf("\n");
}

void add_customer(customer x[50])
{
    printf("Please enter the name of the customer :");
    scanf("%s", x->name);
    printf("Please enter the age of the customer :");
    scanf("%d", &x->age);
    printf("Please enter the label of the customer :");
    while(1) /* Asks label number until it gets valid one */
    {
        scanf("%u", &x->label);
        if(x->label >= 0 && x->label <= 4) break;
        else printf("Invalid label please enter again :");

    }
}

void process_customer(customer x[50])
{
    int i;

    if(x->label == 9) /* Prints notification message if there is no person in the line */
    {
        printf("There is no customer in bank system sequence.\n");
    }
    else
    {
        for(i = 0; i < 49; i++) /* Shifts each valid array element one to get rid of first element */
        { 
        x[i]= x[i + 1];
            if ((x + i + 1)->label == 9) break;
        }
    }
}