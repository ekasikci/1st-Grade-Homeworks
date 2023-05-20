#include <stdio.h>
#include <string.h>

# define WORD_LENGTH 20
# define C_NUMBER 3 /* Candidate words number is indicated by you as 3. */

void fix_spelling_error(FILE *text, FILE *dictionary);

void find_best_correction(FILE *dictionary, char w_canditates[C_NUMBER][WORD_LENGTH], char word[], int *d_number, int word_length);

void fix_spelling_error2(FILE *text, FILE *dictionary);

int is_vowel(char a); /* Determines if the character is vowel. */

int main()
{
    FILE *text, *dictionary;

    text = fopen ("text.txt", "r+");
    dictionary = fopen("dictionary.txt", "r");

    fix_spelling_error2(text, dictionary);

    fclose(text);
    fclose(dictionary);
}

void fix_spelling_error(FILE *text, FILE *dictionary)
{
    int d_number = 1, i = 0, j = C_NUMBER, k, flag = 0, s = 0, is_c = 0;
    char w_canditates[C_NUMBER][WORD_LENGTH], letter, word[WORD_LENGTH], c, empty_c[1] = "\0";
    
    while(!feof(text)) /* Separates all words and characters in the text document. */
    {     
        letter = fgetc(text);
        
        if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9')) /* Obtains words from text. */
        {         
            word[i] = letter;
            i++;
            continue;
        }
        /* Obtains characters other than words. */
        else if ((letter > 0 && letter < '0') || (letter > '9' && letter < 'A') || (letter > 'Z' && letter < 'a') || letter > 'z') 
        {                  
            c = letter;
        }
        else continue;

        if (c == feof(text)) break; /* Breaks the loop if reaches the end of the file. */

        word[i] = '\0';

        for(j = 0; j < C_NUMBER; j++) /* Empties the array of candidate words before send to the function. */
        {
            strcpy(&w_canditates[j][0], empty_c);
        }
        if (i > 1) find_best_correction(dictionary, w_canditates, word, &d_number, i);

        if (d_number != 0 && i > 1) /* Does election from the candidate words according to priority. */
        { 
            for(j = 0; j < C_NUMBER; j++) /* Changes letter of words according to vowel priority. */
            {
                for(k = 0; k <= i; k++)
                {
                    if(w_canditates[j][k] == '\0') break; /* Breaks the loop if there is no word. */
                    else if(w_canditates[j][k] == word[k]) continue; /* Skips the letter if the letters of the words are same. */
                    else if(is_vowel(w_canditates[j][k]) == 1)
                    {                                               
                        word[k] = w_canditates[j][k];
                        if (k == i) word[i + 1] = '\0'; /* If words last character (\0) changes adds new one */                                                                        
                        flag = 1; /* Indicates that fault has been found */
                        break;                        
                    }                                                                 
                }
                if(flag == 1) break;                                 
            }
            
            for(j = 0; j < C_NUMBER; j++) /* Changes letters of word according to other differences */
            {
                for(k = 0; k <= i; k++)
                {
                    if(w_canditates[j][k] == '\0') break; /* Breaks the loop if there is no word. */
                    else if(w_canditates[j][k] == word[k]) continue; /* Skips the letter if the letters of the words are same. */
                    else
                    {                        
                        word[k] = w_canditates[j][k];
                        if (k == i) word[i + 1] = '\0'; /* If words last character (\0) changes adds new one. */
                        flag = 1;
                    }                                                                 
                }
                if(flag == 1) break;                                 
            }      
        }
        flag = 0;

        if (i != 0) /* If there is a word prints it into the text. */
        {
            fseek(text, -i - 1, SEEK_CUR); /* Puts the cursor at the beginning of the incorrect word to substitute the new word for the incorrect word. */       
            fprintf(text, "%s", word);
            is_c = 1; /* Indicates that a printing word process was done. */
        }

        if(c != '\0' && is_c == 1) /* If there is no word to be print skips the printing char part. */
        fprintf(text,"%c", c);

        c = '\0';

        d_number = 1; /* Sets difference number to one. */
        i = 0;
        is_c = 0;       
    }    
}

