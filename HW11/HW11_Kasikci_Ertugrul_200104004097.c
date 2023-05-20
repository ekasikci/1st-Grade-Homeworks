#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct m_b
{
    int budget, year;
    char *name;
    struct m_b *next;
}Movie_Budget;

typedef struct m_n
{
    double score;
    char *genre, *name;
    struct m_n *next;
}Movie_Name;

typedef struct
{
    char name[100], genre[10];
    double score;
    int year, budget;
}movie;

void arrange_lists_years(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void arrange_lists_scores(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void arrange_lists_budgets(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void arrange_lists_names(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void arrange_lists_genres(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void arrange_list_as_asked(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size);

void list_data(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size, int choice_1, int choice_1_2, int start, int end, double score_1, double score_2);

void list_genres(Movie_Name *movie_n);

int list_movies_through_years(Movie_Name *movie_n, Movie_Budget *movie_b, int year, int x, int array_size);

int list_movies_through_scores(Movie_Name *movie_n, Movie_Budget *movie_b, double rate, int x, int array_size);

void search_movie(Movie_Name *movie_n, Movie_Budget *movie_b, char *str);

double average_IMDB(Movie_Name *movie_n);

void genre_frequency(Movie_Name *movie_n);

void merge_sort(movie *a, double *b, int x, int z);

void merge(movie *a, double *b, int x, int y, int z);

void print_genre(int x);

int main()
{
    int choice, choice_1, choice_1_2, start_1, end_1, i = 0, j = 0, k = 0, array_size, exit = 0, flag = 0;
    char c, *unknown = (char*)malloc(sizeof (char)*8), *str  = (char*)malloc(sizeof (char)*100), *name1 = (char*)malloc(sizeof (char)*100);
    double s_to_d, score_1, score_2, *x;
    FILE *infile = fopen("Movies.txt","r");
    movie *a;
    Movie_Budget *movie_b = (Movie_Budget*) malloc(sizeof (Movie_Budget)), *iter_b, *current_b, *one_before_b;
    Movie_Name *movie_n = (Movie_Name*) malloc(sizeof (Movie_Name)), *iter_n, *current_n, *one_before_n;

    iter_b = movie_b; /* Uses another variables to keep the head of the lists */
    iter_n = movie_n;

    while(getc(infile) != '\n'); /* Passes the titles */
    while(!feof(infile)) /* Gets informations from the file and assigns to the proper variables of the linked lists */
    {
        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n') str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;
        if (strcmp(str, "unknown") != 0)
            iter_b->budget = (int)strtod(str, &unknown); /* Converts strings to doubles and assigns to the variable */
        else 
            iter_b->budget  = -1;

        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        iter_n->genre =  (char *) malloc(sizeof (char) * (10)); /* Allocates memory for genre fields in the lists */
        strcpy(iter_n->genre, str); /* Gets genres */

        i = 0;

        while(!feof(infile)) /* Gets characters (stops it if encounters with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        iter_n->name = (char *) malloc(sizeof (char) * 100/* (i + 1) */); /* Allocates memory for name fields in the lists */
        i = 0;
        strcpy(iter_n->name , str);
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
        iter_n->score = strtod(str, &unknown); /* Converts strings to doubles and assigns to the variable */      

        while(!feof(infile)) /* Gets characters (stops if it encounter with ',' or '\n'). In the end appends '\0' to get strings */
        {
            c = getc(infile);
            if(c != ',' && c!= '\n')str[i++] = c;
            else break;
        }
        str[i] = '\0';
        i = 0;
        iter_b->year = atoi(str); /* Converts strings to integers and assigns to the variable */

        
        current_n = iter_n;
        iter_n = movie_n;
        current_b = iter_b;
        iter_b = movie_b;
        
        while(iter_n != current_n) /* Updates the datas of the movie if the movie has encountered before */
        {

            if(strcmp(iter_n->name, name1) == 0) /* If the same movie had written before updates datas */
            {
                iter_b->budget = current_b->budget;
                iter_n->genre = current_n->genre;
                iter_n->score = current_n->score;
                iter_b->year = current_b->year;
                flag = 1;
                break;
            }         
            iter_n = iter_n->next;
            iter_b = iter_b->next;
        }
        iter_b = current_b;
        iter_n = current_n;

        /* Passes to next node if the movie hadn't updated otherwise the new movie will be in this node
        because there is no need to keep the movie more than one */
        if (flag == 0 && !feof(infile) && iter_n->score != 0) 
        {
            iter_n->next = (Movie_Name*) malloc(sizeof (Movie_Name));
            iter_b->next = (Movie_Budget*) malloc(sizeof (Movie_Budget));
            iter_n = iter_n->next;
            iter_b = iter_b->next;
            j++;
        }
        
        flag = 0;
        i = 0;
    }
    
    iter_n->next = NULL;
    iter_b->next = NULL;

    iter_n = movie_n;
    
    fclose(infile);

    iter_n = movie_n;
    iter_b = movie_b;

    array_size = j - 1;

    j = 0;

    arrange_list_as_asked(movie_n, movie_b, array_size); /* Sorts array as asked */

    iter_n = movie_n;
    iter_b = movie_b;

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
                
            if(choice_1 == 4)
            {
                while (1)                
                {                        
                    switch (choice_1_2)
                    {
                    case 1: printf("Enter value (rank): ");
                            scanf("%d", &start_1);
                            score_1 = 0;
                            score_2 = 0;
                            break;
                    case 2: printf("Enter start value: ");
                            scanf("%lf", &score_1);
                            printf("Enter end value: ");
                            scanf("%lf", &score_2);
                            start_1 = 0;
                            break;
                    default:printf("TRY AGAIN.\n");                               
                    }

                    /* If the values are not as the expected asks again */
                    if (choice_1_2 == 2 && score_1 >= score_2)
                    {
                        printf("End value must be bigger than start value. Please enter again.\n");
                        choice_1_2 = 2;
                        continue;
                    }
                    else if (choice_1_2 != 1 && choice_1_2 != 2)
                    {
                        printf("!!!Invalid selection. Please select again\n");
                        printf("1. Single Selection\n2. Multiple Selection\n\n");
                        printf("Please select an operation: ");
                        scanf("%d", &choice_1_2);
                        continue;
                    }
                    else if (choice_1_2 == 1 && (start_1 > array_size + 1))
                    {
                        printf("Start value must be less than or equal to %d (number of the movies)\n", array_size + 1);
                        continue;
                    }
                    else break;
                }                        
                list_data(movie_n, movie_b, array_size, choice_1, choice_1_2, start_1, end_1, score_1, score_2);
            }
            else
            {
                while (1)                
                {                        
                    switch (choice_1_2)
                    {
                    case 1: printf("Enter value (rank): ");
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
                        printf("!!!Invalid selection. Please select again\n");
                        printf("1. Single Selection\n2. Multiple Selection\n\n");
                        printf("Please select an operation: ");
                        scanf("%d", &choice_1_2);
                        continue;
                    }
                    else if (choice_1_2 == 1 && (start_1 > array_size + 1))
                    {
                        printf("Start value must be less than or equal to %d (number of the movies)\n", array_size + 1);
                        continue;
                    }
                    else if (start_1 < 1)
                    {
                        printf("Values must be greater than 0\n");
                        continue;
                    }
                    else break;
                    }
                    list_data(movie_n, movie_b, array_size, choice_1, choice_1_2, start_1, end_1, 0, 0);
                }
                break;

        case 2: 
            list_genres(movie_n);
            break;

        case 3: 
            while(k == 0)
            {
                printf("Enter a year: ");
                scanf("%d", &i);
                printf("Until (0) or Since (1) %d: ", i);
                scanf("%d", &j);
                if (j != 0 && j != 1)
                {
                    printf("Invalid input!!!\n");
                    continue;
                }
                k = list_movies_through_years(movie_n, movie_b, i, j, array_size);
            }         
            k = 0;
            break;

        case 4: 
            while(k == 0)
            {
                printf("Enter a score: ");
                scanf("%lf", &score_1);
                printf("Less (0) or Greater (1) than %.1f: ", score_1);
                scanf("%d", &j);
                if (j != 0 && j != 1)
                    {
                        printf("Invalid input!!!\n");
                        continue;
                    }
                k = list_movies_through_scores(movie_n, movie_b, score_1, j, array_size);
            }
            k = 0;
            break;

        case 5: 
            printf("Please enter the name of the movie: ");
            scanf(" %[^\n]%*c", str);
            search_movie(movie_n, movie_b, str);
            break;

        case 6: 
            printf("\nAverage IMDB scores of the movies: %f\n\n", average_IMDB(movie_n));
            break;

        case 7: 
            genre_frequency(movie_n);
            break;

        case 8: 
            exit++;
            printf("Program Terminated\n");
            break;

        default: 
            printf("TRY AGAIN.\n");
        }
    }
}

void list_data(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size, int choice_1, int choice_1_2, int start, int end, double score_1, double score_2)
{
    Movie_Name *iter_n, *iter_n_2;
    Movie_Budget *iter_b, *iter_b_2;
    movie *a = (movie*) malloc(sizeof (movie) * array_size);
    int e, i = 0, j = 0, t, flag = 0;
    e = end;
    double x[array_size + 1];

    iter_n = movie_n;
    iter_b = movie_b;

    iter_n_2 = movie_n;
    iter_b_2 = movie_b;

     while (i <= array_size)
    {
        x[i] = 0;
        i++;
    }
    i = 0;

    switch (choice_1)
    {
    case 1: /* Sorts lists according to budgets and prints them according to input value */
        switch (choice_1_2) 
        {
        case 1: arrange_lists_budgets(movie_n, movie_b, array_size);

            while (iter_n->next != NULL) 
            {
                if (i == start - 1)
                {
                    if(iter_b->budget == -1) printf("\nUnknown        ");
                    else printf("\n%-15d", iter_b->budget);                          
                    printf("%-12s  %-50s  %-15.1f  %-8d\n\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                    break;
                }
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                i++;
            }
            break;

        case 2: arrange_lists_budgets(movie_n, movie_b, array_size);
    
            while (iter_n->next != NULL)
            {
                if(iter_b->budget < start || iter_b->budget > end)
                {
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;  
                    continue;
                }
                if(iter_b->budget == -1) printf("\nUnknown        ");
                else printf("\n%-15d", iter_b->budget);                          
                printf("%-12s  %-50s  %-15.1f  %-8d\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                printf("\n");
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                flag++;                            
            }
            if (flag == 0)
                printf("\nThere is no movie in this specified area\n");
            printf("\n");
            break;
        }
        break;
    case 2: /* Sorts lists according to genres and prints them according to input value */
        switch (choice_1_2)
        {
        case 1: arrange_lists_genres(movie_n, movie_b, array_size);
            while (iter_n->next != NULL) 
            {
                if (i == start - 1)
                {
                    if(iter_b->budget == -1) printf("\nUnknown        ");
                    else printf("\n%-15d", iter_b->budget);                          
                    printf("%-12s  %-50s  %-15.1f  %-8d\n\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                    break;
                }
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                i++;
            }
            break;
        case 2: arrange_lists_genres(movie_n, movie_b, array_size);
            while (iter_n->next != NULL && i < start - 1) 
            {
                iter_n = iter_n->next;
                i++;
            } 
            while (start <= e)
            {
                printf("%d.\n", start);
                if(iter_b->budget == -1) printf("\nUnknown        ");
                else printf("\n%-15d", iter_b->budget);                          
                printf("%-12s  %-50s  %-15.1f  %-8d\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                printf("\n");
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                start++;                               
                flag++;                            
            }
            if (flag == 0)
                printf("\nThere is no movie in this specified area\n");
            break;
        }
        break;
    case 3: /* Sorts lists according to names and prints them according to input value */
        switch (choice_1_2)
        {
        case 1: arrange_lists_names(movie_n, movie_b, array_size);

            while (iter_n->next != NULL) 
            {
                if (i == start - 1)
                {
                    if(iter_b->budget == -1) printf("\nUnknown        ");
                    else printf("\n%-15d", iter_b->budget);                          
                    printf("%-12s  %-50s  %-15.1f  %-8d\n\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                    break;
                }
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                i++;
            }
            break;
        case 2: arrange_lists_names(movie_n, movie_b, array_size);

            while (iter_n->next != NULL && i < start - 1) 
            {
                iter_n = iter_n->next;
                i++;
            } 
            while (start <= e)
            {
                if(iter_b->budget == -1) printf("\nUnknown        ");
                else printf("\n%-15d", iter_b->budget);                          
                printf("%-12s  %-50s  %-15.1f  %-8d\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                start++;                               
                flag++;                            
            }
            printf("\n");
            if (flag == 0)
                printf("\nThere is no movie in this specified area\n");
            break;
        }
        break;
    case 4: /* Sorts lists according to scores and prints them according to input value */
        switch(choice_1_2)
        {
        case 1: arrange_lists_scores(movie_n, movie_b, array_size);
            while (iter_n->next != NULL) 
            {
                if (i == start - 1)
                {
                    if(iter_b->budget == -1) printf("\nUnknown        ");
                    else printf("\n%-15d", iter_b->budget);                          
                    printf("%-12s  %-50s  %-15.1f  %-8d\n\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);;
                    break;
                }
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                i++;
            }
            break;                              
            
        case 2: arrange_lists_scores(movie_n, movie_b, array_size);
            while (iter_n->next != NULL)
            {
                if(iter_n->score < score_1 || iter_n->score > score_2)
                {
                    iter_n = iter_n->next;
                    iter_b = iter_b->next; 
                    continue;
                }
                if(iter_b->budget == -1) printf("\nUnknown        ");
                else printf("\n%-15d", iter_b->budget);                          
                printf("%-12s  %-50s  %-15.1f  %-8d\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                iter_n = iter_n->next;
                iter_b = iter_b->next;                        
                flag++;                            
            }
            printf("\n");
            if (flag == 0)
                printf("\nThere is no movie in this specified area\n");
            break;
        }
        break;
    case 5: /* Sorts lists according to years and prints them according to input value */
        switch (choice_1_2)
        {
        case 1: arrange_lists_years(movie_n, movie_b, array_size);
            while (iter_n->next != NULL) 
            {
                if (i == start - 1)
                {
                    if(iter_b->budget == -1) printf("\nUnknown        ");
                    else printf("\n%-15d", iter_b->budget);                          
                    printf("%-12s  %-50s  %-15.1f  %-8d\n\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);
                    break;
                }
                iter_n = iter_n->next;
                iter_b = iter_b->next;
                i++;
            }
            break;
        case 2: arrange_lists_years(movie_n, movie_b, array_size);
            while (iter_n->next != NULL)
            {
                if(iter_b->year < start || iter_b->year > end)
                {
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;  
                    continue;
                }
                if(iter_b->budget == -1) printf("\nUnknown        ");
                else printf("\n%-15d", iter_b->budget);                          
                printf("%-12s  %-50s  %-15.1f  %-8d\n",iter_n->genre, iter_n->name, iter_n->score, iter_b->year);               
                iter_n = iter_n->next;
                iter_b = iter_b->next;                              
                flag++;                            
            }
            printf("\n");
            if (flag == 0)
                printf("\nThere is no movie in this specified area\n");
            break;
        }
        break;
    }
}

void list_genres(Movie_Name *movie_n)
{
    Movie_Name *iter_n;
    int i = 0, j = 0, k = 1, z = 0, flag = 0;
    char str[20][20];

    iter_n = movie_n;

    /* Compares genres of the movies and if the genres has not included the list includes the genres to the list. */
    while (iter_n->next != NULL)
    {
        while (j < i)
        {
            if(strcmp(str[j], iter_n->genre) == 0)
            {
                flag = 1;
                break;
            }
            j++;
        }

        if (flag == 0)
        {
            strcpy(str[j], iter_n->genre);           
            i++;
        }
        iter_n = iter_n->next;
        j = 0;
        flag = 0;     
    }
    j = 0;

    while(j < i) /* Prints all genres */
    {
        printf("\n%s", str[j]);
        j++;
    }
    printf("\n\n");
}

int list_movies_through_years(Movie_Name *movie_n, Movie_Budget *movie_b, int year, int x, int array_size)
{
    Movie_Name *iter_n;
    Movie_Budget *iter_b;
    double years[array_size + 1];
    int i = 0, flag = 0;

    /* Sorts lists according to years (it is not necessary but it is more good that the names of the movies to be sorted ) */
    arrange_lists_years(movie_n, movie_b, array_size);
    
    iter_n = movie_n;
    iter_b = movie_b;
    
    printf("\n");
    switch (x)
    {
        case 0: while (iter_n->next != NULL) /* Prints the movie names which it's made year is euqal or smaller than the entered year */
                {
                    if(iter_b->year <= year)
                    {
                        printf("%s\n", iter_n->name);
                        flag = 1;
                    }
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie until the entered year */
                {
                    printf("There is no movie before %d, please enter again\n\n", year);
                    return 0;
                }
                return 1;
        case 1: while (iter_n->next != NULL) /* Prints the movie names which it's made year is bigger than the entered year  */
                {
                    if(iter_b->year >= year)
                    {
                        printf("%s\n", iter_n->name);
                        flag = 1;
                    }
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;
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

int list_movies_through_scores(Movie_Name *movie_n, Movie_Budget *movie_b, double rate, int x, int array_size)
{
    Movie_Name *iter_n;
    Movie_Budget *iter_b;
    double scores[array_size + 1];
    int i = 0, flag = 0;

    /* Sorts lists according to scores (it is not necessary but it is more good that the names of the movies to be sorted ) */
    arrange_lists_scores(movie_n, movie_b, array_size);

    iter_n = movie_n;
    iter_b = movie_b;
    
    printf("\n");
    switch (x)
    {
        case 0: while (iter_n->next != NULL)  /* Prints the movie names which it's score is equal or smaller than the entered score */
                {
                    if(iter_n->score <= rate)
                    {
                        printf("%s\n", iter_n->name);
                        flag = 1;
                    }
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;
                }
                printf("\n");
                if (flag == 0) /* Prints this information if there is no encountered movie equal or smaller than the entered score */
                {
                    printf("There is no movies with a score below %.1f, please enter again\n\n", rate);
                    return 0;
                }
                return 1;
        case 1: while (iter_n->next != NULL)  /* Prints the movie names which it's score is bigger than the entered score */
                {
                    if(iter_n->score >= rate)
                    {
                        printf("%s\n", iter_n->name);
                        flag = 1;
                    }
                    iter_n = iter_n->next;
                    iter_b = iter_b->next;
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

void search_movie(Movie_Name *movie_n, Movie_Budget *movie_b, char *str)
{
    Movie_Name *iter_n, *target_n;
    Movie_Budget *iter_b, *target_b;
    int flag = 0, x, str_size = 0, j = 0;
    char c;

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Checks if there is a movie with the name entered */
    {
        if (strcmp(str, iter_n->name) == 0)
        {
            flag++;
            target_n = iter_n;
            target_b = iter_b;
            break;
        }
        iter_n = iter_n->next;
        iter_b = iter_b->next;
    }

    iter_n = movie_n;
    iter_b = movie_b;

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
        while(iter_n->next != NULL && flag == 0)
        {
            while(j < str_size)
            {
                /* This letter checking process is not case sensitive */
                if(str[j] == iter_n->name[j] || str[j] + 32 == iter_n->name[j] || str[j] -32 == iter_n->name[j]) j++;
                else break;

                if (str[j] == '\0')
                {
                    flag++;
                    target_n = iter_n;
                    target_b = iter_b;
                    break;   
                }
            }
            j = 0;
            iter_n = iter_n->next;
            iter_b = iter_b->next;
        }
    }

    if (flag == 0) printf("\nThere is no movie called %s\n\n", str); /* If there is no encountered movie prints an information about this */
    else if (flag == 1) /* If there is an encountered movie prints all information about that movie */
    {
        if(target_b->budget == -1) printf("\nBudget: Unknown\n");
        else printf("\nBudget: %d\n", target_b->budget);

        printf("Genre : %s\n", target_n->genre);
        printf("Name  : %s\n", target_n->name);
        printf("Score : %.1f\n", target_n->score);
        printf("Year  : %d\n\n", target_b->year);
    }
    else printf("Wtf");
}

double average_IMDB(Movie_Name *movie_n)
{
    Movie_Name *iter;
    double sum = 0;
    int i = 0;

    iter = movie_n;
    
    while (iter->next != NULL) /* Sums all scores of the movies and divides this to the number of the movies to get average score */
    {

        sum += iter->score;
        i ++;

        iter = iter->next;
    } 
    return sum / i;
}

void genre_frequency(Movie_Name *movie_n)
{
    Movie_Name *iter_n;
    int i = 0, j = 0, k = 1, z = 0, flag = 0, *str_c;
    char str[20][20];

    str_c = (int*) calloc(20, sizeof(int));

    iter_n = movie_n;

    /* Compares genres of the movies and if the genres has not included the list includes the genres to the list. */
    while (iter_n->next != NULL)
    {
        while (j < i)
        {
            if(strcmp(str[j], iter_n->genre) == 0)
            {
                flag = 1;
                break;
            }
            j++;
        }

        if (flag == 0)
        {
            strcpy(str[j], iter_n->genre);           
            i++;
        }
        iter_n = iter_n->next;
        j = 0;
        flag = 0;
    }

    j = 0;
    i = 0;

    iter_n = movie_n;
    
    while(iter_n->next != NULL) /* Keeps all genres counters in an array and checks all movies. Increases by one the genre values when encountered that genre */
    {
        while(i < 20)
        {
            if (strcmp(str[i], iter_n->genre) == 0)
            {
                str_c[i] ++;
                break;
            }
            i++;          
        }
        i = 0;
        iter_n = iter_n->next;      
    }

    /* Prints all genres with the number of there are how many movies with this genre */
    i = 0;
    while(i < 20)
    {
        if (str_c[i] == 0)
        {
            i++;
            continue;
        } 
        printf("%-20s %d\n",str[i], str_c[i]);
        i++;
        
    }
    printf("\n");
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

/* Sorts lists according the years (ascending order) */
void arrange_lists_years(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n;
    Movie_Budget *iter_b;
    movie *a;
    double *x;
    int j = 0;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    iter_n = movie_n;
    iter_b = movie_b;
    
    while (iter_n->next != NULL) /* Passes datas to the array of movies */
    {  
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
    j = 0;

    while(j <= array_size) /* Passes datas to the other array */
    {
        x[j] = a[j].year;
        j++;
    }
    j = 0;

    merge_sort(a, x, 0, array_size); /* Merges data in ascending order */

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes merged datas to the lists */
    {   
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
}

/* Sorts lists according the scores (ascending order) */
void arrange_lists_scores(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n;
    Movie_Budget *iter_b;
    movie *a;
    double *x;
    int j = 0;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    iter_n = movie_n;
    iter_b = movie_b;
    
    while (iter_n->next != NULL) /* Passes datas to the array of movies */
    {  
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
    j = 0;

    while(j <= array_size) /* Passes datas to the other array */
    {
        x[j] = a[j].score;
        j++;
    }
    j = 0;

    merge_sort(a, x, 0, array_size); /* Merges data in ascending order */

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes merged datas to the lists */
    {   
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
}

/* Sorts lists according the budgets (ascending order) */
void arrange_lists_budgets(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n;
    Movie_Budget *iter_b;
    movie *a;
    double *x;
    int j = 0;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    iter_n = movie_n;
    iter_b = movie_b;
    
    while (iter_n->next != NULL) /* Passes datas to the array of movies */
    {  
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++;
    }
    j = 0;

    while(j <= array_size) /* Passes datas to the other array */
    {
        x[j] = a[j].budget;
        j++;
    }
    
    j = 0;

    merge_sort(a, x, 0, array_size); /* Merges data in ascending order */

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes merged datas to the lists */
    {   
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
}

void arrange_lists_names(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n, *iter_n_2;
    Movie_Budget *iter_b, *iter_b_2;
    movie *a;
    double *x;
    int i = 0, j = 0, t;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    iter_n = movie_n;
    iter_b = movie_b;

    iter_n_2 = movie_n;
    iter_b_2 = movie_b;
    
    while (iter_n->next != NULL) /* Passes datas to the array of movies */
    {  
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
    j = 0;

    iter_n = movie_n;
    iter_b = movie_b;

    /* Compares every movie names with rest of the movies names. If is precede takes -1 if is equal takes 0 and if is comes later takes 1.
    Sums this values, keeps them in the array*/
    while (iter_n->next != NULL)
    {
        while (iter_n_2->next != NULL)
        {
            t = strcmp(iter_n->name, iter_n_2->name);
            if (t < 0) t = -1;
            else t = 1;
            x[i] += t;
            iter_n_2 = iter_n_2->next;
            iter_b_2 = iter_b_2->next;
        }
        iter_n_2 = movie_n;
        iter_b_2 = movie_b;
        i++;
        iter_n = iter_n->next;
        iter_b = iter_b->next;
    }
    i = 0;

    iter_n = movie_n;
    iter_b = movie_b;

    merge_sort(a, x, 0, array_size); /* Merges data in descending order */

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes merged datas to the lists */
    {   
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
}

void arrange_lists_genres(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n, *iter_n_2;
    Movie_Budget *iter_b, *iter_b_2;
    movie *a;
    double *x;
    int i = 0, j = 0, t;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    iter_n = movie_n;
    iter_b = movie_b;

    iter_n_2 = movie_n;
    iter_b_2 = movie_b;
    
    while (iter_n->next != NULL) /* Passes datas to the array of movies */
    {  
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre); 
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
    j = 0;

    iter_n = movie_n;
    iter_b = movie_b;

    /* Compares every movie genre with rest of the movies names. If is precede takes -1 if is equal takes 0 and if is comes later takes 1.
    Sums this values, keeps them in the array*/
    while (iter_n->next != NULL)
    {
        while (iter_n_2->next != NULL)
        {
            t = strcmp(iter_n->genre, iter_n_2->genre);
            if (t < 0) t = -1;
            else t = 1;
            x[i] += t;
            iter_n_2 = iter_n_2->next;
            iter_b_2 = iter_b_2->next;
        }
        iter_n_2 = movie_n;
        iter_b_2 = movie_b;
        i++;
        iter_n = iter_n->next;
        iter_b = iter_b->next;
    }
    i = 0;

    iter_n = movie_n;
    iter_b = movie_b;

    merge_sort(a, x, 0, array_size); /* Merges data in descending order */

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes merged datas to the lists */
    {   
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }
}

void arrange_list_as_asked(Movie_Name *movie_n, Movie_Budget *movie_b, int array_size)
{
    Movie_Name *iter_n, *holder_n;
    Movie_Budget *iter_b, *holder_b;
    movie *a;
    double *x;
    int i = 0, j = 0, current_year;

    a = (movie*) calloc(array_size + 1, sizeof(movie));
    x = (double*) calloc(array_size + 1, sizeof(double));

    arrange_lists_years(movie_n, movie_b, array_size);

    iter_n = movie_n;
    iter_b = movie_b;
    
    while (iter_n->next != NULL) /* Passes merged datas to the array */
    {   
        a[j].budget = iter_b->budget;
        a[j].year = iter_b->year;
        a[j].score = iter_n->score;
        strcpy(a[j].name, iter_n->name);
        strcpy(a[j].genre, iter_n->genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
        j++; 
    }

    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* Passes datas from the array to the list reversed order so years of the datas will be in descending order as asked */
    {   
        j--; 
        iter_b->budget = a[j].budget;
        iter_b->year = a[j].year;
        iter_n->score = a[j].score;
        strcpy(iter_n->name, a[j].name);
        strcpy(iter_n->genre, a[j].genre);
        iter_n = iter_n->next;
        iter_b = iter_b->next; 
    }

    j = 0;
    iter_n = movie_n;
    iter_b = movie_b;

    while (iter_n->next != NULL) /* For the same years sorts the lists according their budget values in descending order */
    {   
        current_year = iter_b->year;

        holder_n = iter_n;
        holder_b = iter_b;

        while (iter_b->year == current_year && iter_n->next != NULL) /* Passes datas to the array */
        {
            a[j].budget = iter_b->budget;
            a[j].year = iter_b->year;
            a[j].score = iter_n->score;
            strcpy(a[j].name, iter_n->name);
            strcpy(a[j].genre, iter_n->genre);
            iter_n = iter_n->next;
            iter_b = iter_b->next; 
            j++;     
        }

        iter_n = holder_n;
        iter_b = holder_b;

        while(i < j) /* Passes budget values to the other array*/
        {
            x[i] = a[i].budget;
            i++;
        }
        i = 0;

        merge_sort(a, x, 0, j); /* Merges array according to their budget values in ascending order */
        
        while (j > 0) /* Passes the datas from array to the list reversely so it will be sort descending order */
        {
            j--;
            iter_b->budget = a[j].budget;
            iter_b->year = a[j].year;
            iter_n->score = a[j].score;
            strcpy(iter_n->name, a[j].name);
            strcpy(iter_n->genre, a[j].genre);
            iter_n = iter_n->next;
            iter_b = iter_b->next;
        }
    }  
}