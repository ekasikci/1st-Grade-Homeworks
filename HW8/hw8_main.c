/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 20

void test_clean_file () 
{
	char infile[10] = "input.txt", outfile[10] = "output.txt", * words_to_delete[WORDSIZE];
	int number_of_words;

	clean_file(infile, outfile, words_to_delete, number_of_words);
}


void test_maze_move ()
{
	cell_type maze[8][8] = {{cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall}, /* The maze is built here */
						   {cell_wall,cell_p1,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall},
						   {cell_wall,cell_free,cell_free,cell_free,cell_free,cell_free,cell_free,cell_wall},
						   {cell_wall,cell_wall,cell_free,cell_free,cell_wall,cell_wall,cell_free,cell_wall},
						   {cell_wall,cell_wall,cell_free,cell_wall,cell_target,cell_free,cell_free,cell_wall},
						   {cell_wall,cell_free,cell_free,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall},
						   {cell_wall,cell_wall,cell_free,cell_free,cell_free,cell_free,cell_p2,cell_wall},
						   {cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall}};
	int result, p, m, i, j;
	
	cell_type player;
	move_type move;
	
	result = maze_move(maze, player, move);

	if (result == 1) printf("You'reached the target!!!\n\n\n"); /* This indicates that the target has been reached */
}


void test_towers_of_hanoi ()
{
	int n;

	char s, e, a;

	printf("Enter an integer between 1-7 to determine the height of towers of hanoi: ");
	scanf("%d",&n);

	s = 48 + n;
	e = '0';
	a  = '0';
	
	towers_of_hanoi(s, e, a, n);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */