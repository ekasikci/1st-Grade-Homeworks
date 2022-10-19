/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 20

void print_maze(cell_type maze[][8]); /* This function prints the current state of the maze */


void wh_is_player(cell_type maze[][8], cell_type player, int *i, int *j); /* This function determines the location of the indicated player */


void print_towers(char s[7], char e[7], char a[7], int step); /* This function prints given tower */


int pass(char x[7], char y[7], char z[7], int n, int *step); /* This function passes n tower from x to y */


void find_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words, char word[WORDSIZE]);


void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)
{
    char c;

    /*c = getc(infid);

	if (c == words_to_delete[0])
    {
        if (words_to_delete[0] == '\0')
        delete_words (infid, outfid, &words_to_delete[1], number_of_words);
    }
    else if (c == '\n')
    {
        
    }
    else ()
    {
        
    }*/
}


void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE* infid;
	FILE* outfid;

    infid = fopen(infile,"r");
    outfid = fopen(outfile,"w");

	delete_words (infid, outfid, words_to_delete, number_of_words);
}

void find_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words, char word[WORDSIZE])
{
    char letter;
    int i;
 
    letter = getc(infid); 

    if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= '0' && letter <= '9'))
    {
        word [0] = letter;
        find_words(infid, outfid, words_to_delete, number_of_words, &word[1]);
    }
    else
    {
        word[0] = '\0';
    }
}

int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
    int i,j;

    print_maze(maze); /* This function prints the current state of the maze */

    printf("Pick a player by entering it's number\n"); /* User enters the number of the player, if the number is invalid, the program asks again */
	printf("Player 1: 1\n");
	printf("Player 2: 2\n");
	scanf("%u", &player);
	if (player != 1 && player != 2)
    {
        printf("!!!Invalid number!!!\n\n");
        maze_move(maze, player, move);
    }

    printf("Pick a movement by entering it's number\n"); /* User enters the number move, if the number is invalid, the program asks again */
	printf("Down : 0\n");
	printf("Left : 1\n");
	printf("Up   : 2\n");
	printf("Rigth: 3\n");
	scanf("%u", &move);
	if(move != 0 && move != 1 && move != 2 && move != 3)
    {
        printf("!!!Invalid number!!!\n\n");
        maze_move(maze, player, move);
    }

    wh_is_player(maze, player, &i, &j); /* This function determines the location of the selected player*/

    switch (move) /* This switch statement implements the move according to entered move number. 
    If the move can't implement it prints error massage and asks move number again */
    {
        case 0: if (maze[i+1][j] == cell_free) /* This statement indicates that the desired movement is appropriate */
                {
                    maze[i+1][j] = player; /* Moves player to the desired location */
                    maze[i][j] = cell_free;
                    maze_move(maze, player, move);
                }
                else if (maze[i+1][j] == cell_target) return 1; /* This statement indicates that the target has been reached */
                else 
                {
                    printf("!!!Invalid move!!!\n");
                    maze_move(maze, player, move);
                }
                break;
        case 1: if (maze[i][j-1] == cell_free) /* This statement indicates that the desired movement is appropriate */
                {
                    maze[i][j-1] = player; /* Moves player to the desired location */
                    maze[i][j] = cell_free;
                    maze_move(maze, player, move);                                                         
                }
                else if (maze[i][j-1] == cell_target) return 1; /* This statement indicates that the target has been reached */
                else 
                {
                    printf("!!!Invalid move!!!\n");
                    maze_move(maze, player, move);
                }
                break;
        case 2: if (maze[i-1][j] == cell_free) /* This statement indicates that the desired movement is appropriate */
                {
                    maze[i-1][j] = player; /* Moves player to the desired location */
                    maze[i][j] = cell_free;
                    maze_move(maze, player, move);                                                              
                }
                else if (maze[i-1][j] == cell_target)return 1; /* This statement indicates that the target has been reached */
                else 
                {
                    printf("!!!Invalid move!!!\n");
                    maze_move(maze, player, move);
                }
                break;
        case 3: if (maze[i][j+1] == cell_free) /* This statement indicates that the desired movement is appropriate */
                {
                    maze[i][j+1] = player; /* Moves player to the desired location */
                    maze[i][j] = cell_free;
                    maze_move(maze, player, move);                                                            
                }
                else if (maze[i][j+1] == cell_target) return 1; /* This statement indicates that the target has been reached */
                else 
                {
                    printf("!!!Invalid move!!!\n");
                    maze_move(maze, player, move);
                }
                break;
    }
    
}

