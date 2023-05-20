/* 
- This code asks the user antonym or synonym questions. 
- The user can add new words with antonym or synonym equivalent or can add new antonym or synonym equivalent for the words which already exist.
- The code asks questions according to possibility values of the words. Sums all possibilities and gets a randomly number between this sum and zero.
  Asks the word corresponds this number (multiplies the possibility numbers by 10 to increase the precision of the possibilities, so values like 0.2 have 
  meaning).
- Shows the datas each word after the user answer that word (true false number, number of how many times asked and possibility value). 
- Keeps these datas in binary files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node_a
{
    char word[50], antonym[10][50];
    struct node_a *next;
}list_a;

typedef struct node_s
{
    char word[50], synonym[10][50];
    struct node_s *next;
}list_s;

typedef struct
{
    int true_n, false_n, asked_t;
    double possibility;
}word_data;


typedef struct node_p
{
    word_data x;
    struct node_p *next;
}list_p;

int main()
{
    FILE *antoynm_f, *synonym_f, *users_in, *users_out, *current_user_f_i, *current_user_f_o;
    list_a *head_a, *iter_a;
    list_s *head_s, *iter_s;
    list_p *current_head_a, *current_iter_a, *current_head_s, *current_iter_s, *before_iter_a, *before_iter_s;
    char word[50], word_2[50], c, user_names[10][50];
    int i, j, k, r, choice, choice_2, exit = 0, exit_2 = 0, possibility_sum = 0, flag = 0, flag_2 = 0;

    antoynm_f = fopen("antonyms.txt","r+");
    synonym_f = fopen("synonyms.txt","r+");

    head_a = (list_a*)malloc(sizeof (list_a));
    head_s = (list_s*)malloc(sizeof (list_s));
    current_head_a = (list_p*) malloc(sizeof(list_p));
    current_head_s = (list_p*) malloc(sizeof(list_p));

    iter_a = head_a;
    iter_s = head_s;

    current_iter_a = current_head_a;
    current_iter_s = current_head_s;

    while (!feof(antoynm_f)) /* Takes words and their antonyms and keeps them in a linked list */
    {
        i = 0;
        j = 0;     

        c = fgetc(antoynm_f);
        if (feof(antoynm_f))
            break; 
        while(c != '<') /* Gets word and keep it in the list */
        {
            word[i++] = c;
            c = fgetc(antoynm_f);
        }

        word[i-1] = '\0';
        strcpy(iter_a->word, word);
        i = 0;

        c = fgetc(antoynm_f);
        while (c != ' ') /* Moves in the list until reaches the antonyms */
            c = fgetc(antoynm_f);

        while(c != '\n' && !feof(antoynm_f)) /* Takes antonyms of the words */
        {
            i = 0;
            c = fgetc(antoynm_f); 
            while(c != ',' && c != '\n' && !feof(antoynm_f)) 
            {
                word[i++] = c;
                c = fgetc(antoynm_f);           
            }
            word[i] = '\0';
            strcpy(iter_a->antonym[j], word);
            j++;

        }
        
        iter_a->next = (list_a*)malloc(sizeof(list_a));
        iter_a = iter_a->next;

        current_iter_a->next = (list_p*) malloc(sizeof(list_p));
        current_iter_a = current_iter_a->next;
        
        if (feof(antoynm_f))
            break;
    }
    iter_a->next = NULL;
    current_iter_a->next = NULL;

    while (!feof(synonym_f)) /* Takes words and their synonyms and keeps them in a linked list */
    {
        i = 0;
        j = 0;

        c = fgetc(synonym_f);
        if (feof(synonym_f))
            break; 
        while(c != '=') /* Gets word and keep it in the list */
        {
            word[i++] = c;
            c = fgetc(synonym_f);
        }

        word[i-1] = '\0';
        strcpy(iter_s->word, word);
        i = 0;

        c = fgetc(synonym_f);

        while(c != '\n' && !feof(synonym_f)) /* Takes synonyms of the words */
        {
            i = 0;
            c = fgetc(synonym_f); 
            while(c != ',' && c != '\n' && !feof(synonym_f)) 
            {
                word[i++] = c;
                c = fgetc(synonym_f);           
            }
            word[i] = '\0';
            strcpy(iter_s->synonym[j], word);
            j++;

        }
        
        iter_s->next = (list_s*)malloc(sizeof(list_s));
        iter_s = iter_s->next;

        current_iter_s->next = (list_p*) malloc(sizeof(list_p));
        current_iter_s = current_iter_s->next;
        
        if (feof(synonym_f))
            break;
    }
    iter_s->next = NULL;
    current_iter_s->next = NULL;

    iter_a = head_a;
    iter_s = head_s;

    current_iter_a = current_head_a;
    current_iter_s = current_head_s;
    
    while(exit == 0) /* This part of the code is the main menu of the program. Program stays in this part until the user wants to exit. */
    {
        printf("\nPlease choose a selection\n");
        printf("1. Start program\n\n");
        printf("2. Add a new word\n\n");
        printf("0. Exit\n");

        scanf("%d", &choice);

        iter_a = head_a;
        iter_s = head_s;

        current_iter_a = current_head_a;
        current_iter_s = current_head_s;

        switch (choice)
        {
        case 0:
            exit = 1; /* Terminates the loop of the main menu, therefore ends the program */
            printf("\n\nProgram terminated\n");

            break;

        case 1:
            printf("Select an user or create a new user (1: Select 2: Create): ");
            scanf("%d", &choice);         

            switch (choice)
            {
            case 1:
                users_out = fopen("users.txt","r");
                printf("Selectable users:\n\n");               

                j = 0;
                while(1)
                {
                    i = 0;
                    while(1) /* Takes saved users from the file and prints them */
                    {    
                        c = fgetc(users_out);
                        if (c == '\n' || feof(users_out))
                            break;
                        user_names[j][i++] = c;
                    }
                    if (feof(users_out))
                        break;
                    user_names[j][i] = '\0';
                    printf("%d. %s\n", j+1, user_names[j]);
                    j++;                 
                }

                fclose(users_out);

                if (j == 0) /* Prints a warning if there is no user saved */
                {    
                    printf("\nThere is no user can be selected\n\n");
                    flag = 1;
                    break;
                }

                while (1)
                {
                    printf("\nPick an user: ");
                    scanf("%d", &choice);
                    if (choice < 1 || choice > j)
                        printf("\nInvalid input. Please enter again\n\n");
                    else  
                        break;
                }
                strcat (user_names[choice-1], ".worddat"); /* Creates binary file which have same name with the user name (excep the .worddat suffix) */

                current_user_f_o = fopen(user_names[choice-1],"rb");

                /* Passes datas in the file to the lists */
                while(current_iter_a->next != NULL)
                {
                    fread(&(current_iter_a->x), sizeof(word_data), 1, current_user_f_o);
                    before_iter_a = current_iter_a;
                    current_iter_a = current_iter_a->next;
                }
                current_iter_a = before_iter_a;

                while(current_iter_s->next != NULL)
                {
                    fread(&(current_iter_s->x), sizeof(word_data), 1, current_user_f_o);
                    before_iter_s = current_iter_s;
                    current_iter_s = current_iter_s->next;
                }
                current_iter_s = before_iter_s;

                current_iter_a = current_head_a;
                current_iter_s = current_head_s;

                fclose(current_user_f_o);

                current_user_f_i = fopen(user_names[choice-1],"wb");    
                break;

            case 2:
                printf("Enter an user name: ");
                scanf(" %[^\n]%*c", word);
                users_out = fopen("users.txt","r");

                while(1) /* Checks if there is already a user with entered name */
                {
                    i = 0;
                    while(1)
                    {    
                        c = fgetc(users_out);
                        if (c == '\n' || feof(users_out))
                            break;
                        word_2[i++] = c;
                    }
                    if (feof(users_out))
                        break;
                    word_2[i] = '\0';
                    if (strcmp(word, word_2) == 0) /* Prints warning and back to the main menu if finds an user with entered name */
                    {
                        printf("\nThis user already exist\n\n");
                        flag = 1;
                        break;
                    }
                }
                fclose(users_out); /* Sets flag to 1 to return main menu */
                if (flag == 1)
                    break;

                users_in = fopen("users.txt","a");
                fprintf(users_in, "%s\n", word);
                fclose(users_in);

                strcat(word, ".worddat"); /* Creates binary file which have same name with the user name (excep the .worddat suffix) */

                current_user_f_i = fopen(word,"wb");

                current_iter_a = current_head_a;
                current_iter_s = current_head_s;

                /* Arranges data values because a new user have been created */
                while (iter_a->next != NULL)
                {
                    current_iter_a->x.false_n = 0;
                    current_iter_a->x.true_n = 0;
                    current_iter_a->x.asked_t = 0;
                    current_iter_a->x.possibility = 1;
                    current_iter_a = current_iter_a->next;
                    
                    iter_a = iter_a->next;
                }
                current_iter_a->next = NULL;

                while (iter_s->next != NULL)
                {
                    current_iter_s->x.false_n = 0;
                    current_iter_s->x.true_n = 0;
                    current_iter_s->x.asked_t = 0;
                    current_iter_s->x.possibility = 1;
                    current_iter_s = current_iter_s->next;

                    iter_s = iter_s->next;
                }
                current_iter_s->next = NULL;
                
                iter_a = head_a;
                iter_s = head_s;
          
                break;

            default:
                printf("\nInvalid input. Please enter again\n\n"); /* Prints warning if the user types invalid input */
                flag = 1;
                break;
            }

            if (flag == 1) /* Quits if any user had not be selected */
            {    
                flag = 0;
                break; 
            }  
            
            while(1)
            {
                current_iter_a = current_head_a;
                current_iter_s = current_head_s;

                iter_a = head_a;
                iter_s = head_s;

                srand(time(NULL)); /* Gives random numbers on every call */

                r = rand() % 2; /* Sets r 0 or 1. According to result asks antonym or synonym question. */

                if (r == 0)
                {
                    /* To asks antonyms of the words according to their possibility values */
                    while (iter_a->next != NULL)
                    {
                        possibility_sum += (int)current_iter_a->x.possibility * 10;
                        iter_a = iter_a->next;          
                    }
                    r = rand() % possibility_sum;

                    iter_a = head_a;
                    current_iter_a = current_head_a;

                    i = 0;

                    while (iter_a->next != NULL)
                    {
                        j = 0;
                        while (j < ((int)current_iter_a->x.possibility * 10))
                        {
                            i++;
                            j++;
                            if (i == r)
                                break;                          
                        }
                        if (i == r)
                            break;
                        iter_a = iter_a->next;
                        current_iter_a = current_iter_a->next;
                    }
                    j = 0;

                    printf("\nWrite an antonym of %s: ", iter_a->word);
                    scanf(" %[^\n]%*c", word); /* The user enters an antonym */

                    while (strcmp(iter_a->antonym[j], "\0") != 0) /* Checks if the entered word match any of the antonyms of the word */
                    {
                        if (strcmp(word, iter_a->antonym[j++]) == 0) /* Sets flag 1 if checks */
                            flag = 1;
                    }

                    if (flag == 1)
                    {
                        printf("\n\nCorrect answer\n");

                        current_iter_a->x.asked_t ++; /* Increases one the variable which determines how many times the word asked */
                        current_iter_a->x.true_n ++;  /* Increases one the variable which determines how many times the word answered true */
                        current_iter_a->x.possibility *= 1.0/((current_iter_a->x.true_n)+1); /* Changes the possibility of the word to ask */

                        /* Prints the informations about the word */
                        printf("\nFor the current word:  True -> %d   False -> %d   How many times asked -> %d   Possibility of being asked -> %.1f\n\n"
                        , current_iter_a->x.true_n, current_iter_a->x.false_n, current_iter_a->x.asked_t, current_iter_a->x.possibility);

                        while (iter_s->next != NULL) /* Searches if the word which asked has synonym */
                        {
                            if (strcmp (iter_s->word, iter_a->word) == 0)
                            {
                                /* If the word which asked has synonym, multiply by 2 it's possibility to asked it's synonym */
                                current_iter_s->x.possibility *=2; 
                            }
                            iter_s = iter_s->next;
                            current_iter_s = current_iter_s->next;
                        }
                    }
                    else
                    {
                        printf("\n\nFalse answer\n");

                        while (1)
                        {
                            /* If user thinks the antonym they entered is correct, they can add this antonym for the word. If user does that this antonym
                            don't considered as false */
                            printf("Do you want to add this antonym for the given word? (Yes: 1  No: 2): ");
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                                strcpy(iter_a->antonym[j], word);
                                flag_2 = 1;
                                break;
                            }
                            else if (choice == 2)
                                break;
                            else
                                printf("\nInvalid input. Please enter again\n\n");
                        }

                        if (flag_2 == 0)
                        {
                            current_iter_a->x.asked_t ++; /* Increases one the variable which determines how many times the word asked */
                            current_iter_a->x.false_n ++;  /* Increases one the variable which determines how many times the word answered false */
                            current_iter_a->x.possibility *= 2; /* Doubles the possibility of the word to ask because it was answered wrong */

                            /* Prints the informations about the word */
                            printf("\nFor the current word:  True -> %d   False -> %d   How many times asked -> %d   Possibility of being asked -> %.1f\n\n"
                            , current_iter_a->x.true_n, current_iter_a->x.false_n, current_iter_a->x.asked_t, current_iter_a->x.possibility);

                            while (iter_s->next != NULL) /* Searches if the word which asked has synonym */
                            {
                                if (strcmp (iter_s->word, iter_a->word) == 0)
                                {
                                    /* If the word which asked has synonym, multiply by 2 it's possibility to asked it's synonym */
                                    current_iter_s->x.possibility *=2; 
                                }
                                iter_s = iter_s->next;
                                current_iter_s = current_iter_s->next;
                            }
                        }
                    }                        
                        
                    current_iter_a = current_head_a;
                    current_iter_s = current_head_s;

                    iter_a = head_a;
                    iter_s = head_s;

                    if (flag_2 == 1) /* Prints all updated datas in the words list to the file if the user had wanted to antonym in previous step */
                    {
                        fseek(antoynm_f, 0,SEEK_SET);
                        j = 0;

                        while (1)
                        {
                            fprintf(antoynm_f, "%s <> ", iter_a->word);
                            while (1)
                            {
                                fprintf(antoynm_f, "%s", iter_a->antonym[j++]);
                                if (strcmp(iter_a->antonym[j], "\0") == 0)
                                    break;
                                fprintf(antoynm_f, ",");
                            }
                            j = 0;

                            iter_a = iter_a->next;
                            if (iter_a->next == NULL)
                                break;
                            fprintf(antoynm_f, "\n");
                        }            
                    }

                    flag_2 = 0;
                    j = 0;

                    iter_a = head_a;
                    iter_s = head_s;

                    possibility_sum = 0;
                }
                else
                {
                    /* To asks synonyms of the words according to their possibility values */
                    while (iter_s->next != NULL)
                    {
                        possibility_sum += (int)current_iter_s->x.possibility * 10;
                        iter_s = iter_s->next;
                    }
                    r = rand() % possibility_sum;

                    iter_s = head_s;
                    current_iter_s = current_head_s;

                    i = 0;

                    while (iter_s->next != NULL)
                    {
                        j = 0;
                        while (j < (int)current_iter_s->x.possibility * 10)
                        {
                            i++;
                            j++;
                            if (i == r)
                                break;
                        }
                        if (i == r)
                            break;
                        iter_s = iter_s->next;
                        current_iter_s = current_iter_s->next;
                    }
                    j = 0;

                    printf("\nWrite an synonym of %s: ", iter_s->word);
                    scanf(" %[^\n]%*c", word); /* The user enters an antonym */

                    while (strcmp(iter_s->synonym[j], "\0") != 0) /* Checks if the entered word match any of the antonyms of the word */
                    {
                        if (strcmp(word, iter_s->synonym[j++]) == 0) /* Sets flag 1 if checks */
                            flag = 1; 
                    }

                    if (flag == 1)
                    {
                        printf("\n\nCorrect answer\n");

                        current_iter_s->x.asked_t ++; /* Increases one the variable which determines how many times the word asked */
                        current_iter_s->x.true_n ++;  /* Increases one the variable which determines how many times the word answered true */
                        current_iter_s->x.possibility *= 1.0/((current_iter_s->x.true_n)+1); /* Changes the possibility of the word to ask */

                        /* Prints the informations about the word */
                        printf("\nFor the current word:  True -> %d   False -> %d   How many times asked -> %d   Possibility of being asked -> %.1f\n\n"
                        , current_iter_s->x.true_n, current_iter_s->x.false_n, current_iter_s->x.asked_t, current_iter_s->x.possibility);

                        while (iter_a->next != NULL) /* Searches if the word which asked has synonym */
                        {
                            if (strcmp (iter_a->word, iter_s->word) == 0)
                            {
                                /* If the word which asked has synonym, multiply by 2 it's possibility to asked it's synonym */
                                current_iter_a->x.possibility *=2; 
                            }
                            iter_a = iter_a->next;
                            current_iter_a = current_iter_a->next;
                        }
                    }
                    else
                    {
                        printf("\n\nFalse answer\n");

                        while (1)
                        {
                            /* If user thinks the synonym they entered is correct, they can add this synonym for the word. If user does that this synonym
                            don't considered as false */
                            printf("Do you want to add this synoynm for the given word? (Yes: 1  No: 2): ");
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                                strcpy(iter_s->synonym[j], word);
                                flag_2 = 1;
                                break;
                            }
                            else if (choice == 2)
                                break;
                            else
                                printf("\nInvalid input. Please enter again\n\n");
                        }

                        if (flag_2 == 0)
                        {
                            current_iter_s->x.asked_t ++; /* Increases one the variable which determines how many times the word asked */
                            current_iter_s->x.false_n ++;  /* Increases one the variable which determines how many times the word answered false */
                            current_iter_s->x.possibility *= 2; /* Doubles the possibility of the word to ask because it was answered wrong */

                            /* Prints the informations about the word */
                            printf("\nFor the current word:  True -> %d   False -> %d   How many times asked -> %d   Possibility of being asked -> %.1f\n\n"
                            , current_iter_s->x.true_n, current_iter_s->x.false_n, current_iter_s->x.asked_t, current_iter_s->x.possibility);

                            while (iter_a->next != NULL) /* Searches if the word which asked has synonym */
                            {
                                if (strcmp (iter_a->word, iter_s->word) == 0)
                                {
                                    /* If the word which asked has synonym, multiply by 2 it's possibility to asked it's synonym */
                                    current_iter_a->x.possibility *=2; 
                                }
                                iter_a = iter_a->next;
                                current_iter_a = current_iter_a->next;
                            }
                        }
                    }

                    current_iter_a = current_head_a;
                    current_iter_s = current_head_s;

                    iter_a = head_a;
                    iter_s = head_s;

                    if (flag_2 == 1) /* Prints all updated datas in the words list to the file if the user had wanted to add synonym in previous step */
                    {
                        fseek(synonym_f, 0,SEEK_SET);
                        j = 0;

                        while (1)
                        {           
                            fprintf(synonym_f, "%s = ", iter_s->word);
                            while (1)
                            {
                                fprintf(synonym_f, "%s", iter_s->synonym[j++]);
                                if (strcmp(iter_s->synonym[j], "\0") == 0)
                                    break;
                                fprintf(synonym_f, ",");
                            }
                            j = 0;

                            iter_s = iter_s->next;
                            if (iter_s->next == NULL)
                                break;
                            fprintf(synonym_f, "\n");
                        }            
                    }

                    flag_2 = 0;
                    j = 0;

                    iter_a = head_a;
                    iter_s = head_s;

                    possibility_sum = 0;
                }
                flag = 0;        

                /* Passes informations to the binary files */
                while(current_iter_a->next != NULL)
                {
                    fwrite(&(current_iter_a->x), sizeof(word_data), 1, current_user_f_i);               
                    current_iter_a = current_iter_a->next;
                }

                while(current_iter_s->next != NULL)
                {
                    fwrite(&(current_iter_s->x), sizeof(word_data), 1, current_user_f_i);
                    current_iter_s = current_iter_s->next;
                }

                current_iter_a = current_head_a;
                current_iter_s = current_head_s;

                /* Asks the user if they want to continue */
                while (1)
                {
                    printf("Do you want to continue to guessing words? (1: Yes  2: No): ");
                    scanf("%d", &choice);

                    if(choice == 1 || choice == 2)
                        break;
                    
                    else 
                        printf("\nInvalid input. Please enter again\n\n");
                }
                
                if (choice == 2)
                    break;
            }
            fclose(current_user_f_i);
            break;

        case 2:
            while(exit_2 == 0)
            {
                printf("\nWhich one do you want to add\n");
                printf("1: Antonym\n");
                printf("2: Synonym\n");
                printf("0. Exit to main menu\n");

                scanf("%d", &choice_2);

                switch (choice_2)
                {
                case 0:
                    exit_2 = 1;
                    break;
                case 1:
                    j = 0;

                    /* Adds new nodes to the lists to fills them with the new word */
                    while (iter_a->next != NULL) 
                        iter_a = iter_a->next;

                    iter_a->next = (list_a*)malloc(sizeof(list_a));
                    iter_a->next->next = NULL;

                    while (current_iter_a->next != NULL)
                        current_iter_a = current_iter_a->next;

                    current_iter_a->next = (list_p*)malloc(sizeof(list_p));
                    current_iter_a->next->next = NULL;

                    /* Passes datas to the lists */
                    printf("Enter a word: ");
                    scanf("%s", word);
                    strcpy(iter_a->word, word);
                    printf("Enter an antonym of %s: ", word);
                    scanf("%s", word_2);
                    strcpy(iter_a->antonym[j++], word_2);
                    printf("Enter one more antonym of %s: ", word);
                    scanf("%s", word_2);
                    strcpy(iter_a->antonym[j++], word_2);

                    /* Asks user if they want to add more. Until they say no program keeps asking antonyms */
                    while(1)
                    {
                        printf("Do you want to add more (1: Yes  2: No)?: ");
                        scanf("%d", &exit_2);
                        if (exit_2 == 1)
                        {
                            printf("Enter an antonym of %s: ", word);
                            scanf("%s", word_2);
                            strcpy(iter_a->antonym[j++], word_2);
                            exit_2 = 0;
                        }

                        /* Prints new word and antonyms to the list */
                        else if (exit_2 == 2)
                        {
                            fprintf(antoynm_f,"%s <> %s,%s", iter_a->word, iter_a->antonym[0], iter_a->antonym[1]);
                            if (j > 2)
                            {
                                k = 2;
                                while (k < j)                              
                                    fprintf(antoynm_f,",%s",iter_a->antonym[k++]);
                                
                            }
                            fprintf(antoynm_f, "\n");
                            exit_2 = 0;

                            break;
                        }
                        else
                        {
                            printf("\nInvalid input. Please enter again\n\n");
                        }
                    }
                    break;

                case 2:
                    j = 0;

                    /* Adds new nodes to the lists to fills them with the new word */
                    while (iter_s->next != NULL)
                        iter_s = iter_s->next;

                    iter_s->next = (list_s*)malloc(sizeof(list_s));
                    iter_s->next->next = NULL;

                    while (current_iter_s->next != NULL)
                        current_iter_s = current_iter_s->next;

                    current_iter_s->next = (list_p*)malloc(sizeof(list_p));
                    current_iter_s->next->next = NULL;

                    /* Passes datas to the lists */
                    printf("Enter a word: ");
                    scanf("%s", word);
                    strcpy(iter_s->word, word);
                    printf("Enter an synonym of %s: ", word);
                    scanf("%s", word_2);
                    strcpy(iter_s->synonym[j++], word_2);
                    printf("Enter one more synonym of %s: ", word);
                    scanf("%s", word_2);
                    strcpy(iter_s->synonym[j++], word_2);

                    /* Asks user if they want to add more. Until they say no program keeps asking synonyms */
                    while(1)
                    {
                        printf("Do you want to add more (1: Yes  2: No)?: ");
                        scanf("%d", &exit_2);
                        if (exit_2 == 1)
                        {
                            printf("Enter an synonym of %s: ", word);
                            scanf("%s", word_2);
                            strcpy(iter_s->synonym[j++], word_2);
                            exit_2 = 0;
                        }
                        /* Prints new word and synonyms to the list */
                        else if (exit_2 == 2)
                        {
                            fprintf(synonym_f,"%s = %s,%s", iter_s->word, iter_s->synonym[0], iter_s->synonym[1]);
                            if (j > 2)
                            {
                                k = 2;
                                while (k < j)                              
                                    fprintf(synonym_f,",%s",iter_s->synonym[k++]);
                                
                            }
                            fprintf(synonym_f, "\n");
                            exit_2 = 0;
                            break;
                        }
                        else
                        {
                            printf("\nInvalid input. Please enter again\n\n");
                        }
                    }
                    break;
                }         
            }
            exit_2 = 0;
            break;

        default:
            printf("\nInvalid input. Please enter again\n\n");
            break;
        }
    }
}