void find_best_correction(FILE *dictionary, char w_canditates[C_NUMBER][WORD_LENGTH], char word[], int *d_number, int word_length)
{
    int result, difference = 0, j = 0, i = 0, flag = 0, word_n = 0, d_number2 = 0, length_difference;
    char letter, word2[WORD_LENGTH];
    
    while(d_number2 <= *d_number && word_n < C_NUMBER)
    {        
        rewind(dictionary);
        
        while(!feof(dictionary)) /* Extracts words from dictionary and compare them with the words in text. */
        {
            letter = fgetc(dictionary);
            if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9')) /*  Obtains words from dictionary. */
            {         
                word2[i] = letter;
                i++;
                continue;
            }
            
            word2[i] = '\0';
            
            if (i == 0) continue; 
            
            difference = 0;
            
            /* Finds the difference between dictionary word and text word. */
            if (word_length > i) length_difference = word_length - i;
            else if (word_length < i) length_difference = i - word_length;
            else length_difference = 0;
          
            i = 0;
            
            /* If the difference between words lengths bigger than expected difference skips that candidate word. */
            if(length_difference > d_number2) continue;
            
            while(i < word_length)
            {
                if (word2[i] == word[i] + 32 || word2[i] == word[i] - 32 ) /* If the letters of the words are of different size but the same letter, skips it. */
                {
                    i++;
                    continue;
                }
                if (word2[i] != word[i]) difference++; 

                i++;
            }

            difference += length_difference; /* Adds the difference between words lengths to difference counter. */
            i = 0;

            /* Accepts the word if the difference between the words is lower or equal the indicated number (indicated number depends on functions). */
            if (difference <= d_number2) 
            {                        
                if (difference == 0) /* Breaks the loop if the word has true syntax. */
                {
                    /* If the letters of the words are of different size but the same letter than equals the letters to the text words letter size. */
                    for(i = 0; i < word_length; i++) 
                    {
                        if(word2[i] == word[i] + 32)
                        {
                            word[i] = word2[i];
                            word[i] -= 32;
                        }
                        if(word2[i] == word[i] - 32)
                        {
                            word[i] = word2[i];
                            word[i] += 32;
                        }
                    }
                    i = 0;
                    
                    flag = 1; /* This flag indicates that the word has true syntax. */
                    break;
                } 
                else
                {
                    /* Skips the word if the word has been copied to the array. */                   
                    if((strcmp(&w_canditates[0][0], word2) != 0) && (strcmp(&w_canditates[1][0], word2) != 0))
                    {                                                    
                        strcpy(&w_canditates[word_n][0], word2); 
                        word_n ++;
                    } 
                    
                    /* If words number in array passes the indicated number (it's been indicated by you as a 3) breaks the loop. */
                    if(word_n >= C_NUMBER) break;
                }
            }
        }      
        if (flag == 1)
        {
            *d_number = 0; 
            break;
        }

        d_number2 ++;        
    }    
}

void fix_spelling_error2(FILE *text, FILE *dictionary)
{
    int d_number = 2, i = 0, j = C_NUMBER, k, flag = 0, is_c = 0;
    char w_canditates[C_NUMBER][WORD_LENGTH], letter, word[WORD_LENGTH], c, empty_c[1] = "\0";

    while(!feof(text)) /* Separates all words and characters in the text document. */
    {
        
        letter = fgetc(text);
        
        if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9')) /*  Obtains words from text. */
        {         
            word[i] = letter;
            i++;
            continue;
        }
        /* Obtains characters other than words. */
        else if ((letter > 0 && letter < '0') || (letter > '9' && letter < 'A') || (letter > 'Z' && letter < 'a') || letter > 'z') 
        {
                    
            c = letter;
        }
        else continue;

        if (c == feof(text)) break; /* Breaks the loop if reaches the end of the file */

        word[i] = '\0';

        for(j = 0; j < C_NUMBER; j++) /* Empties the array of candidate words before send to the function. */
        {
            strcpy(&w_canditates[j][0], empty_c);
        }
        if (i > 1) find_best_correction(dictionary, w_canditates, word, &d_number, i);

        if (d_number != 0 && i > 1) /* Does election from the candidate words according to priority. */
        {     
            for(j = 0; j < C_NUMBER; j++) /* Changes letter of words according to vowel priority. */
            {
                for(k = 0; k <= i; k++)
                {
                    if(w_canditates[j][k] == '\0') break; /* Breaks the loop if there is no word. */
                    else if(w_canditates[j][k] == word[k]) continue; /* Skips the letter if the letters of the words are same. */
                    else if(w_canditates[j][k-1] == word[k-1] && is_vowel(w_canditates[j][k]) == 1)
                    {                                             
                        word[k] = w_canditates[j][k];
                        if (k == i) word[i + 1] = '\0'; /* If words last character (\0) changes adds new one. */                                                                             
                        flag ++; /* Indicates that fault has been found. */
                        if (flag == 2) break; /* Breaks the loop because no more fault can't find. */                   
                    }                                                                 
                }
                if (flag > 1) break;          
            }
            if (flag < 2)
            {
                for(j = 0; j < C_NUMBER; j++) /* Changes letters of word according to other differences. */
                {
                    for(k = 0; k <= i; k++)
                    {
                        if(w_canditates[j][k] == '\0') break; /* Breaks the loop if there is no word. */
                        else if(w_canditates[j][k] == word[k]) continue; /* Skips the letter if the letters of the words are same. */
                        else
                        {                        
                            word[k] = w_canditates[j][k];
                            if (k == i) word[i + 1] = '\0'; /* If words last character (\0) changes adds new one. */
                            flag ++; /* Indicates that fault has been found. */
                            if (flag == 2) break; /* Breaks the loop because no more fault can't find. */
                        }                                                                 
                    }
                    if (flag > 1) break;                               
                }     
            }         
        }
        flag = 0;

        if (i != 0) /* If there is a word prints it into the text. */
        {
            fseek(text, -i - 1, SEEK_CUR); /* Puts the cursor at the beginning of the incorrect word to substitute the new word for the incorrect word. */       
            fprintf(text, "%s", word);
            is_c = 1; /* Indicates that a printing word process was done. */
        }

        if(c != '\0' && is_c == 1) /* If there is no word to be print skips the printing char part. */
        fprintf(text,"%c", c);

        c = '\0';

        d_number = 2; /* Sets difference number to two. */
        i = 0;
        is_c = 0;       
    }  
}

int is_vowel(char a) /* Determines if the character is vowel. */
{
    if(a == 65 || a == 69 || a == 73 || a == 79 || a == 85 || a == 97 || a == 101 || a == 105 || a == 111 || a == 117 ) return 1;
    else return 0;
}