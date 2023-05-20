#include <stdio.h>
#include <stdlib.h>

#define ROW 3
#define COLUMN 3

typedef enum
{
    down, left, up, rigth
}movement;

void move (movement x, int puzzle_board[ROW][COLUMN], int i, int j); /* Performs movements */

void print_board (int puzzle_board[ROW][COLUMN], int i, int j); /* Prints the board */

int game_check(int puzzle_board[ROW][COLUMN], int i, int j); /* Checks if the game has finished */

int main()
{
    int a, i, j, k1 = 0, k2, r1, r2, r3, r4, c = 300, puzzle_board[ROW][COLUMN];
    movement x;

    printf("The numbers of the board has numbered according their row and column sequences. The sequences start from 0 and goes on.\n");
    printf("If you put the numbers in the correct order, the game is over.\n");

    for (i = 0; i < ROW; i++) /* Creates a board and gives sequential numbers */
    {
       for (j = 0; j < COLUMN ; j++)
        {
            puzzle_board[i][j] = k1;
            k1++;
        } 
    }

    while (c > 0) /* Mixes the board numbers */
    {
        r1 = rand() % ROW;
        r2 = rand() % COLUMN;
        r3 = rand() % ROW;
        r4 = rand() % COLUMN;

        k1 = puzzle_board[r1][r2];
        k2 = puzzle_board[r3][r4];

        puzzle_board[r1][r2] = k2;
        puzzle_board[r3][r4] = k1;

        c--;    
    }

    print_board (puzzle_board, i, j);

    while (1) /* Asks inputs and if they are not valid prints error messages and asks again */
    {
        printf("To move enter location of a number and choose a movement\ndown:  0\nleft:  1\nup:    2\nrigth: 3\nexit:  9 (enter in the movement step)\n");
        printf("Row Location: ");
        scanf("%d", &i);

        if (i >= ROW || i < 0) /* Checks if the entered row is valid */
        {
            printf("\n\n\n!!! Invalid Row Location. Please enter again!!! \n");
            print_board (puzzle_board, i, j);
            continue;
        }
        printf("Column Location: ");
        scanf("%d", &j);

        if (j >= COLUMN || j < 0) /* Checks if the entered column is valid */
        {
            printf("\n\n\n!!! Invalid Column Location. Please enter again!!! \n");
            print_board (puzzle_board, i, j);
            continue;
        }
        printf("Movement: ");
        scanf("%d", &a);
        x = a;

        if(x != 0 && x != 1 && x != 2 && x != 3 && x != 9) /* Checks if the entered movement is valid */
        {
            printf("\n\n\n!!! Invalid move. Please enter again!!! \n");
            print_board (puzzle_board, i, j);
            continue;
        }
        if (x == 9) /* Checks if the user want to end the game */
        {
            printf("\n\n\nGame ended\n");
            print_board (puzzle_board, i, j);
            break;
        }

        move(x, puzzle_board, i, j);
        
        if (game_check(puzzle_board, i, j) == 1) break; /* Checks if the game is over */
    }

    return 0;
}

void move(movement x, int puzzle_board[ROW][COLUMN], int i ,int j)
{
    int t, pi, pj, move_check = 0;

    if (puzzle_board[i][j] == 0) /* Prints error message if number 0 selected */
    {
        printf("\n\n!!!Invalid location!!!\n\n");
        move_check = 1;
    }

    switch (x)
    {
    case up:
        pi = i;
        while (i > 0)
        {
            i--;
            if (puzzle_board[i][j] == 0)
            {
                while (i < pi)
                {
                    t = puzzle_board[i+1][j];
                    puzzle_board[i][j] = t;
                    puzzle_board[++i][j] = 0;
                }

                puzzle_board[i][j] = 0;

                move_check = 1; /* Determines the movement have done correctly */
            }
        }
        break;
    case down:
        pi = i;
        while (i < COLUMN)
        {
            i++;
            if (puzzle_board[i][j] == 0)
            {
                while (i > pi)
                {
                    t = puzzle_board[i-1][j];
                    puzzle_board[i][j] = t;
                    puzzle_board[--i][j] = 0;
                }

                puzzle_board[i][j] = 0;

                move_check = 1; /* Determines the movement have done correctly */
            }
        }
        break;
    case left:
        pj = j;
        while (j > 0)
        {
            j--;
            if (puzzle_board[i][j] == 0)
            {
                while (j < pj)
                {
                    t = puzzle_board[i][j+1];
                    puzzle_board[i][j] = t;
                    puzzle_board[i][++j] = 0;
                }

                puzzle_board[i][j] = 0;

                move_check = 1; /* Determines the movement have done correctly */

                break;
            }
        }
        break;
    case rigth:
        pj = j;
        while (j < ROW)
        {
            j++;
            if (puzzle_board[i][j] == 0)
            {
                while (j > pj)
                {
                    t = puzzle_board[i][j-1];
                    puzzle_board[i][j] = t;
                    puzzle_board[i][--j] = 0;
                }

                puzzle_board[i][j] = 0;

                move_check = 1; /* Determines the movement have done correctly */
            }
        }
        break;  
    }
    
    if(move_check == 0) printf("\n\n!!!Invalid move!!!\n\n"); /* Checks if the move done correctly */
    
    print_board (puzzle_board, i, j); /* Prints the new obtained board */
}

void print_board (int puzzle_board[ROW][COLUMN], int i, int j)
{
    printf("\n");
        for (i = 0; i < ROW; i++) 
        {
        for(j = 0; j < COLUMN; j++)
        {
            printf("***");
        }
        printf("*\n");
        for (j = 0; j < COLUMN; j++)
        {
            printf("*%2d", puzzle_board[i][j]);
        } 
        printf("*\n");
        }
        for(j = 0; j < COLUMN; j++)
        {
            printf("***");
        }
        printf("*\n\n");
}

int game_check(int puzzle_board[ROW][COLUMN], int i, int j)
{
    int t = 0, counter = 0;

    for (i = 0; i < ROW; i++) 
    {
       for (j = 0; j < COLUMN ; j++)
        {
            if (puzzle_board[i][j] != ++t) break; /* Checks if the numbers are in the correct position */
            else counter++;
        } 
    }

    if (counter == (ROW * COLUMN) -1) /* Checks if the game has finished */
    {
        printf("YOU WİN!\n");
        return 1;
    }

    return 0;
}