void print_maze(cell_type maze[][8]) /* This function prints the current state of the maze */
{
    int i,j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            switch (maze[i][j])
            {
                case 0: printf("  *  ");               
                        break;
                case 1: printf("1 o-:");               
                        break;
                case 2: printf("2 o-:");
                        break;
                case 3: printf("     ");
                        break;
                case 4: printf("|||||");
                        break;         
            }
        }
        printf("\n");
    }
}

void wh_is_player(cell_type maze[][8], cell_type player, int *i, int *j) /* This function determines the location of the indicated player */
{
    int a , b;

    for (a = 0; a < 8; a++)
    {
        for (b = 0; b < 8; b++)
        {
            if (maze[a][b] ==  player)
            {
                *i = a; 
                *j = b;
                a = 8;
                b = 8;
            }
        }
        printf("\n");
    }
}

void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
    char s[7], a[7], e[7];

	int step = 0, i, j = 0, flag;

    for (i = 6; i >= 0; i--) s[i] = 48;
    for (i = 6; i >= 0; i--) a[i] = 48;
    for (i = 6; i >= 0; i--) e[i] = 48;

    for (i = n; i > 0; i--) s[j++] = i + 48; /* This loop places the towers in the start array */

    
    print_towers(s, a, e, step);

    switch (n) /* This statement does implementations according to entered number of the tower between 1-7 */
    /* pass (s, e, a, n, &step) passes n tower from s to e. This implementation makes it easy to apply tower movements */
    {
        case 1: pass (s, e, a, 1, &step); 
                break;
        case 2: pass (s, e, a, 2, &step);
                break;
        case 3: pass (s, e, a, 3, &step);
                break;
        case 4: pass (s, a, e, 3, &step);
                pass (s, e, a, 1, &step);
                pass (a, e, s, 3, &step);
                break;
        case 5: pass (s, a, e, 3, &step);
                pass (s, e, a, 2, &step);
                pass (a, e, s, 3, &step);
                break;
        case 6: pass (s, a, e, 3, &step);
                pass (s, e, a, 3, &step);
                pass (a, e, s, 3, &step);
                break;
        case 7: pass (s, e, a, 3, &step);
                pass (s, a, e, 3, &step);
                pass (e, a, s, 3, &step);
                pass (s, e, a, 1, &step);
                pass (a, s, e, 3, &step);
                pass (a, e, s, 3, &step);
                pass (s, e, a, 3, &step);
                break;
    }
    
}

void print_towers(char s[7], char a[7], char e[7], int step) /* This function prints given tower */
{
	int i, si = 0, ei = 0, ai = 0, space, line, js = 1, ja = 1, je = 1, y, s_peg, a_peg, e_peg;

    for (i = 6; i >= 0; i--) if (s[i] != '0') si++;

    s_peg = si;

    for (i = 6; i >= 0; i--) if (a[i] != '0') ai++;

    a_peg = ai;

    for (i = 6; i >= 0; i--) if (e[i] != '0') ei++;

    e_peg = ei;

    printf("\n%d %d %d\n", s_peg, a_peg, e_peg);
    	
    printf("======================================================\n");
	printf("=                       Step %d                      =\n", step);
	printf("======================================================\n");
	printf("        S                 A                 E         \n\n");

    for(line = 1; line <= 7*2 + 1; line++)
    {
        if (line == 7*2 + 1)
        {
            space = 7 - js;
            for (i = 0; i <= space; i ++) printf(" ");
            y = 5 + (js - 1) * 2;
            for(i = 1; i < y - 1; i ++) printf("*");
            for (i = 0; i <= space + 1; i ++) printf(" ");
            
            space = 7 - ja;
            for (i = 0; i <= space; i ++) printf(" ");
            y = 5 + (ja - 1) * 2;
            for(i = 1; i < y - 1; i ++) printf("*");
            for (i = 0; i <= space + 1; i ++) printf(" ");
                    
            space = 7 - je;
            for (i = 0; i <= space; i++) printf(" ");
            y = 5 + (je - 1) * 2;
            for(i = 1; i < y - 1; i ++) printf("*");
            for (i = 0; i <= space + 1 ; i ++) printf(" ");

            printf("\n");
            break;
        }
        if (line % 2 == 1)
        {
            if (7 * 2 + 1 - line < s_peg * 2 + 1)
            {
                y = 5 + (js - 1) * 2;
                space = 7 - js;
                for (i = 0; i < space; i ++) printf(" ");
                for(i = 1; i <= y; i ++) printf("*");  
                for (i = 0; i < space + 1; i ++) printf(" ");
            }          
            else
            {
                for (space = 0; space <= 7*2 + 3; space ++) printf(" ");
            }

            if (7 * 2 + 1 - line < a_peg * 2 + 1)
            {
                y = 5 + (ja - 1) * 2;
                space = 7 - ja;
                for (i = 0; i < space; i ++) printf(" ");
                for(i = 1; i <= y; i ++) printf("*");  
                for (i = 0; i < space + 1; i ++) printf(" ");
            }
            else
            {
                for (space = 0; space <= 7*2 + 3; space ++) printf(" ");
            }

            if (7 * 2 + 1 - line < e_peg * 2 + 1)
            {
                y = 5 + (je - 1) * 2;
                space = 7 - je;
                for (i = 0; i < space; i ++) printf(" ");
                for(i = 1; i <= y; i ++) printf("*");  
                for (i = 0; i < space + 1; i ++) printf(" ");
            }
            else
            {
                for (space = 0; space < 7*2 + 3; space ++) printf(" ");
            }          
        }
        else
        {
            if (7 * 2 + 1 - line < s_peg * 2 + 1)
            {
                y = 5 + (js - 1) * 2;
                space = 7 - js;
                for (i = 0; i < space; i ++) printf(" ");
                printf("*");
                for (i = 0; i < js; i ++) printf(" ");	
                printf("%c", s[--si]);
                for (i = 0; i < js; i ++) printf(" ");
                printf("*");
                for (i = 0; i < space + 1; i ++) printf(" ");
                js ++;
            }
            else
            {
                for (space = 0; space <= 7*2 + 3; space ++) printf(" ");
            }

            if (7 * 2 + 1 - line < a_peg * 2 + 1)
            {
                y = 5 + (ja - 1) * 2;
                space = 7 - ja;
                for (i = 0; i < space; i ++) printf(" ");
                printf("*");
                for (i = 0; i < ja; i ++) printf(" ");	
                printf("%c", a[--ai]);
                for (i = 0; i < ja; i ++) printf(" ");
                printf("*");
                for (i = 0; i < space + 1; i ++) printf(" ");
                ja ++;
            }
            else
            {
                for (space = 0; space <= 7*2 + 3; space ++) printf(" ");
            }

            if (7 * 2 + 1 - line < e_peg * 2 + 1)
            {
                y = 5 + (je - 1) * 2;
                space = 7 - je;
                for (i = 0; i < space; i ++) printf(" ");
                printf("*");
                for (i = 0; i < je; i ++) printf(" ");	
                printf("%c", e[--ei]);
                for (i = 0; i < je; i ++) printf(" ");
                printf("*");
                for (i = 0; i < space; i ++) printf(" ");
                je ++;
            }
            else
            {
                for (space = 0; space <= 7*2 + 3; space ++) printf(" ");
            }
        }
        printf("\n");
    }
}

int pass(char x[7], char y[7], char z[7], int n, int *step) /* This function pass n tower to y from x */
{
    int i, j;

    if (n == 1)
    {
        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;
    }
    else if (n == 2)
    {
        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (z[j] != '0') break;
        if (i != -1)
        {
            z[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (z[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = z[i];
            z[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;
    }

    else if (n == 3)
    {
        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (z[j] != '0') break;
        if (i != -1)
        {
            z[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (y[i] != '0') break;
        for (j = 6; j >= 0; j--) if (z[j] != '0') break;
        if (i != -1)
        {
            z[j+1] = y[i];
            y[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (z[i] != '0') break;
        for (j = 6; j >= 0; j--) if (x[j] != '0') break;
        if (i != -1)
        {
            x[j+1] = z[i];
            z[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (z[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = z[i];
            z[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;

        for (i = 6; i >= 0; i--) if (x[i] != '0') break;
        for (j = 6; j >= 0; j--) if (y[j] != '0') break;
        if (i != -1)
        {
            y[j+1] = x[i];
            x[i] = '0';
        }
        (*step) ++;
        print_towers(x, z, y, *step);
        if (x[0] == '0' && y[0] == 48 + n && z[0] == '0') return 1;
    }
}