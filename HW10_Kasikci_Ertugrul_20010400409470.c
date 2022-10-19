#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    double budget;
    int genre;
    char *name ;
    double score;
    int year;
}movie;

void list_data(movie *a, int array_size, int choice_1, int choice_1_2, int start, int end);

void list_genres();

int list_movies_through_years(movie *a, int year, int x, int array_size);

int list_movies_through_scores(movie *a, double rate, int x, int array_size);

void search_movie(movie *a, char *str, int array_size);

double average_IMDB(movie *a, int array_size);

void genre_frequency(movie *a, int array_size);

void merge_sort(movie *a, double *b, int x, int z);

void merge(movie *a, double *b, int x, int y, int z);

void print_genre(int x);

int main()
{
    int choice, choice_1, choice_1_2, start_1, end_1, i = 0, j = 0, k = 0, array_size, exit = 0;
    char c, *unknown = (char*)malloc(sizeof (char)*8), *str  = (char*)malloc(sizeof (char)*100), *name1 = (char*)malloc(sizeof (char)*100);
    double s_to_d, score;
    FILE *infile = fopen("Movies.txt","r");
    movie *a;

    while(!feof(infile))
    {
        if (getc(infile) == '\n') j++;
    }

    array_size = j - 1;

    a = (movie *)calloc(array_size, sizeof (movie)); /* Allocates as many space to the array as numbers of the movies */
                                                                                                                
    rewind(infile);

    while(getc(infile) != '\n'); /* Passes the titles */

    j = 0;

    while(!feof(infile)) /* Gets informations from the file, converts them if needed and assigns to the proper variable of the struct array */
    {
        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n') str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;
        if (strcmp(str, "unknown") != 0) (a + j)->budget = strtod(str, &unknown); /* Converts strings to doubles and assigns to the variable */
        else (a + j) -> budget = -1;

        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;

        /* Gives numers to the variable according to the genres of the movies */
        if (strcmp(str, "action") == 0) (a + j) -> genre = 1; 
        else if (strcmp(str, "adventure") == 0) (a + j) -> genre = 2;
        else if (strcmp(str, "animation") == 0) (a + j) -> genre = 3;
        else if (strcmp(str, "biography") == 0) (a + j) -> genre = 4;
        else if (strcmp(str, "comedy") == 0) (a + j) -> genre = 5;
        else if (strcmp(str, "crime") == 0) (a + j) -> genre = 6;
        else if (strcmp(str, "drama") == 0) (a + j) -> genre = 7;         
        else if (strcmp(str, "horror") == 0) (a + j) -> genre = 8;      
        else if (strcmp(str, "musical") == 0) (a + j) -> genre = 9;
        else if (strcmp(str, "mystery") == 0) (a + j) -> genre = 10;
        else if (strcmp(str, "romance") == 0) (a + j) -> genre = 11;
        else if (strcmp(str, "sci-fi") == 0) (a + j) -> genre = 12;
        else if (strcmp(str, "thriller") == 0) (a + j) -> genre = 13;
        else (a + j) -> genre = -1;

        while(!feof(infile)) /* Gets characters (stops it if encounters with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        (a + j)->name = (char *) malloc(sizeof (char) * (i + 1));
        i = 0;
        strcpy((a + j)->name , str);
        strcpy(name1 , str);
        
        i = 0;

        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;
        (a + j) -> score = strtod(str, &unknown); /* Converts strings to doubles and assigns to the variable */      

        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;
        (a + j) -> year = atoi(str); /* Converts strings to integers and assigns to the variable */

        while(i < j) /* Updates the datas of the movie if the movie has encountered before */
        {
            if(strcmp((a + i) -> name, name1) == 0)
            {
                (a + i) -> budget = (a + j) -> budget;
                (a + i) -> genre = (a + j) -> genre;
                (a + i) -> score = (a + j) -> score;
                (a + i) -> year = (a + j) -> year;
                j--; /* Decreases j (array order) by one because the current movie has encountered before
                therefore the datas updated and there is no need to keep the movie more than one (new movie will be overwritten this movie) */
            }         
            i++;
        }
        if((a + i) -> score == 0) j--;
        i = 0;
        j++;
    }

    fclose(infile);

    array_size = j-1;

    while(exit == 0)
    {
        printf("1. List of the Sorted Data\n");
        printf("2. List of the Sorted Genres\n");
        printf("3. List of the Movie Through the Years\n");
        printf("4. List of the Movie Through the Scores\n");
        printf("5. All Informations of a Single Movie\n");
        printf("6. Average of the IMDB Scores\n");
        printf("7. Frequence of the Genres\n");
        printf("8. Exit\n\n");
        printf("Please select an operation: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1: printf("1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n\n");

                    while(1)
                    {
                        printf("Please select an operation: ");
                        scanf("%d", &choice_1);
                        if(choice_1 < 1 || choice_1 > 5) printf("TRY AGAIN.\n");
                        else break;
                    }
                    printf("1. Single Selection\n2. Multiple Selection\n\n");
                    printf("Please select an operation: ");
                    scanf("%d", &choice_1_2);
                    
                    while (1)                
                    {                        
                        switch (choice_1_2)
                        {
                            case 1: printf("Enter value: ");
                                    scanf("%d", &start_1);
                                    break;
                            case 2: printf("Enter start value: ");
                                    scanf("%d", &start_1);
                                    printf("Enter end value: ");
                                    scanf("%d", &end_1);
                                    break;
                            default:printf("TRY AGAIN.\n");
                                    
                        }

                        /* If the values are not as the expected asks again */
                        if (choice_1_2 == 2 && start_1 >= end_1)
                        {
                            printf("End value must be bigger than start value. Please enter again.\n");
                            choice_1_2 = 2;
                            continue;
                        }
                        else if (choice_1_2 != 1 && choice_1_2 != 2)
                        {
                            printf("1. Single Selection\n2. Multiple Selection\n\n");
                            printf("Please select an operation: ");
                            scanf("%d", &choice_1_2);
                            continue;
                        }
                        else if (start_1 > array_size + 1)
                        {
                            printf("Start value must be less than or equal to %d (number of the movies)\n", array_size + 1);
                            continue;
                        }
                        else if (start_1 < 1 )
                        {
                            printf("Values must be greater than 0\n");
                            continue;
                        }
                        else break;
                    }

                    list_data(a, array_size, choice_1, choice_1_2, start_1, end_1);

                    break;

            case 2: list_genres();
                    break;

            case 3: while(k == 0)
                    {
                        printf("Enter a year: ");
                        scanf("%d", &i);
                        printf("Until (0) or Since (1) %d: ", i);
                        scanf("%d", &j);
                        k = list_movies_through_years(a, i, j, array_size);
                    }         
                    k = 0;
                    break;

            case 4: while(k == 0)
                    {
                        printf("Enter a score: ");
                        scanf("%lf", &score);
                        printf("Less (0) or Greater (1) than %.1f: ", score);
                        scanf("%d", &j);
                        k = list_movies_through_scores(a, score, j, array_size);
                    }
                    k = 0;
                    break;

            case 5: printf("Please enter the name of the movie: ");
                    scanf(" %[^\n]%*c", str);
                    search_movie(a, str, array_size);
                    break;

            case 6: printf("\nAverage IMDB scores of the movies: %f\n\n", average_IMDB(a, array_size));
                    break;

            case 7: genre_frequency(a, array_size);
                    break;

            case 8: exit++;
                    printf("Program Terminated\n");
                    break;

            default: printf("TRY AGAIN.\n");
        }
    }
}

void list_data(movie *a, int array_size, int choice_1, int choice_1_2, int start, int end)
{
    int e, i = 0, j = 0, t;
    e = end;
    double x[array_size + 1];
     while (i <= array_size)
    {
        x[i] = 0;
        i++;
    }
    i = 0;
    switch (choice_1)
    {
        case 1: /* Takes the budget values of the movies, keeps them in the array and sorts this array with 
                merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
                switch (choice_1_2) 
                {
                    case 1: while (i <= array_size) 
                            {
                                x[i] = (a + i)->budget;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            if((a + start - 1)->budget == -1) printf("Unknown        ");
                            else printf("\n%-15.1f", (a + start - 1)->budget);
                            print_genre((a + start - 1)->genre);                            
                            printf("  %-40s  %-15.1f  %-8d\n\n", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                            break;

                    case 2: while (i <= array_size)
                            {
                                x[i] = (a + i)->budget;
                                i++;
                            }
                            merge_sort(a, x, 0, i);
                            while (start <= e)
                            {
                                printf("%d.\n", start);
                                if((a + start - 1)->budget == -1) printf("Unknown        ");
                                else printf("\n%-15.1f", (a + start - 1)->budget);
                                print_genre((a + start - 1)->genre);                            
                                printf("  %-40s  %-12.1f  %-8d", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                                start++;
                                printf("\n\n");
                            }
                            printf("\n");
                            break;
                }
                break;

        case 2: /* Takes the genre values of the movies, keeps them in the array and sorts this array with 
                merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
                switch (choice_1_2)
                {
                    case 1: while (i <= array_size)
                            {
                                x[i] = (a + i)->genre;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            if((a + start - 1)->budget == -1) printf("Unknown        ");
                            else printf("\n%-15.1f  ", (a + start - 1)->budget);
                            print_genre((a + start - 1)->genre);                            
                            printf("  %-40s  %-12.1f  %-8d\n\n", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                            break;

                    case 2: while (i <= array_size)
                            {
                                x[i] = (a + i)->genre;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            while (start <= e)
                            {
                                printf("%d.\n", start);
                                if((a + start - 1)->budget == -1) printf("Unknown        ");
                                else printf("\n%-15.1f  ", (a + start - 1)->budget);
                                print_genre((a + start - 1)->genre);                            
                                printf("  %-40s  %-12.1f  %-8d", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                                start++;
                                printf("\n\n");
                            }
                            break;
                }
                break;

        case 3: /* Compares every movie name with rest of the movies names. If is precede takes -1 if is equal takes 0 and if is comes later takes 1.
                Sums this values, keeps them in the array and sorts this array with merge sort and while doing this sorting, sorts movie array at the 
                same time with the same indexes */
                switch (choice_1_2)
                {
                    case 1: for (i = 0; i <= array_size; i++)
                            {
                                for (j = 0; j <= array_size; j++)
                                {
                                    t = strcmp((a + i)->name, (a + j)->name);
                                    if (t < 0) t = -1;
                                    else t = 1;
                                    x[i] += t;
                                    j++;
                                }
                            }
                            i = 0;
                            merge_sort(a, x, 0, array_size);
                            if((a + start - 1)->budget == -1) printf("Unknown        ");
                            else printf("\n%-15.1f  ", (a + start - 1)->budget);
                            print_genre((a + start - 1)->genre);                            
                            printf("  %-40s  %-12.1f  %-8d\n\n", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                            break;

                    case 2: for (i = 0; i <= array_size; i++)
                            {
                                for (j = 0; j <= array_size; j++)
                                {
                                    t = strcmp((a + i)->name, (a + j)->name);
                                    if (t < 0) t = -1;
                                    else t = 1;
                                    x[i] += t;
                                    j++;
                                }
                            }
                            i = 0;
                            merge_sort(a, x, 0, array_size);
                            while (start <= e)
                            {
                                printf("%d.\n", start);
                                if((a + start - 1)->budget == -1) printf("Unknown        ");
                                else printf("\n%-15.1f", (a + start - 1)->budget);
                                print_genre((a + start - 1)->genre);                            
                                printf("  %-40s  %-12.1f  %-8d", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                                start++;
                                printf("\n\n");
                            }
                            break;
                }
                break;
                
        case 4: /* Takes the score values of the movies, keeps them in the array and sorts this array with 
                merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
                switch (choice_1_2)
                {
                    case 1: while (i <= array_size)
                            {
                                x[i] = (a + i)->score;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            if((a + start - 1)->budget == -1) printf("Unknown        ");
                            else printf("\n%-15.1f", (a + start - 1)->budget);
                            print_genre((a + start - 1)->genre);                            
                            printf("  %-40s  %-12.1f  %-8d\n\n", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                            break;

                    case 2: while (i <= array_size)
                            {
                                x[i] = (a + i)->score;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            while (start <= e)
                            {
                                printf("%d.\n", start);
                                if((a + start - 1)->budget == -1) printf("Unknown        ");
                                else printf("\n%-15.1f", (a + start - 1)->budget);
                                print_genre((a + start - 1)->genre);                            
                                printf("  %-40s  %-12.1f  %-8d", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                                start++;
                                printf("\n\n");
                            }
                            break;
                }
                break;

        case 5: /* Takes the year values of the movies, keeps them in the array and sorts this array with 
                merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
                switch (choice_1_2)
                {
                    case 1: while (i <= array_size)
                            {
                                x[i] = (a + i)->year;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            if((a + start - 1)->budget == -1) printf("Unknown        ");
                            else printf("\n%-15.1f  ", (a + start - 1)->budget);
                            print_genre((a + start - 1)->genre);                            
                            printf("  %-40s  %-12.1f  %-8d\n\n", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                            break;

                    case 2: while (i <= array_size)
                            {
                                x[i] = (a + i)->budget;
                                i++;
                            }
                            merge_sort(a, x, 0, array_size);
                            while (start <= e)
                            {
                                printf("%d.\n", start);
                                if((a + start - 1)->budget == -1) printf("Unknown        ");
                                else printf("\n%-15.1f  ", (a + start - 1)->budget);
                                print_genre((a + start - 1)->genre);                            
                                printf("  %-40s  %-12.1f  %-8d", (a + start - 1)->name, (a + start - 1)->score, (a + start - 1)->year);
                                start++;
                                printf("\n\n");
                            }
                            break;
                }
                break;
    }
}

void list_genres()
{
    printf("\nAction\n");
    printf("Adventure\n");
    printf("Animation\n");
    printf("Biograpy\n");
    printf("Comedy\n");
    printf("Crime\n");
    printf("Drama\n");
    printf("Horror\n");
    printf("Musical\n");
    printf("Mystery\n");
    printf("Romance\n");
    printf("Sci-fi\n");
    printf("Thriller\n\n\n");
}

int list_movies_through_years(movie *a, int year, int x, int array_size)
{
    double years[array_size + 1];
    int i = 0, flag = 0;

    while (i <= array_size) /* Keeps the year values of the movies in the array */
    {
        years[i] = (a + i)->year;
        i++;
    }
    i = 0;

    /* Sorts this array with merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
    merge_sort(a, years, 0, array_size); 
    
    printf("\n");
    switch (x)
    {
        case 0: while(i <= array_size) /* Prints the movie names which it's made year is euqal or smaller than the entered year */
                {
                    if((a + i)->year <= year)
                    {
                        printf("%s\n", (a + i)->name);
                        flag = 1;
                    }
                    i++;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie until the entered year */
                {
                    printf("There is no movie before %d, please enter again\n\n", year);
                    return 0;
                }
                return 1;
        case 1: while(i <= array_size) /* Prints the movie names which it's made year is bigger than the entered year  */
                {
                    if((a + i)->year >= year)
                    {
                        printf("%s\n", (a + i)->name);
                        flag = 1;
                    }
                    i++;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie since the entered year */
                {
                    printf("There is no movie after %d, please enter again\n\n", year);
                    return 0;
                }
                return 1;
    }
}

int list_movies_through_scores(movie *a, double rate, int x, int array_size)
{
    double scores[array_size + 1];
    int i = 0, flag = 0;

    while (i <= array_size) /* Keeps the score values of the movies in the array */
    {
        scores[i] = (a + i)->score;
        i++;
    }
    i = 0;
    
    /* Sorts this array with merge sort while doing this sorting, sorts movie array at the same time with the same indexes */
    merge_sort(a, scores, 0, array_size);

    printf("\n");
    switch (x)
    {
        case 0: while(i <= array_size) /* Prints the movie names which it's score is equal or smaller than the entered score */
                {
                    if((a + i)->score <= rate)
                    {
                        printf("%s\n", (a + i)->name);
                        flag = 1;
                    }
                    i++;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie equal or smaller than the entered score */
                {
                    printf("There is no movies with a score below %.1f, please enter again\n\n", rate);
                    return 0;
                }
                return 1;
        case 1: while(i <= array_size) /* Prints the movie names which it's score is bigger than the entered score */
                {
                    if((a + i)->score >= rate)
                    {
                        printf("%s\n", (a + i)->name);
                        flag = 1;
                    }
                    i++;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie bigger than the entered score */
                {
                    printf("There is no movies with a score over %.1f, please enter again\n\n", rate);
                    return 0;
                }          
                return 1;
    }  
}

void search_movie(movie *a, char *str, int array_size)
{
    int i = 0, flag = 0, x, str_size = 0, j = 0;
    char c;

    while (i < array_size) /* Checks if there is a movie with the name entered */
    {
        if (strcmp(str, (a +i)->name) == 0)
        {
            flag++;
            x = i;
            break;
        }
        i++;
    }
    i = 0;

    /* If there is no encountered movie with the entered name checks again without case sensitivity 
    (and for this time the encountered name can have number or extra letters)*/
    if (flag == 0) 
    {
        while (c != '\0') /* Determines the size of the movie name */ 
        {
            c = str[str_size];
            str_size++;
        }

        /* Checks each letter of the entered movie name with the other movie names. If the same name is encountered keeps this information in the flag variable */
        while(i < array_size && flag == 0)
        {
            while(j < str_size)
            {
                /* This letter checking process is not case sensitive */
                if(str[j] == (a + i)->name[j] || str[j] + 32 == (a + i)->name[j] || str[j] -32 == (a + i)->name[j]) j++;
                else break;

                if (str[j] == '\0')
                {
                    flag++;
                    x = i;
                    break;   
                }
            }
            j = 0;
            i ++;
        }
    }

    if (flag == 0) printf("\nThere is no movie called %s\n\n", str); /* If there is no encountered movie prints an information about this */
    else if (flag == 1) /* If there is an encountered movie prints all information about that movie */
    {
        if((a + x)->budget == -1) printf("\nBudget: Unknown\n");
        else printf("\nBudget: %.1f\n", (a + x)->budget);

        switch ((a + x)->genre)
        {
            case 1: printf("Genre : Action\n");
                    break;
            case 2: printf("Genre : Adventure\n");
                    break;
            case 3: printf("Genre : Animation\n");
                    break;
            case 4: printf("Genre : Biograpy\n");
                    break;
            case 5: printf("Genre : Comedy\n");
                    break;
            case 6: printf("Genre : Crime\n");
                    break;
            case 7: printf("Genre : Drama\n");
                    break;
            case 8: printf("Genre : Horror\n");
                    break;
            case 9: printf("Genre : Musical\n");
                    break;
            case 10: printf("Genre : Mystery\n");
                    break;
            case 11: printf("Genre : Romance\n");
                    break;
            case 12: printf("Genre : Sci-fi\n");
                    break;
            case 13: printf("Genre : Thriller\n");
                    break;
            case -1: printf("Genre : Unknown\n");
                    break;
        }
        printf("Name  : %s\n", (a + x)->name);
        printf("Score : %.1f\n", (a + x)->score);
        printf("Year  : %d\n\n", (a + x)->year);
    }
    else printf("Wtf");
}

double average_IMDB(movie *a, int array_size)
{
    double sum = 0;
    int i = 0, j = 0;
    
    while (i <= array_size) /* Sums all scores of the movies and divides this to the number of the movies to get average score */
    {
        if ((a + i)->score == 0)
        {
            i ++;
            continue;
        } 
        sum += (a + i++)->score;
        j ++;
    } 
    return sum / j;
}

void genre_frequency(movie *a, int array_size)
{
    char str[10];
    int *x = (int*) calloc(14, sizeof (int)), i = 0, genre;

    while(i < array_size) /* Keeps all genres counters in an array and checks all movies. Increases by one the genre values when encountered this genre */
    {
        genre = (a + i)->genre;
        i ++;

        switch (genre)
        {
            case 1: x[0] ++;
                    break;
            case 2: x[1] ++;
                    break;
            case 3: x[2] ++;
                    break;
            case 4: x[3] ++;
                    break;
            case 5: x[4] ++;
                    break;
            case 6: x[5] ++;
                    break;
            case 7: x[6] ++;
                    break;
            case 8: x[7] ++;
                    break;
            case 9: x[8] ++;
                    break;
            case 10: x[9] ++;
                    break;
            case 11: x[10] ++;
                    break;
            case 12: x[11] ++;
                    break;
            case 13: x[12] ++;
                    break;
            case -1: x[13] ++;
                    break;
        }      
    }

    /* Prints all genres with the number of there are how many movies with this genre */
    printf("\naction          %d\n", x[0]);
    printf("adventure       %d\n", x[1]);
    printf("animation       %d\n", x[2]);
    printf("biograpy        %d\n", x[3]);
    printf("comedy          %d\n", x[4]);
    printf("crime           %d\n", x[5]);
    printf("drama           %d\n", x[6]);
    printf("horror          %d\n", x[7]);
    printf("musical         %d\n", x[8]);
    printf("mystery         %d\n", x[9]);
    printf("romance         %d\n", x[10]);
    printf("sci-fi          %d\n", x[11]);
    printf("thriller        %d\n", x[12]);
    printf("unknown         %d\n\n", x[13]);
    
}

void merge_sort(movie *a, double *b, int x, int z) /* This function does merge short */
{
    int y;

    /* This condition has recursive feature. Bisects the array repeatedly until the 
    array length decreases to the one and send the to the another function to sort them */
    if (x < z)
    {
        y = (x + z) / 2;
        merge_sort(a, b, x, y);
        merge_sort(a, b, y+1, z);
        merge(a, b, x, y, z);    
    }
}

void merge(movie *a, double *b, int x, int y, int z) /* This function sorts the elements of the arrays */
{
    int i = 0, j = 0, d_1 = y - x , d_2 = z - y;

    movie c[z - x + 1]; /* When sorting the array sorts the movie array at the same time with same index */
    double d[z - x + 1];

    /* This part of code takes two array fragment (these arrays are will be sorted due to the recursive feature of the function). 
    Checks each element of the array, first places the smaller one to the another array than places the bigger one and so on. Like this 
    aprroach merges two array by sorting them. When doing this, applies this implementation also for the movie array by using the index values */
    while (1)
    {      
        while (i <= d_1)
        {
            
            if (b[x + i] <= b[y + 1 + j] || j == d_2)
            {
                d[i + j] = b[x + i];
                c[i + j] = a[x + i];
                i ++;           
            }
            else break;
        }
        
        while (j < d_2)
        {

            if (b[x + i] >= b[y + 1 + j] || i == d_1 + 1)
            {
                d[i + j] = b[y + 1 + j];
                c[i + j] = a[y + 1 + j];
                j ++;               
            } 
            else break;
        }
        if (i == d_1 + 1 && j == d_2) break;          
    }

    i = 0;

    while (i < z - x + 1)
    {
        b[x + i] = d[i];
        a[x + i] = c[i];
        i++;
    }
    i = 0; 
}

void print_genre(int x) /* This function prints the genres of the movies according the values of the genres of the movies */
{
    switch(x)
    {
        case -1:printf("Unknown    ");
                break;
        case 1: printf("Action     ");
                break;
        case 2: printf("Adventure  ");
                break;
        case 3: printf("Animation  ");
                break;
        case 4: printf("Biograpy   ");
                break;
        case 5: printf("Comedy     ");
                break;
        case 6: printf("Crime      ");
                break;
        case 7: printf("Drama      ");
                break;
        case 8: printf("Horror     ");
                break;
        case 9: printf("Musical    ");
                break;
        case 10: printf("Mystery   ");
                break;
        case 11: printf("Romance   ");
                break;
        case 12: printf("Sci-fi    ");
                break;
        case 13: printf("Thriller  ");
                break;
    }
}